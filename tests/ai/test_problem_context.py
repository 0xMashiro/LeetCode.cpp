#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest

from script.leetcode.ai.problem_context import ProblemContext


class TestProblemContext(unittest.TestCase):
    def test_from_question_normalizes_fields(self) -> None:
        context = ProblemContext.from_question(
            1,
            {
                "title": "Two Sum",
                "titleSlug": "two-sum",
                "difficulty": "Easy",
                "topicTags": [{"name": "Array"}, {"name": "Hash Table"}],
            },
            is_daily=True,
        )

        self.assertEqual(context.problem_id, 1)
        self.assertEqual(context.title, "Two Sum")
        self.assertEqual(context.slug, "two-sum")
        self.assertEqual(context.tags, ["Array", "Hash Table"])
        self.assertEqual(context.title_prefix, "📋 今日题目")
        self.assertEqual(context.solve_prefix, "每日一题")
        self.assertEqual(context.url, "https://leetcode.com/problems/two-sum/")

    def test_defaults_unknown_difficulty_and_empty_tags(self) -> None:
        context = ProblemContext.from_question(
            2,
            {"title": "Add Two Numbers", "titleSlug": "add-two-numbers"},
            is_daily=False,
        )

        self.assertEqual(context.difficulty, "Unknown")
        self.assertEqual(context.tags, [])
        self.assertEqual(context.title_prefix, "📋 题目")
        self.assertEqual(context.solve_prefix, "题目")


if __name__ == "__main__":
    unittest.main()
