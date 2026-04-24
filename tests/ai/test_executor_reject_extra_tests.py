#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
首次 create_or_update_file 时 test 文件的 TEST_P 数量校验。

动机:
  p3530 kimi-k2.6 运行中违反了 system prompt 的 "严禁自己在一开始构造额外的
  测试用例"。kimi 多加了 SingleNode/Chain 两个自编用例。如果自编的 expected
  算错，solver 会一路"修代码去迎合错用例"，是个典型毒性失败模式。

  这里在执行器层兜底：首次生成（三文件都不存在）时，统计 test 文件里的 TEST_P
  条数，与已缓存 metadata 里的官方 examples 数量比较。只有明确超出才拒绝；
  如果 metadata 还没拿到（模型跳过 fetch_problem_metadata 直接建文件，罕见
  但不该硬挂），保守放过。
"""

import os
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from script.leetcode.ai.tools.executor import ToolExecutor


class _FakeProblemInfo:
    def __init__(self, slug: str):
        self.slug = slug


class _FakeRepo:
    def __init__(self, slug: str = "foo-bar"):
        self._info = _FakeProblemInfo(slug)

    def get_by_id(self, pid: int):
        return self._info


def _prime_metadata_cache(executor: ToolExecutor, problem_id: int, example_count: int) -> None:
    """直接塞入 metadata 缓存，省掉完整 fetch 路径。"""
    examples = [{"index": i + 1, "input": "", "output": "", "explanation": ""}
                for i in range(example_count)]
    executor._metadata_cache[problem_id] = {"examples": examples, "title": "t", "slug": "s"}


def _write_three_files(
    tmp: Path, slug: str, test_body: str
) -> None:
    """写 scaffold 前不生效；这里用于后续 overwrite 场景准备初始文件。"""
    (tmp / f"{slug}.h").write_text("// header", encoding="utf-8")
    (tmp / f"{slug}.cpp").write_text("// source", encoding="utf-8")
    (tmp / f"test_{slug}.cpp").write_text(test_body, encoding="utf-8")


def _two_official_tests() -> str:
    return """#include "leetcode/problems/x.h"
TEST_P(XTest, Example1) { EXPECT_EQ(1, 1); }
TEST_P(XTest, Example2) { EXPECT_EQ(2, 2); }
"""


def _three_tests_with_extra() -> str:
    return """#include "leetcode/problems/x.h"
TEST_P(XTest, Example1) { EXPECT_EQ(1, 1); }
TEST_P(XTest, Example2) { EXPECT_EQ(2, 2); }
TEST_P(XTest, EdgeCaseMadeUp) { EXPECT_EQ(0, 0); }
"""


def _three_tests_with_self_authored() -> str:
    return """#include "leetcode/problems/x.h"
TEST_P(XTest, Example1) { EXPECT_EQ(1, 1); }
TEST_P(XTest, Example2) { EXPECT_EQ(2, 2); }
TEST_P(XTest, SelfAuthoredEmpty) { EXPECT_EQ(0, 0); }
"""


def _only_one_test() -> str:
    return """#include "leetcode/problems/x.h"
