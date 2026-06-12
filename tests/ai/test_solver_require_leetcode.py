#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
`require_leetcode` 高层契约单测。

动机：
  LeetCode 提交开关本来埋在 SubmissionService 里（env var 二次 gate），
  调用方看不出一次运行到底做不做判题。现在把决策抬到 AISolver.__init__：
    - True  → 必须尝试提交；WA/RE/TLE 触发 fix loop
    - False → 本地编译通过即完成，根本不调 SubmissionService
    - None  → 兜底读 LEETCODE_SUBMIT_ENABLED，默认 True（以前默认 False）

  默认切 True 是因为"本地测试用例可能不全，LeetCode 判题才是真相"。
"""

import os
import types
import unittest
from unittest.mock import MagicMock, patch

from script.leetcode.ai.solver import AISolver


def _instantiate(env: dict, **kwargs) -> AISolver:
    """绕开 OpenAI / 仓库初始化，只验 flag 解析"""
    with patch.dict(os.environ, env, clear=True):
        with patch("script.leetcode.ai.solver.settings.load_project_env", lambda: None):
            with patch("script.leetcode.ai.solver.settings.require_api_key", lambda provider: "dummy"):
                with patch("script.leetcode.ai.solver.AIApiClient"):
                    with patch("script.leetcode.ai.solver.ProblemRepository"):
                        return AISolver(**kwargs)


class TestRequireLeetcodeResolution(unittest.TestCase):
    def test_default_true_when_env_unset(self) -> None:
        """新默认：env 不设时 require_leetcode=True（以前是 False）"""
        solver = _instantiate({"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x"})
        self.assertTrue(solver.require_leetcode)

    def test_env_false_sets_false(self) -> None:
        solver = _instantiate({
            "AI_PROVIDER": "moonshot",
            "MOONSHOT_API_KEY": "x",
            "LEETCODE_SUBMIT_ENABLED": "false",
        })
        self.assertFalse(solver.require_leetcode)

    def test_env_true_sets_true(self) -> None:
        solver = _instantiate({
            "AI_PROVIDER": "moonshot",
            "MOONSHOT_API_KEY": "x",
            "LEETCODE_SUBMIT_ENABLED": "true",
        })
        self.assertTrue(solver.require_leetcode)

    def test_env_case_insensitive(self) -> None:
        solver = _instantiate({
            "AI_PROVIDER": "moonshot",
            "MOONSHOT_API_KEY": "x",
            "LEETCODE_SUBMIT_ENABLED": "FALSE",
        })
        self.assertFalse(solver.require_leetcode)

    def test_explicit_true_overrides_env_false(self) -> None:
        solver = _instantiate(
            {
                "AI_PROVIDER": "moonshot",
                "MOONSHOT_API_KEY": "x",
                "LEETCODE_SUBMIT_ENABLED": "false",
            },
            require_leetcode=True,
        )
        self.assertTrue(solver.require_leetcode)

    def test_explicit_false_overrides_env_true(self) -> None:
        solver = _instantiate(
            {
                "AI_PROVIDER": "moonshot",
                "MOONSHOT_API_KEY": "x",
                "LEETCODE_SUBMIT_ENABLED": "true",
            },
            require_leetcode=False,
        )
        self.assertFalse(solver.require_leetcode)


class TestHandleCompletionGating(unittest.TestCase):
    """`_handle_completion` 根据 require_leetcode 决定是否调 SubmissionService。"""

    def _make_state(self, require_leetcode: bool) -> types.SimpleNamespace:
        journal = MagicMock()
        submit = MagicMock(return_value=(True, True, None, None))
        return types.SimpleNamespace(
            require_leetcode=require_leetcode,
            scaffold_mode=False,
            problem_id=42,
            _scaffold=types.SimpleNamespace(still_dirty=lambda pid: False),
            _write_report=lambda: None,
            _submit_to_leetcode=submit,
            _journal=journal,
            _leetcode_fix_count=0,
            messages=[],
        )

    def test_local_only_short_circuits_without_submit(self) -> None:
        state = self._make_state(require_leetcode=False)
        outcome = AISolver._handle_completion(state, iteration=0, round_start=0.0)
        self.assertIs(outcome, True)
        state._submit_to_leetcode.assert_not_called()
        state._journal.set_leetcode_passed.assert_called_once_with(None)
        state._journal.set_skip_reason.assert_called_once_with("local_only")

    def test_require_leetcode_calls_submit(self) -> None:
        state = self._make_state(require_leetcode=True)
        outcome = AISolver._handle_completion(state, iteration=0, round_start=0.0)
        self.assertIs(outcome, True)
        state._submit_to_leetcode.assert_called_once()


if __name__ == "__main__":
    unittest.main()
