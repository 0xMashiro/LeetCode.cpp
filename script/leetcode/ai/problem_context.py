#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Problem context carried by one AISolver run."""

from dataclasses import dataclass
from typing import Any, Dict, List


@dataclass(frozen=True)
class ProblemContext:
    problem_id: int
    title: str
    slug: str
    difficulty: str
    tags: List[str]
    is_daily: bool

    @classmethod
    def from_question(
        cls, problem_id: int, question: Dict[str, Any], *, is_daily: bool
    ) -> "ProblemContext":
        return cls(
            problem_id=problem_id,
            title=question["title"],
            slug=question["titleSlug"],
            difficulty=question.get("difficulty", "Unknown"),
            tags=[tag["name"] for tag in question.get("topicTags", [])],
            is_daily=is_daily,
        )

    @property
    def title_prefix(self) -> str:
        return "📋 今日题目" if self.is_daily else "📋 题目"

    @property
    def solve_prefix(self) -> str:
        return "每日一题" if self.is_daily else "题目"

    @property
    def url(self) -> str:
        return f"https://leetcode.com/problems/{self.slug}/"
