#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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


class TestSubmissionService(unittest.TestCase):
    def setUp(self) -> None:
        self.service = SubmissionClassifier()

    def test_missing_problem_id_returns_error(self) -> None:
        outcome = self.service.submit_and_classify(None)
        self.assertFalse(outcome.should_continue)
        self.assertEqual(outcome.error_message, "无法获取题目 ID")

    def test_missing_cookie_is_non_blocking(self) -> None:
        with patch.dict(os.environ, {}, clear=True):
            outcome = self.service.submit_and_classify(1)
            self.assertTrue(outcome.should_continue)
            self.assertIsNone(outcome.result)
            self.assertIsNone(outcome.error_message)

    def test_accepted_is_non_blocking(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(result=FakeResult("Accepted", 10))
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertTrue(outcome.should_continue)
        self.assertIsNone(outcome.result)
        self.assertIsNone(outcome.error_message)

    def test_code_failure_is_blocking(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(result=FakeResult("Wrong Answer", 11))
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertFalse(outcome.should_continue)
        self.assertIsNotNone(outcome.result)
        self.assertEqual(outcome.result.status, "Wrong Answer")

    def test_infra_failure_is_non_blocking(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(
                result=FakeResult("Error", -1, "LEETCODE_COOKIE 无效或已过期")
            )
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertTrue(outcome.should_continue)
        self.assertIsNone(outcome.result)

    def test_submitter_exception_is_non_blocking(self) -> None:
        service = SubmissionClassifier(
            submitter_factory=lambda: FakeSubmitter(exception=RuntimeError("network timeout"))
        )
        with patch.dict(os.environ, {"LEETCODE_COOKIE": "dummy"}, clear=True):
            outcome = service.submit_and_classify(1)
        self.assertTrue(outcome.should_continue)
        self.assertIsNone(outcome.result)


if __name__ == "__main__":
    unittest.main()
