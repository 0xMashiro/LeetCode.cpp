#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Scaffold 模式相关的文件生成、示例注入、完成校验。

scaffold 模式下先生成三文件模板（空 body 可编译），再把题目官方 examples
翻译成 TEST_P body 注入 test 文件，模型只需专注 source 的算法实现。
"""

import json
import re
import shutil
from datetime import datetime
from pathlib import Path
from typing import Any, Dict, List, Optional

from script.leetcode.ai.tools.description import extract_examples
from script.leetcode.ai.tools.example_translator import translate_examples_to_cpp
from script.leetcode.config import AIProvider
from script.leetcode.services import (
    DesignClassExtractor,
    FileGenerator,
    SignatureParser,
)
from script.leetcode.utils import ColorCode, log_with_time

SCAFFOLD_MARKER = "/* Code here */"
OFFICIAL_EXAMPLE_TODO_MARKER = "// TODO: 用上面 Input 构造 C++ 变量"


class ScaffoldManager:
    def __init__(
        self,
        repository: Any,
        openai_client: Any,
        provider: AIProvider,
    ) -> None:
        self._repo = repository
        self._client = openai_client
        self._provider = provider

    def has_solution(self, problem_id: int) -> bool:
        """三文件都存在且 source 里没有 scaffold marker → 视为完整解答。

        读取失败时保守按"已解"处理，避免误覆盖用户手写代码。
        """
        problem_info = self._repo.get_by_id(problem_id)
        generator = FileGenerator(problem_info)
        if not generator.files_exist():
            return False

        _, source_path, _ = generator._get_file_paths()
        try:
            source_content = source_path.read_text(encoding="utf-8")
        except Exception:
            return True
        return SCAFFOLD_MARKER not in source_content

    def cleanup_files(self, problem_id: int) -> None:
        try:
            problem_info = self._repo.get_by_id(problem_id)
            generator = FileGenerator(problem_info)
            removed = generator.remove_files()
            if removed:
                log_with_time(f"🧹 已清理 {len(removed)} 个生成的文件", ColorCode.YELLOW)
        except Exception as e:
            log_with_time(f"⚠️ 清理文件时出错: {e}", ColorCode.YELLOW)

    def snapshot_failed_run(
        self,
        problem_id: int,
        *,
        reason: str,
        metrics: Optional[Dict[str, Any]] = None,
    ) -> Optional[Path]:
        """Copy generated files and metrics before cleanup.

        Failed AI runs are useful training data. We keep the snapshot outside
        tracked source paths so cleanup can still leave the working tree clean.
        """
        try:
            problem_info = self._repo.get_by_id(problem_id)
            generator = FileGenerator(problem_info)
            paths = generator._get_file_paths()
            existing = [p for p in paths if p.exists()]
            if not existing and not metrics:
                return None

            timestamp = datetime.now().strftime("%Y%m%d-%H%M%S")
            safe_reason = re.sub(r"[^A-Za-z0-9_.-]+", "-", reason).strip("-") or "failed"
            snapshot_dir = (
                Path(".leetcode-cache")
                / "failed-runs"
                / f"p{problem_id}_{timestamp}_{safe_reason[:48]}"
            )
            snapshot_dir.mkdir(parents=True, exist_ok=True)

            for path in existing:
                destination = snapshot_dir / path
                destination.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(path, destination)
            if metrics is not None:
                (snapshot_dir / "metrics.json").write_text(
                    json.dumps(metrics, ensure_ascii=False, indent=2),
                    encoding="utf-8",
                )
            log_with_time(f"🧾 失败快照已保存: {snapshot_dir}", ColorCode.CYAN)
            return snapshot_dir
        except Exception as e:
            log_with_time(f"⚠️ 保存失败快照时出错: {e}", ColorCode.YELLOW)
            return None

    def prepare(self, problem_id: int) -> None:
        """scaffold 模式入口：若三文件不存在则生成模板并注入官方 examples。"""
        problem_info = self._repo.get_by_id(problem_id)
        if FileGenerator(problem_info).files_exist():
            log_with_time("🧱 已存在 scaffold 文件，直接进入解题", ColorCode.CYAN)
            return

        problem_data = self._repo.get_detail_by_id(problem_id, include_code=True)
        generator = self._build_generator(problem_id, problem_info, problem_data)
        created = generator.generate_files(force=False)
        log_with_time(f"🧱 已生成 scaffold：{len(created)} 个文件", ColorCode.CYAN)

        self._inject_official_examples(problem_info, problem_data)

    def user_message_preamble(self, problem_id: int, problem_data: Any) -> str:
        """scaffold 模式首条 user message：把当前三文件内容内联，明确只填 body。"""
        problem_info = self._repo.get_by_id(problem_id)
        header_path, source_path, test_path = FileGenerator(problem_info)._get_file_paths()

        return f"""请帮我完成 LeetCode 题目：

题目 ID: {problem_id}
标题: {problem_data.title}
难度: {problem_data.difficulty}

【Scaffold 模式】三个模板文件已经生成好，当前状态能编译通过但测试会失败（solution1 返回默认值、TEST_P 体为空）。你只需要填实现，不要重建骨架。

任务步骤（按顺序）：
1. 调用 `fetch_problem_metadata` 拿到完整题目描述和示例（你需要题目示例来写测试用例）
2. 基于题意修改 source 文件：把 `solution1` 函数体里的 `/* Code here */` 和 `return ...()` 换成真实算法
3. 基于题目给出的示例修改 test 文件：把 `TEST_P(..., Example1)` 函数体填满；如果题目有多个示例，再加 TEST_P(..., Example2/3/...)
4. 调用 `create_or_update_file`（overwrite_existing=true）提交修改；files 只包含你改过的 category（source、test），header 不用动
5. 调用 `compile_and_test` 验证

