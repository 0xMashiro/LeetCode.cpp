#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""leetcode_feedback.build 在 SelfAuthored 本地通过 + LeetCode WA 时的锚定警告。"""

import types
import unittest

from script.leetcode.submit import feedback as leetcode_feedback


def _wa(failed_case=None) -> types.SimpleNamespace:
    return types.SimpleNamespace(
        status="Wrong Answer",
        passed_test_cases=1,
        total_test_cases=2,
        failed_test_case=failed_case or {"input": "[1,2]", "actual": "3", "expected": "4"},
        error_message=None,
    )


class TestSelfAuthoredAnchoringWarning(unittest.TestCase):
    def test_warning_included_when_self_authored_and_wa(self) -> None:
        out = leetcode_feedback.build(_wa(), self_authored_tests_locally_passed=True)
        self.assertIn("SelfAuthored", out)
        self.assertIn("expected", out)

    def test_no_warning_without_self_authored(self) -> None:
        out = leetcode_feedback.build(_wa(), self_authored_tests_locally_passed=False)
        self.assertNotIn("SelfAuthored", out)

    def test_no_warning_on_non_wa_even_if_self_authored(self) -> None:
        tle = types.SimpleNamespace(status="Time Limit Exceeded", error_message=None)
        out = leetcode_feedback.build(tle, self_authored_tests_locally_passed=True)
        self.assertNotIn("SelfAuthored", out)


if __name__ == "__main__":
    unittest.main()
