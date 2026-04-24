#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
对话守卫状态机测试。

测试 guard.should_abort 的三条判定：
  1. 文件被修改 → 计数器重置
  2. 连续 N 轮无文件修改 → 终止
  3. 同类错误签名连续 M 次出现 → 终止
"""

import unittest
from contextlib import ExitStack, contextmanager
from unittest.mock import patch

from script.leetcode.ai.guard import GuardState, should_abort
from script.leetcode.config import AIConfig


@contextmanager
def _override(**overrides):
    """临时覆盖 AIConfig 上的阈值。"""
    with ExitStack() as stack:
        for name, value in overrides.items():
            stack.enter_context(patch.object(AIConfig, name, value))
        yield


class TestGuardStateMachine(unittest.TestCase):
    def test_file_mutated_resets_counters(self) -> None:
        state = GuardState()
        state.no_file_change_rounds = 3
        state.repeat_error_signature_count = 2
        state.last_error_signature = "x"

        terminate = should_abort({"file_mutated": True, "error_signatures": []}, state)
        self.assertFalse(terminate)
        self.assertEqual(state.no_file_change_rounds, 0)
        self.assertEqual(state.repeat_error_signature_count, 0)
        self.assertIsNone(state.last_error_signature)

    def test_consecutive_no_file_change_triggers_termination(self) -> None:
        state = GuardState()
        with _override(MAX_NO_FILE_CHANGE_ROUNDS=3):
            terminate1 = should_abort(
                {"file_mutated": False, "error_signatures": []}, state
            )
            terminate2 = should_abort(
                {"file_mutated": False, "error_signatures": []}, state
            )
            terminate3 = should_abort(
                {"file_mutated": False, "error_signatures": []}, state
            )
        self.assertFalse(terminate1)
        self.assertFalse(terminate2)
        self.assertTrue(terminate3, "连续 3 轮无文件修改应触发终止")

    def test_repeated_error_signature_triggers_termination(self) -> None:
        state = GuardState()
        sig = "compile_and_test|编译错误|error: expected ';'"
        with _override(MAX_NO_FILE_CHANGE_ROUNDS=10, MAX_REPEAT_ERROR_SIGNATURE=3):
            should_abort({"file_mutated": False, "error_signatures": [sig]}, state)
            should_abort({"file_mutated": False, "error_signatures": [sig]}, state)
            terminate = should_abort(
                {"file_mutated": False, "error_signatures": [sig]}, state
            )
        self.assertTrue(terminate)

    def test_different_error_signatures_do_not_trigger_termination(self) -> None:
        state = GuardState()
        with _override(MAX_NO_FILE_CHANGE_ROUNDS=10, MAX_REPEAT_ERROR_SIGNATURE=3):
            for sig in ("err_a", "err_b", "err_c", "err_d"):
                terminate = should_abort(
                    {"file_mutated": False, "error_signatures": [sig]}, state
                )
                self.assertFalse(terminate, f"错误签名变化不应触发终止，当前 sig={sig}")


if __name__ == "__main__":
    unittest.main()