当前 scaffold 文件内容：

=== {header_path} ===
```cpp
{_read_file(header_path)}
```

=== {source_path} ===
```cpp
{_read_file(source_path)}
```

=== {test_path} ===
```cpp
{_read_file(test_path)}
```

禁止改动：namespace、类声明、SolutionBase 继承、setMetaInfo、registerStrategy、getSolution() 调度、test fixture（TestWithParam/SetUp）、INSTANTIATE_TEST_SUITE_P —— 这些已经是对的，改了反而会出编译/链接错误。"""

    def still_dirty(self, problem_id: int) -> bool:
        """test 文件里是否仍有注入时留的 OfficialExample TODO 标记。

        用于拦截：模型不调 create_or_update_file、只用文字讨论却被误判为"完成"。
        读文件失败时保守返回 False，避免误杀正常完成。
        """
        try:
            problem_info = self._repo.get_by_id(problem_id)
            _, _, test_path = FileGenerator(problem_info)._get_file_paths()
            if not test_path.exists():
                return True
            return OFFICIAL_EXAMPLE_TODO_MARKER in test_path.read_text(encoding="utf-8")
        except Exception:
            return False

    def _build_generator(self, problem_id: int, problem_info: Any, problem_data: Any) -> FileGenerator:
        code_template = problem_data.get_cpp_code_template()
        is_design = self._repo.is_design_problem(problem_id)

        if is_design:
            design_def = DesignClassExtractor.extract(code_template) if code_template else None
            return FileGenerator(problem_info=problem_info, is_design=True, design_class_def=design_def)

        func_sig = None
        if code_template:
            try:
                extracted = SignatureParser.extract_from_code_template(code_template)
                if extracted:
                    func_sig = SignatureParser.parse(extracted)
            except Exception as e:
                log_with_time(f"⚠️ 签名提取失败，使用默认模板: {e}", ColorCode.YELLOW)
        return FileGenerator(problem_info=problem_info, is_design=False, function_signature=func_sig)

    def _inject_official_examples(self, problem_info: Any, problem_data: Any) -> None:
        """把官方 examples 注入 test 文件，优先用 LLM 翻译成可编译 body。"""
        official = extract_examples(problem_data.content or "")
        if not official:
            return

        _, _, test_path = FileGenerator(problem_info)._get_file_paths()
        try:
            content = test_path.read_text(encoding="utf-8")
        except Exception as e:
            log_with_time(f"⚠️ 读取 scaffold test 文件失败，跳过 example 注入: {e}", ColorCode.YELLOW)
            return

        marker = "INSTANTIATE_TEST_SUITE_P"
        insert_at = content.find(marker)
        if insert_at < 0:
            log_with_time("⚠️ scaffold test 文件里没找到 INSTANTIATE_TEST_SUITE_P，跳过 example 注入", ColorCode.YELLOW)
            return

        class_base = "".join(word.capitalize() for word in problem_info.slug.split("-"))
        translations = self._translate(problem_data, class_base, official)

        stubs = "\n".join(
            _render_stub(class_base, ex, body=translations.get(ex["index"]))
            for ex in official
        )
        test_path.write_text(content[:insert_at] + stubs + "\n\n" + content[insert_at:], encoding="utf-8")

        filled = sum(1 for ex in official if ex["index"] in translations)
        if filled == len(official):
            log_with_time(f"📎 已注入 {filled} 个 OfficialExampleN，全部翻译到可编译 body", ColorCode.CYAN)
        else:
            log_with_time(
                f"📎 已注入 {len(official)} 个 OfficialExampleN，"
                f"{filled} 个已翻译、{len(official) - filled} 个留 TODO 占位",
                ColorCode.CYAN,
            )

    def _translate(
        self, problem_data: Any, class_base: str, official: List[Dict[str, Any]]
    ) -> Dict[int, str]:
        code_template = problem_data.get_cpp_code_template() or ""
        try:
            signature = SignatureParser.extract_from_code_template(code_template) if code_template else None
        except Exception:
            signature = None
        if not signature:
            return {}
        try:
            return translate_examples_to_cpp(
                self._client,
                self._provider,
                solution_class_name=f"{class_base}Solution",
                function_signature=signature,
                examples=official,
            )
        except Exception as e:
            log_with_time(f"⚠️ example 翻译调用失败，全部用 TODO 兜底: {e}", ColorCode.YELLOW)
            return {}


def _read_file(path: Path) -> str:
    try:
        return path.read_text(encoding="utf-8")
    except Exception as e:
        return f"<读取失败: {e}>"


def _render_stub(class_base: str, example: Dict[str, Any], body: Optional[str] = None) -> str:
    idx = example.get("index", 1)
    input_line = example.get("input", "").replace("\n", " ").strip()
    output_line = example.get("output", "").replace("\n", " ").strip()
    if body is None:
        body_text = (
            "  // TODO: 用上面 Input 构造 C++ 变量，用 Output 作为 expected，调用 solution.<method>(...)\n"
            "  // 类型从 header 的 Func 签名推断。禁止删除此函数或修改 Input/Output 注释。\n"
        )
    else:
        body_text = body if body.endswith("\n") else body + "\n"
    return (
        f"// ===== Official Example {idx} (from LeetCode) =====\n"
        f"// Input:  {input_line}\n"
        f"// Output: {output_line}\n"
        f"TEST_P({class_base}Test, OfficialExample{idx}) {{\n"
        f"{body_text}"
        f"}}\n"
    )