TEST_P(XTest, Example1) { EXPECT_EQ(1, 1); }
"""


class TestRejectExtraTestsOnFirstGeneration(unittest.TestCase):
    def _run_with_tmp_paths(self, executor: ToolExecutor, files: list, overwrite: bool = False):
        """把 ProjectPaths.* 指向 tmp 目录，避免污染真实项目。"""
        with tempfile.TemporaryDirectory() as raw:
            tmp = Path(raw)
            incl = tmp / "include"
            src = tmp / "src"
            tst = tmp / "test"
            for d in (incl, src, tst):
                d.mkdir(parents=True)
            with patch("script.leetcode.ai.tools.file_ops.ProjectPaths") as paths:
                paths.INCLUDE_PROBLEMS = str(incl)
                paths.SRC_PROBLEMS = str(src)
                paths.TEST_PROBLEMS = str(tst)
                return executor.execute(
                    "create_or_update_file",
                    {"problem_id": 42, "files": files, "overwrite_existing": overwrite},
                ), tmp

    def test_reject_when_extra_test_lacks_self_authored_prefix(self) -> None:
        """3 个 TEST_P 超出官方 2，第三个没 SelfAuthored 前缀 → 拒。"""
        executor = ToolExecutor(repository=_FakeRepo("x"))
        _prime_metadata_cache(executor, 42, example_count=2)

        result, _ = self._run_with_tmp_paths(
            executor,
            files=[
                {"file_category": "header", "content": "h"},
                {"file_category": "source", "content": "s"},
                {"file_category": "test", "content": _three_tests_with_extra()},
            ],
        )
        self.assertFalse(result["is_successful"])
        self.assertEqual(result.get("error_type"), "extra_test_cases_on_first_generation")
        self.assertIn("SelfAuthored", result.get("error_message", ""))
        self.assertIn("EdgeCaseMadeUp", result.get("error_message", ""))

    def test_allow_extra_test_with_self_authored_prefix(self) -> None:
        """超出官方数量但命名是 SelfAuthored* → 放行（锚定风险由 leetcode_feedback 接管）。"""
        executor = ToolExecutor(repository=_FakeRepo("x"))
        _prime_metadata_cache(executor, 42, example_count=2)

        result, _ = self._run_with_tmp_paths(
            executor,
            files=[
                {"file_category": "header", "content": "h"},
                {"file_category": "source", "content": "s"},
                {"file_category": "test", "content": _three_tests_with_self_authored()},
            ],
        )
        self.assertTrue(result["is_successful"], msg=result.get("error_message"))

    def test_allow_when_matching_official_count(self) -> None:
        executor = ToolExecutor(repository=_FakeRepo("x"))
        _prime_metadata_cache(executor, 42, example_count=2)

        result, _ = self._run_with_tmp_paths(
            executor,
            files=[
                {"file_category": "header", "content": "h"},
                {"file_category": "source", "content": "s"},
                {"file_category": "test", "content": _two_official_tests()},
            ],
        )
        self.assertTrue(result["is_successful"], msg=result.get("error_message"))

    def test_allow_when_fewer_than_official(self) -> None:
        """少于官方数量也放过（极端：模型只覆盖一个示例，自己选择保守）。
        严格性由 prompt 约束；兜底只关心 "多写了编的"。"""
        executor = ToolExecutor(repository=_FakeRepo("x"))
        _prime_metadata_cache(executor, 42, example_count=2)

        result, _ = self._run_with_tmp_paths(
            executor,
            files=[
                {"file_category": "header", "content": "h"},
                {"file_category": "source", "content": "s"},
                {"file_category": "test", "content": _only_one_test()},
            ],
        )
        self.assertTrue(result["is_successful"])

    def test_skip_check_when_metadata_not_cached(self) -> None:
        """metadata 还没 fetch（理论上不该发生）→ 兜底保守放过，不要硬挂"""
        executor = ToolExecutor(repository=_FakeRepo("x"))
        # 故意不 prime cache

        result, _ = self._run_with_tmp_paths(
            executor,
            files=[
                {"file_category": "header", "content": "h"},
                {"file_category": "source", "content": "s"},
                {"file_category": "test", "content": _three_tests_with_extra()},
            ],
        )
        self.assertTrue(result["is_successful"])

    def test_overwrite_path_not_affected(self) -> None:
        """非首次生成（overwrite）允许任意测试数量，包括追加 LeetCode 失败用例。"""
        executor = ToolExecutor(repository=_FakeRepo("x"))
        _prime_metadata_cache(executor, 42, example_count=2)

        # 先占位写三个文件
        with tempfile.TemporaryDirectory() as raw:
            tmp = Path(raw)
            incl = tmp / "include"
            src = tmp / "src"
            tst = tmp / "test"
            for d in (incl, src, tst):
                d.mkdir(parents=True)
            (incl / "x.h").write_text("old", encoding="utf-8")
            (src / "x.cpp").write_text("old", encoding="utf-8")
            (tst / "x.cpp").write_text("old", encoding="utf-8")
            with patch("script.leetcode.ai.tools.file_ops.ProjectPaths") as paths:
                paths.INCLUDE_PROBLEMS = str(incl)
                paths.SRC_PROBLEMS = str(src)
                paths.TEST_PROBLEMS = str(tst)
                result = executor.execute(
                    "create_or_update_file",
                    {
                        "problem_id": 42,
                        "files": [{"file_category": "test", "content": _three_tests_with_extra()}],
                        "overwrite_existing": True,
                    },
                )
        self.assertTrue(result["is_successful"])

    def test_no_test_file_submitted_still_blocks_for_missing_initial(self) -> None:
        """首次但没提交 test 文件 → 已有的 missing_initial_files 逻辑先拦下，不走 TEST_P 校验。"""
        executor = ToolExecutor(repository=_FakeRepo("x"))
        _prime_metadata_cache(executor, 42, example_count=2)

        result, _ = self._run_with_tmp_paths(
            executor,
            files=[
                {"file_category": "header", "content": "h"},
                {"file_category": "source", "content": "s"},
                # 没 test
            ],
        )
        self.assertFalse(result["is_successful"])
        self.assertEqual(result.get("error_type"), "missing_initial_files")


if __name__ == "__main__":
    unittest.main()
