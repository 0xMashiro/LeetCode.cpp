#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
SubmissionOutcome.skip_reason 字段单测。

为什么新增：原实现把 "未开提交 / 没 cookie / infra 错" 都压成 accepted=None
+ should_continue=True，用户无法分辨根因。新增 skip_reason 三态：
  - "disabled"    : LEETCODE_SUBMIT_ENABLED 未开
  - "no_cookie"   : cookie 缺失
  - "infra_error" : 提交调用异常 / 非代码类错误
  - None          : 没 skip（Accepted 或 code failure）
"""

import os
import unittest
from unittest.mock import patch

from script.leetcode.submit.classifier import SubmissionClassifier


class FakeResult:
    def __init__(self, status: str, status_code: int, error_message: str | None = None):
        self.status = status
        self.status_code = status_code
        self.error_message = error_message


class FakeSubmitter:
    def __init__(self, result: FakeResult | None = None, exception: Exception | None = None):
        self._result = result
        self._exception = exception

    def submit_problem_with_result(self, problem_id: int, solution_num: int = 1):
        if self._exception:
            raise self._exception
        return self._result


class TestSubmissionSkipReason(unittest.TestCase):
    def _clean_env(self) -> dict:
        return {}

    def test_missing_cookie_sets_skip_reason_no_cookie(self) -> None:
        with patch.dict(os.environ, {}, clear=True):
            outcome = SubmissionClassifier().submit_and_classify(1)
        self.assertEqual(outcome.skip_reason, "no_cookie")
        self.assertTrue(outcome.should_continue)

    def test_submitter_exception_sets_skip_reason_infra_error(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(exception=RuntimeError("network timeout"))
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertEqual(outcome.skip_reason, "infra_error")
        self.assertTrue(outcome.should_continue)

    def test_non_code_status_sets_skip_reason_infra_error(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(
                result=FakeResult("Error", -1, "LEETCODE_COOKIE 无效或已过期")
            )
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertEqual(outcome.skip_reason, "infra_error")
        self.assertTrue(outcome.should_continue)

    def test_accepted_has_no_skip_reason(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(result=FakeResult("Accepted", 10))
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertIsNone(outcome.skip_reason)
        self.assertTrue(outcome.accepted)

    def test_code_failure_has_no_skip_reason(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(result=FakeResult("Wrong Answer", 11))
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertIsNone(outcome.skip_reason)
        self.assertFalse(outcome.accepted)


class TestJournalSkipReasonSummary(unittest.TestCase):
    """journal 摘要按 skip_reason 输出不同信息。"""

    def _make_journal(self, skip_reason):
        from script.leetcode.ai.journal import SolveJournal
        from script.leetcode.config import AIProvider
        provider = AIProvider(name="moonshot", base_url="u", model="kimi-k2.6", use_reasoner=True)
        j = SolveJournal(provider)
        j.set_skip_reason(skip_reason)
        return j

    def test_skip_reason_persisted_to_metrics(self) -> None:
        j = self._make_journal("disabled")
        self.assertEqual(j.metrics.skip_reason, "disabled")

    def test_skip_reason_none_default(self) -> None:
        from script.leetcode.ai.journal import ExperimentMetrics
        m = ExperimentMetrics(provider="moonshot", model="kimi-k2.6", thinking_enabled=True)
        self.assertIsNone(m.skip_reason)


if __name__ == "__main__":
    unittest.main()
