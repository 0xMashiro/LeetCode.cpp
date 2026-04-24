#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""compile_and_test 成功后的短路逻辑单测（迁到 tool_round 模块后的版本）。"""

import unittest

from script.leetcode.ai.tool_round import should_short_circuit, update_summary


class TestShouldShortCircuit(unittest.TestCase):
    def test_short_circuit_when_compile_passed(self) -> None:
        summary = {"file_mutated": True, "error_signatures": [], "compile_passed": True}
        self.assertTrue(should_short_circuit(summary))

    def test_no_short_circuit_when_compile_failed(self) -> None:
        summary = {"file_mutated": True, "error_signatures": ["..."], "compile_passed": False}
        self.assertFalse(should_short_circuit(summary))

    def test_no_short_circuit_when_compile_not_called(self) -> None:
        summary = {"file_mutated": True, "error_signatures": []}
        self.assertFalse(should_short_circuit(summary))

    def test_no_short_circuit_when_compile_passed_but_file_not_mutated_yet(self) -> None:
        summary = {"file_mutated": False, "error_signatures": [], "compile_passed": True}
        self.assertTrue(should_short_circuit(summary))


class TestCompilePassedTracking(unittest.TestCase):
    def test_compile_and_test_success_sets_flag(self) -> None:
        summary = {"file_mutated": False, "error_signatures": []}
        update_summary(summary, "compile_and_test", {"is_successful": True, "message": "所有测试通过"})
        self.assertTrue(summary.get("compile_passed"))

    def test_compile_and_test_failure_leaves_flag_unset_or_false(self) -> None:
        summary = {"file_mutated": False, "error_signatures": []}
        update_summary(summary, "compile_and_test", {"is_successful": False, "error_type": "编译错误"})
        self.assertFalse(summary.get("compile_passed", False))

    def test_create_or_update_file_does_not_set_compile_flag(self) -> None:
        summary = {"file_mutated": False, "error_signatures": []}
        update_summary(summary, "create_or_update_file", {"is_successful": True})
        self.assertFalse(summary.get("compile_passed", False))


if __name__ == "__main__":
    unittest.main()
