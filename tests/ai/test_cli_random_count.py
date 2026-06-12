#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest
from unittest.mock import patch

from script.leetcode.ai.cli import _solve_random


class _Solver:
    def __init__(self) -> None:
        self.solved = []

    def solve_problem(self, problem_id: int) -> None:
        self.solved.append(problem_id)


class _Pool:
    def __init__(self) -> None:
        self.ids = iter([101, 202, 303])

    def get_random(self, difficulty):
        return next(self.ids)


class TestRandomCount(unittest.TestCase):
    def test_solves_requested_number_of_random_problems(self) -> None:
        solver = _Solver()
        with patch("script.leetcode.problem_pool.ProblemPool", _Pool):
            _solve_random(solver, difficulty="Easy", count=3)
        self.assertEqual(solver.solved, [101, 202, 303])

    def test_rejects_non_positive_count(self) -> None:
        solver = _Solver()
        with self.assertRaisesRegex(ValueError, "random-count"):
            _solve_random(solver, difficulty=None, count=0)


if __name__ == "__main__":
    unittest.main()
