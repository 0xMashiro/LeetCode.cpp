#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""一轮工具调用的编排：参数解析、执行、结果回写、摘要汇总。

`ToolRoundProcessor` 承接 AISolver 原先的 `_handle_tool_calls` 调用树，把散在
`self` 上的 `_compile_fix_count` 和工具分类集合都吸收进来；`update_summary` /
`should_short_circuit` / `is_success` 等纯函数暴露在模块级，方便单测。
"""

import json
from typing import Any, Dict, List

from script.leetcode.ai import result_utils
from script.leetcode.ai.messages import ToolCall
from script.leetcode.config import AIConfig
from script.leetcode.utils import ColorCode, color_text, log_with_time


COMPILE_TOOLS = {"compile_project", "compile_and_test"}
RUNTIME_FAILURE_TOOLS = {"compile_project", "compile_and_test", "execute_test_suite"}
FILE_MUTATION_TOOLS = {"create_or_update_file", "append_test_case"}


def should_short_circuit(summary: Dict[str, Any]) -> bool:
    """本轮工具里有成功的 compile_and_test → 可以跳到完成路径。"""
    return bool(summary.get("compile_passed"))


def update_summary(summary: Dict[str, Any], tool_name: str, result: Dict[str, Any]) -> None:
    """把单次工具结果反映到本轮摘要（file_mutated / error_signatures / compile_passed）。"""
    success = result_utils.is_success(result)
    if success and tool_name in FILE_MUTATION_TOOLS:
        summary["file_mutated"] = True
    if not success and tool_name in RUNTIME_FAILURE_TOOLS:
        summary["error_signatures"].append(result_utils.error_signature(tool_name, result))
    if success and tool_name == "compile_and_test":
        summary["compile_passed"] = True


class ToolRoundProcessor:
    def __init__(self, executor: Any) -> None:
        self._executor = executor
        self._compile_fix_count = 0

    def reset(self) -> None:
        self._compile_fix_count = 0

    @property
    def compile_fix_count(self) -> int:
        return self._compile_fix_count

    def run(
        self,
        tool_calls: List[ToolCall],
        *,
        problem_id: int,
        messages: List[Dict[str, Any]],
    ) -> Dict[str, Any]:
        summary: Dict[str, Any] = {"file_mutated": False, "error_signatures": []}
        for tc in tool_calls:
            self._run_one(tc, problem_id, messages, summary)
        return summary

    def _run_one(
        self,
        tc: ToolCall,
        problem_id: int,
        messages: List[Dict[str, Any]],
        summary: Dict[str, Any],
    ) -> None:
        log_with_time(f"🔧 调用工具: {tc.function_name}", ColorCode.MAGENTA)
        preview = tc.function_arguments
        if len(preview) > 100:
            preview = preview[:100] + "..."
        print(f"   参数: {preview}")

        try:
            args = json.loads(tc.function_arguments)
        except Exception as e:
            self._append_error(tc, f"参数 JSON 解析失败: {e}", messages, summary)
            return

        if tc.function_name in COMPILE_TOOLS and problem_id:
            args["problem_id"] = problem_id

        try:
            result = self._executor.execute(tc.function_name, args)
        except Exception as e:
            self._append_error(tc, f"工具调用异常: {e}", messages, summary)
            return

        self._update_compile_counter(tc.function_name, result)
        update_summary(summary, tc.function_name, result)
        _print_result(result)
        messages.append({
            "role": "tool",
            "tool_call_id": tc.id,
            "content": json.dumps(result_utils.compact(result), ensure_ascii=False),
        })

    def _update_compile_counter(self, tool_name: str, result: Dict[str, Any]) -> None:
        if tool_name not in COMPILE_TOOLS:
            return
        if result_utils.is_success(result):
            self._compile_fix_count = 0
            return
        self._compile_fix_count += 1
        if self._compile_fix_count >= AIConfig.MAX_COMPILE_FIX_ATTEMPTS:
            print(color_text(
                f"⚠️ 警告：已连续 {self._compile_fix_count} 次编译失败。建议：\n"
                "1. 仔细检查代码结构和语法\n"
                "2. 使用 retrieve_file_content 查看完整代码\n"
                "3. 考虑简化实现或检查头文件包含",
                ColorCode.YELLOW.value,
            ))

    @staticmethod
    def _append_error(
        tc: ToolCall,
        error_msg: str,
        messages: List[Dict[str, Any]],
        summary: Dict[str, Any],
    ) -> None:
        print(color_text(f"   ✗ {error_msg}", ColorCode.RED.value))
        error_payload = {
            "status": "error",
            "is_successful": False,
            "message": error_msg,
            "error_message": error_msg,
            "error_type": "execution_exception",
            "retryable": False,
            "artifacts": [],
        }
        messages.append({
            "role": "tool",
            "tool_call_id": tc.id,
            "content": json.dumps(result_utils.compact(error_payload), ensure_ascii=False),
        })
        if tc.function_name in RUNTIME_FAILURE_TOOLS:
            summary["error_signatures"].append(result_utils.error_signature(
                tc.function_name,
                {"error_message": error_msg, "error_type": "execution_exception"},
            ))


def _print_result(result: Dict[str, Any]) -> None:
    if result_utils.is_success(result):
        msg = result.get("message") or result.get("status_message") or "成功"
        print(color_text(f"   ✓ {msg}", ColorCode.GREEN.value))
        artifacts = result.get("artifacts", [])
        if artifacts:
            for artifact in artifacts:
                if artifact.get("type") == "file":
                    category = artifact.get("category", "file")
                    path = artifact.get("path", "")
                    print(f"      {category}: {path}")
        elif "generated_files" in result:
            for file_info in result["generated_files"]:
                print(f"      {file_info['file_category']}: {file_info['file_path']}")
    else:
        error = result.get("message") or result.get("error_message") or "未知错误"
        preview = error[:500] + "..." if len(error) > 500 else error
        print(color_text(f"   ✗ 失败: {preview}", ColorCode.RED.value))
