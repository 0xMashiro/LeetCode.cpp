#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest

from script.leetcode.api.repository import ProblemRepository
from script.leetcode.exceptions import ProblemNotFoundError
from script.leetcode.models import ProblemData


def make_problem_data(
    qid: str,
    fid: str,
    title: str,
    slug: str,
    difficulty: str = "Easy",
) -> ProblemData:
    return ProblemData(
        question_id=qid,
        question_frontend_id=fid,
        title=title,
        title_slug=slug,
        difficulty=difficulty,
        is_paid_only=False,
        content="",
        code_snippets=[{"langSlug": "cpp", "code": "class Solution {};"}],
        topic_tags=[],
    )


class FakeClient:
    def __init__(self):
        self.problem_by_id = make_problem_data("1", "1", "Two Sum", "two-sum")
        self.problem_by_slug = make_problem_data("2", "2", "Add Two Numbers", "add-two-numbers")
        self.all_problems = [
            make_problem_data("1", "1", "Two Sum", "two-sum"),
            make_problem_data("2", "2", "Add Two Numbers", "add-two-numbers"),
            make_problem_data("3", "3", "Add Digits", "add-digits"),
        ]
        self.daily = {"date": "2026-03-09", "question": {"questionFrontendId": "1"}}
        self.calls = []

    def get_problem_by_id(self, problem_id: int, include_code_snippets: bool = False):
        self.calls.append(("get_problem_by_id", problem_id, include_code_snippets))
        return self.problem_by_id

    def get_problem_by_slug(self, slug: str, include_code_snippets: bool = False):
        self.calls.append(("get_problem_by_slug", slug, include_code_snippets))
        return self.problem_by_slug

    def get_all_problems(self):
        self.calls.append(("get_all_problems",))
        return self.all_problems

    def is_design_problem(self, problem_id: int):
        self.calls.append(("is_design_problem", problem_id))
        return problem_id == 146

    def get_daily_challenge(self):
        self.calls.append(("get_daily_challenge",))
        return self.daily


class TestProblemRepository(unittest.TestCase):
    def setUp(self) -> None:
        self.client = FakeClient()
        self.repo = ProblemRepository(client=self.client)

    def test_get_by_id_maps_to_problem_info(self) -> None:
        p = self.repo.get_by_id(1)
        self.assertEqual(p.id, 1)
        self.assertEqual(p.title, "Two Sum")
        self.assertEqual(p.slug, "two-sum")

    def test_get_detail_by_id_forwards_include_code(self) -> None:
        data = self.repo.get_detail_by_id(1, include_code=True)
        self.assertEqual(data.slug, "two-sum")
        self.assertIn(("get_problem_by_id", 1, True), self.client.calls)

    def test_get_detail_by_slug_forwards_include_code(self) -> None:
        data = self.repo.get_detail_by_slug("add-two-numbers", include_code=True)
        self.assertEqual(data.slug, "add-two-numbers")
        self.assertIn(("get_problem_by_slug", "add-two-numbers", True), self.client.calls)

    def test_get_by_title_found(self) -> None:
        p = self.repo.get_by_title("Add Digits")
        self.assertEqual(p.slug, "add-digits")

    def test_get_by_title_not_found_raises(self) -> None:
        with self.assertRaises(ProblemNotFoundError):
            self.repo.get_by_title("No Such Problem")

    def test_find_by_slug_prefix(self) -> None:
        matches = self.repo.find_by_slug_prefix("add-")
        self.assertEqual(sorted(p.slug for p in matches), ["add-digits", "add-two-numbers"])

    def test_build_slug_map(self) -> None:
        slug_map = self.repo.build_slug_map()
        self.assertIn("two-sum", slug_map)
        self.assertEqual(slug_map["two-sum"].title, "Two Sum")

    def test_get_cpp_code_template(self) -> None:
        template = self.repo.get_cpp_code_template("add-two-numbers")
        self.assertEqual(template, "class Solution {};")
        self.assertIn(("get_problem_by_slug", "add-two-numbers", True), self.client.calls)

    def test_is_design_problem_and_daily(self) -> None:
        self.assertTrue(self.repo.is_design_problem(146))
        self.assertFalse(self.repo.is_design_problem(1))
        daily = self.repo.get_daily_challenge()
        self.assertEqual(daily["date"], "2026-03-09")


if __name__ == "__main__":
    unittest.main()
