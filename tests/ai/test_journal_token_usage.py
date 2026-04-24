#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
journal token 累加字段单测。

动机:
  journal 之前只记 api_calls 和 total_api_time，没有 token 数。用户问 "140s 是
  短是长、是不是 reasoning 炸了" 时查不到。现在让每次 API 调用返回 usage 后
  调 journal.add_usage(prompt, completion)，最终写入 metrics JSON 供对比。
"""

import json
import os
import tempfile
import unittest
from pathlib import Path

from script.leetcode.ai.journal import ExperimentMetrics, SolveJournal
from script.leetcode.config import AIProvider


class TestTokenUsageAccumulation(unittest.TestCase):
    def setUp(self) -> None:
        provider = AIProvider(
            name="moonshot", base_url="u", model="kimi-k2.6", use_reasoner=True
        )
        self.journal = SolveJournal(provider)

    def test_default_tokens_zero(self) -> None:
        m = self.journal.metrics
        self.assertEqual(m.prompt_tokens, 0)
        self.assertEqual(m.completion_tokens, 0)
        self.assertEqual(m.total_tokens, 0)

    def test_add_usage_accumulates(self) -> None:
        self.journal.add_usage(prompt_tokens=100, completion_tokens=200)
        self.journal.add_usage(prompt_tokens=50, completion_tokens=75)
        m = self.journal.metrics
        self.assertEqual(m.prompt_tokens, 150)
        self.assertEqual(m.completion_tokens, 275)
        self.assertEqual(m.total_tokens, 425)

    def test_add_usage_none_values_ignored(self) -> None:
        """某些 provider 不返 usage —— 允许 None 而不挂。"""
        self.journal.add_usage(prompt_tokens=None, completion_tokens=50)
        self.journal.add_usage(prompt_tokens=10, completion_tokens=None)
        m = self.journal.metrics
        self.assertEqual(m.prompt_tokens, 10)
        self.assertEqual(m.completion_tokens, 50)
        self.assertEqual(m.total_tokens, 60)

    def test_metrics_dict_includes_tokens(self) -> None:
        self.journal.add_usage(prompt_tokens=42, completion_tokens=100)
        d = self.journal.metrics.to_dict()
        self.assertIn("prompt_tokens", d)
        self.assertIn("completion_tokens", d)
        self.assertIn("total_tokens", d)
        self.assertEqual(d["prompt_tokens"], 42)
        self.assertEqual(d["total_tokens"], 142)

    def test_persist_emits_tokens(self) -> None:
        """写盘 metrics JSON 里包含 token 三元组。"""
        self.journal.add_usage(prompt_tokens=1000, completion_tokens=500)
        with tempfile.TemporaryDirectory() as tmpdir:
            os.environ["AI_SOLVER_METRICS_DIR"] = tmpdir
            try:
                self.journal.persist_if_enabled(problem_id=1)
                files = list(Path(tmpdir).glob("metrics_*.json"))
                self.assertEqual(len(files), 1)
                payload = json.loads(files[0].read_text())
                self.assertEqual(payload["prompt_tokens"], 1000)
                self.assertEqual(payload["completion_tokens"], 500)
                self.assertEqual(payload["total_tokens"], 1500)
            finally:
                os.environ.pop("AI_SOLVER_METRICS_DIR", None)


class TestExperimentMetricsTokenFields(unittest.TestCase):
    def test_tokens_default_zero_not_none(self) -> None:
        """token 字段用 int 默认 0（而非 None），方便 CSV 聚合时直接相加。"""
        m = ExperimentMetrics(provider="x", model="y", thinking_enabled=False)
        self.assertEqual(m.prompt_tokens, 0)
        self.assertEqual(m.completion_tokens, 0)
        self.assertEqual(m.total_tokens, 0)


if __name__ == "__main__":
    unittest.main()
