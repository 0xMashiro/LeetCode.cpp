#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""编译 + 测试一组工具：`compile_project` / `compile_and_test` / `execute_test_suite`。

全走 subprocess 调 `just`，failure 会过 classifier 给出 error_type + 可复用的
`action_items` 修复提示。
"""

import re
import subprocess
import sys
from typing import Any, Dict, List, Optional

from script.leetcode.ai import result_utils
from script.leetcode.ai.tools.classifier import analyze_test_failure, classify_compilation_error
from script.leetcode.config import AIConfig


class BuildRunner:
    def compile_project(self, problem_id: Optional[int] = None) -> Dict[str, Any]:
        try:
            if problem_id:
                result = subprocess.run(
                    ["just", "multi", str(problem_id)],
                    capture_output=True, text=True, timeout=AIConfig.BUILD_TIMEOUT,
                )
            else:
                from pathlib import Path
                cmake_cache = Path("build/CMakeCache.txt")
                if cmake_cache.exists():
                    cmake_cache.unlink()
                result = subprocess.run(
                    ["just", "build"],
                    capture_output=True, text=True, timeout=AIConfig.BUILD_TIMEOUT,
                )

            if result.returncode == 0:
                excerpt = result_utils.truncate_output(result.stdout, 1000)
                return {
                    "is_successful": True,
                    "status_message": "编译成功",
                    "output": excerpt,
                    "output_excerpt": excerpt,
                }

            full_output = result.stderr + result.stdout
            analysis = classify_compilation_error(full_output)
            excerpt = result_utils.truncate_output(full_output)
            return _compile_failure(analysis, excerpt, next_steps="修复后重新调用 compile_and_test。")
        except subprocess.TimeoutExpired:
            return _timeout("编译超时", "编译时间过长，可能是代码有无限递归或其他问题")
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}

    def compile_and_test(self, problem_id: int) -> Dict[str, Any]:
        try:
            result = subprocess.run(
                ["just", "single", str(problem_id)],
                capture_output=True, text=True,
                timeout=AIConfig.BUILD_TIMEOUT + AIConfig.TEST_TIMEOUT,
            )
            output = result.stdout + result.stderr
            excerpt = result_utils.truncate_output(output)

            if result.returncode != 0:
                analysis = classify_compilation_error(output)
                return _compile_failure(analysis, excerpt, next_steps="修复代码后重新 compile_and_test。")

            if "PASSED" in output and "FAILED" not in output.split("PASSED")[0]:
                match = re.search(r"\[(==========)\]\s+(\d+)\s+test", output)
                count = match.group(2) if match else "?"
                return {
                    "is_successful": True,
                    "status_message": f"编译成功，{count} 个测试通过",
                    "output": excerpt,
                    "output_excerpt": excerpt,
                    "next_steps": "本地测试通过，等待在线验证或后续流程。",
                }

            if "FAILED" in output:
                analysis = analyze_test_failure(output)
                return _test_failure(analysis, excerpt, next_steps="修复失败用例后重新 compile_and_test。")

            return {
                "is_successful": True,
                "status_message": "编译成功，测试结果未知",
                "output": excerpt,
                "output_excerpt": excerpt,
            }
        except subprocess.TimeoutExpired:
            return _timeout("编译或测试超时", "编译或测试时间过长，请检查代码是否有无限循环或其他问题")
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}

    def execute_test_suite(self, problem_id: int) -> Dict[str, Any]:
        try:
            result = subprocess.run(
                [sys.executable, "-m", "script.leetcode.cli", "test", str(problem_id)],
                capture_output=True, text=True, timeout=AIConfig.TEST_TIMEOUT,
            )
            output = result.stdout + result.stderr
            excerpt = result_utils.truncate_output(output)

            if result.returncode == 0:
                return {
                    "is_successful": True,
                    "status_message": "所有测试通过",
                    "output": excerpt,
                    "output_excerpt": excerpt,
                }

            analysis = analyze_test_failure(output)
            return _test_failure(analysis, excerpt, next_steps="修复后重新执行测试。")
        except subprocess.TimeoutExpired:
            return _timeout("测试超时", "算法可能存在无限循环或时间复杂度过高，请检查循环条件和算法复杂度")
        except Exception as e:
            return {"is_successful": False, "error_message": str(e), "error_type": "exception"}


def _compile_failure(analysis: Dict[str, Any], excerpt: str, *, next_steps: str) -> Dict[str, Any]:
    return {
        "is_successful": False,
        "error_message": "编译失败",
        "error_type": analysis["type"],
        "error_details": analysis["details"],
        "suggestion": analysis["suggestion"],
        "output": excerpt,
        "output_excerpt": excerpt,
        "action_items": _action_items(analysis["type"]),
        "next_steps": next_steps,
    }


def _test_failure(analysis: Dict[str, Any], excerpt: str, *, next_steps: str) -> Dict[str, Any]:
    return {
        "is_successful": False,
        "error_message": f"测试失败: {analysis['type']}",
        "error_type": analysis["type"],
        "error_details": analysis["details"],
        "suggestion": analysis["suggestion"],
        "output": excerpt,
        "output_excerpt": excerpt,
        "action_items": _action_items(analysis["type"]),
        "next_steps": next_steps,
    }


def _timeout(msg: str, suggestion: str) -> Dict[str, Any]:
    return {
        "is_successful": False,
        "error_message": msg,
        "error_type": "timeout",
        "suggestion": suggestion,
        "action_items": _action_items("超时"),
        "next_steps": "排查后重新执行。",
    }


def _action_items(error_type: str) -> List[str]:
    if error_type in {"语法错误", "类型错误", "编译错误", "链接错误", "头文件错误"}:
        return [
            "定位并修复 source/header 的编译问题",
            "如有必要更新测试用例以覆盖边界",
            "调用 create_or_update_file(overwrite_existing=true) 后重新 compile_and_test",
        ]
    if error_type in {"结果错误", "内存错误", "超时"}:
        return [
            "基于失败信息定位算法或边界条件问题",
            "先补充/修正测试用例，再修复实现",
            "修改后重新调用 compile_and_test 验证",
        ]
    return [
        "先查看关键错误摘要并定位问题",
        "修复后重新编译并测试",
    ]
