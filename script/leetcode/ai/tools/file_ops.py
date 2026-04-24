#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""文件 CRUD 工具：`create_or_update_file` / `retrieve_file_content` / `append_test_case`。

`create_or_update_file` 在首次生成时多做两道守卫：必须三文件齐全 +
额外 TEST_P 必须 `SelfAuthored` 前缀——两条规则 JSON Schema 表达不了，
只能在执行器层兜底。
"""

import re
from pathlib import Path
from typing import Any, Dict, List, Optional

from script.leetcode.ai.tools._utils import class_name_from_slug
from script.leetcode.config import ProjectPaths


_REQUIRED_CATEGORIES = ("header", "source", "test")


def _category_paths(slug: str) -> Dict[str, Path]:
    return {
        "header": Path(f"{ProjectPaths.INCLUDE_PROBLEMS}/{slug}.h"),
        "source": Path(f"{ProjectPaths.SRC_PROBLEMS}/{slug}.cpp"),
        "test": Path(f"{ProjectPaths.TEST_PROBLEMS}/{slug}.cpp"),
    }


class FileOps:
    def __init__(self, repository: Any, metadata_cache: Dict[int, Dict[str, Any]]):
        self._repo = repository
        self._cache = metadata_cache

    def create_or_update(
        self,
        problem_id: int,
        files: list,
        overwrite_existing: bool = False,
    ) -> Dict[str, Any]:
        try:
            problem_info = self._repo.get_by_id(problem_id)
            paths = _category_paths(problem_info.slug)

            any_existing = any(p.exists() for p in paths.values())
            submitted = {f.get("file_category") for f in files}
            if not any_existing:
                missing = [c for c in _REQUIRED_CATEGORIES if c not in submitted]
                if missing:
                    return _missing_initial(missing)
                extra_check = self._check_extra_tests(problem_id, files)
                if extra_check is not None:
                    return extra_check

            generated: List[Dict[str, str]] = []
            errors: List[str] = []

            for entry in files:
                category = entry["file_category"]
                content = entry["content"]
                file_path = paths.get(category)
                if file_path is None:
                    errors.append(f"未知文件类型: {category}")
                    continue
                if file_path.exists() and not overwrite_existing:
                    errors.append(f"文件已存在: {file_path}")
                    continue
                file_path.parent.mkdir(parents=True, exist_ok=True)
                file_path.write_text(content, encoding="utf-8")
                generated.append({"file_category": category, "file_path": str(file_path)})

            if errors:
                return {
                    "is_successful": False,
                    "error_message": "; ".join(errors),
                    "generated_files": generated,
                }

            suffix = "（覆盖旧文件）" if overwrite_existing else ""
            return {
                "is_successful": True,
                "status_message": f"已生成 {len(generated)} 个文件{suffix}",
                "generated_files": generated,
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}

    def retrieve(self, problem_id: int, file_category: str) -> Dict[str, Any]:
        try:
            problem_info = self._repo.get_by_id(problem_id)
            file_path = _category_paths(problem_info.slug).get(file_category)
            if file_path is None:
                return {"is_successful": False, "error_message": f"未知文件类型: {file_category}"}
            if not file_path.exists():
                return {"is_successful": False, "error_message": f"文件不存在: {file_path}"}
            return {
                "is_successful": True,
                "file_category": file_category,
                "file_path": str(file_path),
                "content": file_path.read_text(encoding="utf-8"),
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}

    def append_test_case(
        self, problem_id: int, test_name: str, test_code: str
    ) -> Dict[str, Any]:
        try:
            problem_info = self._repo.get_by_id(problem_id)
            test_path = _category_paths(problem_info.slug)["test"]
            class_base = class_name_from_slug(problem_info.slug)

            if not test_path.exists():
                return {"is_successful": False, "error_message": f"测试文件不存在: {test_path}"}

            content = test_path.read_text(encoding="utf-8")
            match = re.search(r"INSTANTIATE_TEST_SUITE_P\(", content)
            if not match:
                return {
                    "is_successful": False,
                    "error_message": "无法找到 INSTANTIATE_TEST_SUITE_P 标记",
                }

            indented = "\n".join(
                "  " + line if line.strip() else line
                for line in test_code.strip().split("\n")
            )
            stub = (
                f"\n// LeetCode 失败用例: {test_name}\n"
                f"TEST_P({class_base}Test, {test_name}) {{\n"
                f"{indented}\n"
                f"}}\n"
            )
            insert_pos = match.start()
            test_path.write_text(content[:insert_pos] + stub + content[insert_pos:], encoding="utf-8")

            return {
                "is_successful": True,
                "message": f"测试用例 '{test_name}' 已添加到 {test_path}",
                "test_file": str(test_path),
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}

    def _check_extra_tests(self, problem_id: int, files: list) -> Optional[Dict[str, Any]]:
        """首次生成时兜底拦截未命名的自编 TEST_P。

        官方 examples 以内的 TEST_P 放行任意命名；超出数量的必须 `SelfAuthored` 前缀，
        否则拒——这条约束用于 leetcode_feedback 在 WA 时提醒模型"先核对 SelfAuthored
        的 expected 是否算错"。metadata 还没缓存时保守放过。
        """
        cached = self._cache.get(problem_id)
        if not cached:
            return None
        examples = cached.get("examples") or []
        expected_count = len(examples)
        if expected_count == 0:
            return None

        test_file = next((f for f in files if f.get("file_category") == "test"), None)
        if not test_file:
            return None

        test_content = test_file.get("content") or ""
        names = re.findall(r"\bTEST_P\s*\(\s*[^,]+,\s*([A-Za-z_][A-Za-z0-9_]*)", test_content)
        if len(names) <= expected_count:
            return None

        bad = [n for n in names[expected_count:] if not n.startswith("SelfAuthored")]
        if not bad:
            return None

        return {
            "is_successful": False,
            "error_type": "extra_test_cases_on_first_generation",
            "retryable": True,
            "error_message": (
                f"首次生成时超出官方 examples 数（{expected_count}）的自编 TEST_P 必须以 "
                f"`SelfAuthored` 开头，当前违规命名：{bad}。命名约束用于在 LeetCode 返回 WA 时"
                "提醒你先核对自编 expected 是否算错（否则会把修复方向带偏）。"
                "请改名（例如 SelfAuthoredEmptyInput、SelfAuthoredSingleNode）后重新提交。"
            ),
            "next_steps": [
                "把违规命名改成 SelfAuthored 前缀（必须保留官方 ExampleN TEST_P）",
                "重新调用 create_or_update_file 提交（overwrite_existing=true）",
            ],
        }


def _missing_initial(missing: list) -> Dict[str, Any]:
    return {
        "is_successful": False,
        "error_type": "missing_initial_files",
        "retryable": True,
        "error_message": (
            f"首次生成题目必须同时提交 header+source+test 三个文件，当前缺少: "
            f"{', '.join(missing)}。请把三份完整内容合并到一次 create_or_update_file "
            f"调用里（files 数组含 3 个条目）。"
        ),
        "next_steps": [
            "在同一次 create_or_update_file 调用中提交 header、source、test 三份文件",
            "参考 two-sum 的结构：header 声明类与函数签名，source 实现策略并调用 registerStrategy，test 使用 TestWithParam fixture 并以 INSTANTIATE_TEST_SUITE_P 结尾",
        ],
    }
