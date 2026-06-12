#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import types
import unittest

from script.leetcode.ai.leetcode_gate import LeetCodeGate


class FakeClassifier:
    def __init__(self, outcome):
        self.outcome = outcome
        self.single_calls = []
        self.all_calls = []

    def submit_and_classify(self, problem_id):
        self.single_calls.append(problem_id)
        return self.outcome

    def submit_all_and_classify(self, problem_id):
        self.all_calls.append(problem_id)
        return self.outcome


def _outcome(**kwargs):
    base = {
        "should_continue": True,
        "accepted": True,
        "error_message": None,
        "result": None,
        "skip_reason": None,
    }
    base.update(kwargs)
    return types.SimpleNamespace(**base)


class TestLeetCodeGate(unittest.TestCase):
    def test_accepted_single_strategy_continues(self) -> None:
        classifier = FakeClassifier(_outcome())
        gate = LeetCodeGate(classifier)

        result = gate.submit(
            42,
            verify_all_strategies=False,
            self_authored_tests_locally_passed=lambda: False,
        )

        self.assertEqual(result, (True, True, None, None))
        self.assertEqual(classifier.single_calls, [42])
        self.assertEqual(classifier.all_calls, [])

    def test_all_strategy_path_is_selected(self) -> None:
        classifier = FakeClassifier(_outcome())
        gate = LeetCodeGate(classifier)

        gate.submit(
            42,
            verify_all_strategies=True,
            self_authored_tests_locally_passed=lambda: False,
        )

        self.assertEqual(classifier.all_calls, [42])

    def test_error_message_is_returned_as_feedback(self) -> None:
        gate = LeetCodeGate(FakeClassifier(_outcome(
            should_continue=False,
            accepted=False,
            error_message="compile failed",
        )))

        result = gate.submit(
            42,
            verify_all_strategies=False,
            self_authored_tests_locally_passed=lambda: False,
        )

        self.assertEqual(result, (False, False, "compile failed", None))

    def test_result_is_converted_to_feedback(self) -> None:
        submission = types.SimpleNamespace(
            status="Wrong Answer",
            passed_test_cases=1,
            total_test_cases=2,
            failed_test_case={"input": "[1,2]", "actual": "3", "expected": "4"},
            error_message=None,
        )
        gate = LeetCodeGate(FakeClassifier(_outcome(
            should_continue=False,
            accepted=False,
            result=submission,
        )))

        result = gate.submit(
            42,
            verify_all_strategies=False,
            self_authored_tests_locally_passed=lambda: True,
        )

        self.assertFalse(result[0])
        self.assertFalse(result[1])
        self.assertIn("Wrong Answer", result[2])
        self.assertIn("SelfAuthored", result[2])


if __name__ == "__main__":
    unittest.main()
