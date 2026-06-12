#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""多策略提交聚合 + verify_all_strategies flag 解析。"""

import os
import types
import unittest
from unittest.mock import MagicMock, patch

from script.leetcode.ai.solver import AISolver
from script.leetcode.submit.classifier import SubmissionClassifier


def _r(status: str, **extra) -> types.SimpleNamespace:
    return types.SimpleNamespace(
        status=status,
        status_code=0,
        total_test_cases=extra.get("total", 0),
        passed_test_cases=extra.get("passed", 0),
        failed_test_case=extra.get("failed", None),
        runtime_ms=None,
        memory_mb=None,
        error_message=extra.get("error_message", None),
    )


def _fake_submitter(results_map):
    """依次让 submit_all_solutions 返回 results_map（三元组：n, result, expected）。"""
    sub = MagicMock()
    sub.submit_all_solutions = MagicMock(return_value=results_map)
    return sub


def _triple(n, status, expected="Accepted", **extra):
    return (n, _r(status, **extra), expected)


class TestSubmitAllAndClassify(unittest.TestCase):
    def setUp(self) -> None:
        os.environ["LEETCODE_COOKIE"] = "dummy"
        self.addCleanup(lambda: os.environ.pop("LEETCODE_COOKIE", None))

    def test_all_accepted_returns_success(self) -> None:
        results = [_triple(1, "Accepted"), _triple(2, "Accepted")]
        svc = SubmissionClassifier(submitter_factory=lambda: _fake_submitter(results))
        outcome = svc.submit_all_and_classify(42)
        self.assertTrue(outcome.should_continue)
        self.assertTrue(outcome.accepted)
        self.assertIsNone(outcome.result)

    def test_expected_tle_actual_tle_counts_as_pass(self) -> None:
        """暴力解标了 @expected: TLE，真 TLE → 符合预期，整体视为通过。"""
        results = [
            _triple(1, "Time Limit Exceeded", expected="Time Limit Exceeded"),
            _triple(2, "Accepted"),
        ]
        svc = SubmissionClassifier(submitter_factory=lambda: _fake_submitter(results))
        outcome = svc.submit_all_and_classify(42)
        self.assertTrue(outcome.accepted)

    def test_expected_tle_actual_accepted_is_mismatch(self) -> None:
        """标了预期 TLE 但真 AC → mismatch，失败归类（模型可能需要移除 @expected 标记）。"""
        results = [_triple(1, "Accepted", expected="Time Limit Exceeded")]
        svc = SubmissionClassifier(submitter_factory=lambda: _fake_submitter(results))
        outcome = svc.submit_all_and_classify(42)
        self.assertFalse(outcome.accepted)
        # AC 不在 CODE_FAILURE_STATUSES 里 → infra_error 分支（不阻断）
        self.assertEqual(outcome.skip_reason, "infra_error")

    def test_one_wa_surfaces_code_failure(self) -> None:
        results = [
            _triple(1, "Accepted"),
            _triple(2, "Wrong Answer", passed=3, total=10),
            _triple(3, "Accepted"),
        ]
        svc = SubmissionClassifier(submitter_factory=lambda: _fake_submitter(results))
        outcome = svc.submit_all_and_classify(42)
        self.assertFalse(outcome.should_continue)
        self.assertFalse(outcome.accepted)
        self.assertEqual(outcome.result.status, "Wrong Answer")
        # 汇总信息写进 error_message：格式是 "solutionN: expected=X actual=Y"
        self.assertIn("solution1: expected=Accepted actual=Accepted", outcome.result.error_message)
        self.assertIn("solution2: expected=Accepted actual=Wrong Answer", outcome.result.error_message)

    def test_all_infra_failures_treated_as_skip(self) -> None:
        results = [_triple(1, "Error"), _triple(2, "Error")]
        svc = SubmissionClassifier(submitter_factory=lambda: _fake_submitter(results))
        outcome = svc.submit_all_and_classify(42)
        self.assertTrue(outcome.should_continue)
        self.assertIsNone(outcome.accepted)
        self.assertEqual(outcome.skip_reason, "infra_error")

    def test_no_problem_id_is_hard_error(self) -> None:
        svc = SubmissionClassifier(submitter_factory=MagicMock())
        outcome = svc.submit_all_and_classify(None)
        self.assertFalse(outcome.should_continue)


class TestVerifyAllStrategiesFlagResolution(unittest.TestCase):
    def _instantiate(self, env: dict, **kwargs) -> AISolver:
        with patch.dict(os.environ, env, clear=True):
            with patch("script.leetcode.ai.solver.settings.load_project_env", lambda: None):
                with patch("script.leetcode.ai.solver.settings.require_api_key", lambda provider: "dummy"):
                    with patch("script.leetcode.ai.solver.AIApiClient"):
                        with patch("script.leetcode.ai.solver.ProblemRepository"):
                            return AISolver(**kwargs)

    def test_default_off(self) -> None:
        solver = self._instantiate({"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x"})
        self.assertFalse(solver.verify_all_strategies)

    def test_env_true_enables(self) -> None:
        solver = self._instantiate({
            "AI_PROVIDER": "moonshot",
            "MOONSHOT_API_KEY": "x",
            "AI_SOLVER_VERIFY_ALL_STRATEGIES": "true",
        })
        self.assertTrue(solver.verify_all_strategies)

    def test_explicit_true_overrides_env_false(self) -> None:
        solver = self._instantiate(
            {"AI_PROVIDER": "moonshot", "MOONSHOT_API_KEY": "x",
             "AI_SOLVER_VERIFY_ALL_STRATEGIES": "false"},
            verify_all_strategies=True,
        )
        self.assertTrue(solver.verify_all_strategies)


if __name__ == "__main__":
    unittest.main()
