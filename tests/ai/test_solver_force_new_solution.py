#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
AI_SOLVER_FORCE_NEW_SOLUTION flag 单测。

覆盖 `.env.example` 里宣传的 "文件已存在时仍强制重解" 开关。实现前这个 flag
在代码里完全没被读过，表现为：删除 + 重跑才能让 solver 再次工作。
"""

import os
import types
import unittest
from unittest.mock import patch

from script.leetcode.ai.solver import AISolver


def _make_solver_like(
    force_new_solution: bool, has_solution: bool = True
) -> types.SimpleNamespace:
    """构造轻量 self，直接喂给 unbound method。依赖 force_new_solution + _scaffold.has_solution。"""
    return types.SimpleNamespace(
        force_new_solution=force_new_solution,
        _scaffold=types.SimpleNamespace(has_solution=lambda pid: has_solution),
    )


class TestShouldSkipAsAlreadySolved(unittest.TestCase):
    def test_skips_when_solution_exists_and_flag_off(self) -> None:
        state = _make_solver_like(force_new_solution=False)
        self.assertTrue(AISolver._should_skip_as_already_solved(state, 42))

    def test_does_not_skip_when_flag_on(self) -> None:
        state = _make_solver_like(force_new_solution=True)
        self.assertFalse(AISolver._should_skip_as_already_solved(state, 42))

    def test_does_not_skip_when_no_solution(self) -> None:
        state = _make_solver_like(force_new_solution=False, has_solution=False)
        self.assertFalse(AISolver._should_skip_as_already_solved(state, 42))


class TestForceNewSolutionEnv(unittest.TestCase):
    """__init__ 是否把 AI_SOLVER_FORCE_NEW_SOLUTION 正确读入属性。"""

    def _instantiate(self, env: dict) -> AISolver:
        # 绕开 load_dotenv 和 API key 校验，只验 flag 解析逻辑
        with patch.dict(os.environ, env, clear=True):
            with patch("script.leetcode.ai.solver.settings.load_project_env", lambda: None):
                with patch("script.leetcode.ai.solver.settings.require_api_key", lambda provider: "dummy"):
                    with patch("script.leetcode.ai.solver.AIApiClient"):
                        with patch("script.leetcode.ai.solver.ProblemRepository"):
                            return AISolver()

    def test_env_true_enables_flag(self) -> None:
        solver = self._instantiate({"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x",
                                    "AI_SOLVER_FORCE_NEW_SOLUTION": "true"})
        self.assertTrue(solver.force_new_solution)

    def test_env_false_disables_flag(self) -> None:
        solver = self._instantiate({"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x",
                                    "AI_SOLVER_FORCE_NEW_SOLUTION": "false"})
        self.assertFalse(solver.force_new_solution)

    def test_env_missing_defaults_off(self) -> None:
        solver = self._instantiate({"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x"})
        self.assertFalse(solver.force_new_solution)

    def test_env_case_insensitive(self) -> None:
        solver = self._instantiate({"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x",
                                    "AI_SOLVER_FORCE_NEW_SOLUTION": "TRUE"})
        self.assertTrue(solver.force_new_solution)

    def test_constructor_arg_overrides_env(self) -> None:
        """构造函数参数优先于环境变量，便于测试和 CLI 显式覆盖。"""
        with patch.dict(os.environ, {"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x",
                                      "AI_SOLVER_FORCE_NEW_SOLUTION": "true"}, clear=True):
            with patch("script.leetcode.ai.solver.settings.load_project_env", lambda: None):
                with patch("script.leetcode.ai.solver.settings.require_api_key", lambda provider: "dummy"):
                    with patch("script.leetcode.ai.solver.AIApiClient"):
                        with patch("script.leetcode.ai.solver.ProblemRepository"):
                            solver = AISolver(force_new_solution=False)
        self.assertFalse(solver.force_new_solution)


if __name__ == "__main__":
    unittest.main()
