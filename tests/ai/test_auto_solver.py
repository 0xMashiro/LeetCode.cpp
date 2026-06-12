#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import io
import unittest
from unittest.mock import patch

from script.leetcode.ai.auto_solver import AutoSolver


class _FakeProcess:
    def __init__(self, stdout_lines):
        self.stdout = iter(stdout_lines)
        self.stderr = io.StringIO("")
        self.returncode = 1

    def wait(self, timeout):
        return self.returncode

    def kill(self):
        pass


class TestAutoSolverLongRun(unittest.TestCase):
    def test_failed_problem_is_skipped_for_current_run(self) -> None:
        solver = AutoSolver(max_retries=1, retry_delay=0)
        solver._pick_problem = lambda: 123

        with patch.object(AutoSolver, "_get_solved_count", return_value=10):
            with patch(
                "script.leetcode.ai.auto_solver.subprocess.Popen",
                return_value=_FakeProcess(["error: boom\n"]),
            ):
                success, error = solver.run_once()

        self.assertFalse(success)
        self.assertEqual(error, "compile_error")
        self.assertEqual(solver.failed_problem_ids, {123})

    def test_pick_problem_passes_session_failures_to_pool(self) -> None:
        class _Pool:
            def get_random(self, exclude_ids):
                self.exclude_ids = exclude_ids
                return 456

        pool = _Pool()
        solver = AutoSolver()
        solver.failed_problem_ids = {123}

        with patch("script.leetcode.problem_pool.ProblemPool", return_value=pool):
            self.assertEqual(solver._pick_problem(), 456)

        self.assertEqual(pool.exclude_ids, {123})


if __name__ == "__main__":
    unittest.main()
