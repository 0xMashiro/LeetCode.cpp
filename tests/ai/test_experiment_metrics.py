#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ExperimentMetrics dataclass 与聚合器的基础测试。

重点：
  - 失败路径也要记录 rounds（旧实现只在 success 分支写，导致摘要里出现
    "对话轮数: 0 / API 调用次数: 12" 的矛盾）。
  - aggregate_metrics 能正确按 (provider, model, thinking) 分组。
"""

import json
import tempfile
import unittest
from dataclasses import asdict
from pathlib import Path

from script.leetcode.ai.aggregate_metrics import (
    _config_key,
    load_metrics,
    print_summary,
    write_csv,
)
from script.leetcode.ai.journal import ExperimentMetrics


class TestExperimentMetrics(unittest.TestCase):
    def test_default_fields(self) -> None:
        m = ExperimentMetrics(provider="deepseek", model="deepseek-v4-flash", thinking_enabled=False)
        self.assertEqual(m.rounds, 0)
        self.assertEqual(m.api_calls, 0)
        self.assertFalse(m.success)
        self.assertFalse(m.leetcode_passed)
        self.assertIsNone(m.failure_reason)

    def test_failure_path_captures_rounds_and_reason(self) -> None:
        """模拟失败路径也能记录 rounds 与 failure_reason"""
        m = ExperimentMetrics(provider="deepseek", model="deepseek-v4-pro", thinking_enabled=True)
        m.rounds = 5
        m.api_calls = 5
        m.failure_reason = "stream_error:stream_timeout:60s"
        m.success = False

        dumped = asdict(m)
        self.assertEqual(dumped["rounds"], 5)
        self.assertEqual(dumped["failure_reason"], "stream_error:stream_timeout:60s")
        self.assertFalse(dumped["success"])

    def test_to_dict_roundtrip(self) -> None:
        m = ExperimentMetrics(
            provider="deepseek",
            model="deepseek-v4-flash",
            thinking_enabled=False,
            problem_id=3,
            rounds=3,
            api_calls=3,
            total_api_time=42.0,
            total_solve_time=55.0,
            success=True,
            leetcode_passed=True,
        )
        dumped = m.to_dict()
        self.assertEqual(dumped["problem_id"], 3)
        self.assertEqual(dumped["rounds"], 3)
        self.assertTrue(dumped["success"])


class TestAggregateMetrics(unittest.TestCase):
    def _write_metric(self, tmp: Path, **overrides) -> None:
        base = {
            "provider": "deepseek",
            "model": "deepseek-v4-pro",
            "thinking_enabled": True,
            "problem_id": 1,
            "rounds": 3,
            "api_calls": 3,
            "total_api_time": 30.0,
            "total_solve_time": 45.0,
            "success": True,
            "leetcode_passed": True,
            "failure_reason": None,
        }
        base.update(overrides)
        fname = f"metrics_p{base['problem_id']}_{base['provider']}_{base['model']}_{'on' if base['thinking_enabled'] else 'off'}.json"
        (tmp / fname).write_text(json.dumps(base), encoding="utf-8")

    def test_config_key_distinguishes_think_on_off(self) -> None:
        on_key = _config_key({"provider": "deepseek", "model": "deepseek-v4-pro", "thinking_enabled": True})
        off_key = _config_key({"provider": "deepseek", "model": "deepseek-v4-pro", "thinking_enabled": False})
        self.assertNotEqual(on_key, off_key)
        self.assertIn("think-on", on_key)
        self.assertIn("think-off", off_key)

    def test_load_and_write_csv(self) -> None:
        with tempfile.TemporaryDirectory() as raw:
            tmp = Path(raw)
            self._write_metric(tmp, problem_id=1, thinking_enabled=True)
            self._write_metric(tmp, problem_id=3, thinking_enabled=False, success=False, rounds=7,
                               failure_reason="stream_error:stream_timeout:60s")
            records = load_metrics(tmp)
            self.assertEqual(len(records), 2)
            # Ensure failure path rounds survives
            failed = [r for r in records if not r["success"]][0]
            self.assertEqual(failed["rounds"], 7)
            self.assertIn("stream_error", failed["failure_reason"])

            csv_path = tmp / "summary.csv"
            write_csv(records, csv_path)
            content = csv_path.read_text(encoding="utf-8")
            self.assertIn("problem_id", content.splitlines()[0])
            self.assertIn("stream_error", content)

    def test_print_summary_empty(self) -> None:
        # Just make sure it doesn't throw on empty
        print_summary([])


if __name__ == "__main__":
    unittest.main()
