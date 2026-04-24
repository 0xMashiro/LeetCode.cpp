#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`fetch_problem_metadata` 工具：抓题目详情、装配面向模型的上下文，附缓存。

重复 fetch 同一题返回精简"cached=True"响应——flash 在没读懂时会盲目重 fetch，
这条缓存把白烧的轮次切掉。缓存 dict 公开给外部，让 `file_ops` 的 extra-test
守卫能直接读"官方 examples 数"做校验。
"""

from pathlib import Path
from typing import Any, Dict, Optional

from script.leetcode.ai.tools._utils import class_name_from_slug, read_file
from script.leetcode.ai.tools.description import extract_examples, html_to_markdown
from script.leetcode.config import ExampleProblems, ProjectPaths
from script.leetcode.services import SignatureParser


_FRAMEWORK_PATHS = {
    "solution_base": "include/leetcode/solution.hpp",
    "tree_utils": "include/leetcode/utils/tree.h",
    "linked_list_utils": "include/leetcode/utils/linked-list.h",
}


class MetadataFetcher:
    def __init__(self, repository: Any, cache: Dict[int, Dict[str, Any]]):
        self._repo = repository
        self._cache = cache

    def fetch(self, problem_id: int) -> Dict[str, Any]:
        if problem_id in self._cache:
            return self._cached_response(problem_id)
        try:
            result = self._build(problem_id)
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}
        if result.get("is_successful"):
            self._cache[problem_id] = result
        return result

    def _build(self, problem_id: int) -> Dict[str, Any]:
        """装配面向模型的题目元信息。

        字段顺序经过调优：`examples` + `description` 放最前，让 flash 注意力落在
        解题真正需要的两样东西上；HTML 原文不再回传（已被 markdown 覆盖）。
        """
        problem_data = self._repo.get_detail_by_id(problem_id, include_code=True)
        problem_info = self._repo.get_by_id(problem_id)

        code_template = problem_data.get_cpp_code_template()
        signature = (
            SignatureParser.extract_from_code_template(code_template) if code_template else None
        )

        raw_content = problem_data.content or ""
        problem_examples = extract_examples(raw_content)
        description = html_to_markdown(raw_content)

        class_base = class_name_from_slug(problem_info.slug)

        return {
            "is_successful": True,
            "problem_id": problem_id,
            "title": problem_data.title,
            "slug": problem_data.slug,
            "difficulty": problem_data.difficulty,
            "url": f"https://leetcode.com/problems/{problem_data.slug}/",
            "examples": problem_examples,
            "description": description,
            "function_signature": signature,
            "code_template": code_template,
            "is_design": self._repo.is_design_problem(problem_id),
            "solution_class_name": f"{class_base}Solution",
            "solution_class_base": class_base,
            "test_class_name": f"{class_base}Test",
            "namespace": f"problem_{problem_id}",
            "framework_apis": _load_framework_apis(code_template),
            **_load_examples(),
        }

    def _cached_response(self, problem_id: int) -> Dict[str, Any]:
        cached = self._cache[problem_id]
        return {
            "is_successful": True,
            "cached": True,
            "problem_id": problem_id,
            "title": cached.get("title"),
            "slug": cached.get("slug"),
            "hint": (
                "本次返回的数据与上一次 fetch_problem_metadata 完全相同，请直接从历史消息中"
                "提取 examples 和 description；重复 fetch 不会带来新信息，只会浪费轮次。"
            ),
            "examples": cached.get("examples"),
            "description": cached.get("description"),
        }


def _load_framework_apis(code_template: Optional[str]) -> Dict[str, str]:
    """solution.hpp 一定给；tree.h / linked-list.h 仅在模板里用到才给，避免刷屏。"""
    apis: Dict[str, str] = {
        "solution_base": read_file(Path(_FRAMEWORK_PATHS["solution_base"])),
    }
    template = code_template or ""
    if "TreeNode" in template:
        apis["tree_utils"] = read_file(Path(_FRAMEWORK_PATHS["tree_utils"]))
    if "ListNode" in template:
        apis["linked_list_utils"] = read_file(Path(_FRAMEWORK_PATHS["linked_list_utils"]))
    return apis


def _load_examples() -> Dict[str, Any]:
    ordinary = _read_example(ExampleProblems.ORDINARY_SLUG)
    design = _read_example(ExampleProblems.DESIGN_SLUG)
    return {
        "example_ordinary": {
            **ordinary,
            "description": "普通题目示例（Two Sum - 题目 ID 1）：使用 SolutionBase 模式，支持多策略实现",
        },
        "example_design": {
            **design,
            "description": "设计类题目示例（LRU Cache - 题目 ID 146）：直接实现类方法，不使用 SolutionBase",
        },
    }


def _read_example(slug: str) -> Dict[str, str]:
    return {
        "header": read_file(Path(f"{ProjectPaths.INCLUDE_PROBLEMS}/{slug}.h")),
        "source": read_file(Path(f"{ProjectPaths.SRC_PROBLEMS}/{slug}.cpp")),
        "test": read_file(Path(f"{ProjectPaths.TEST_PROBLEMS}/{slug}.cpp")),
    }
