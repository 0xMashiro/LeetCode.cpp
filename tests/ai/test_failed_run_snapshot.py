#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json
import os
import tempfile
import unittest
from pathlib import Path

from script.leetcode.ai.scaffold import ScaffoldManager


class _ProblemInfo:
    id = 42
    slug = "snapshot-problem"
    title = "Snapshot Problem"


class _Repo:
    def get_by_id(self, problem_id: int):
        return _ProblemInfo()


class TestFailedRunSnapshot(unittest.TestCase):
    def test_snapshot_copies_generated_files_and_metrics(self) -> None:
        old_cwd = Path.cwd()
        with tempfile.TemporaryDirectory() as raw:
            tmp = Path(raw)
            os.chdir(tmp)
            try:
                header = tmp / "include/leetcode/problems/snapshot-problem.h"
                source = tmp / "src/leetcode/problems/snapshot-problem.cpp"
                test = tmp / "test/leetcode/problems/snapshot-problem.cpp"
                for path, content in (
                    (header, "header"),
                    (source, "source"),
                    (test, "test"),
                ):
                    path.parent.mkdir(parents=True, exist_ok=True)
                    path.write_text(content, encoding="utf-8")

                manager = ScaffoldManager(_Repo(), openai_client=None, provider=None)
                snapshot = manager.snapshot_failed_run(
                    42,
                    reason="compile/test failed",
                    metrics={"failure_reason": "compile_or_test_fix_exhausted"},
                )

                self.assertIsNotNone(snapshot)
                assert snapshot is not None
                self.assertTrue((snapshot / "include/leetcode/problems/snapshot-problem.h").exists())
                self.assertTrue((snapshot / "src/leetcode/problems/snapshot-problem.cpp").exists())
                self.assertTrue((snapshot / "test/leetcode/problems/snapshot-problem.cpp").exists())
                self.assertEqual(
                    json.loads((snapshot / "metrics.json").read_text(encoding="utf-8")),
                    {"failure_reason": "compile_or_test_fix_exhausted"},
                )
                self.assertIn("compile-test-failed", snapshot.name)
            finally:
                os.chdir(old_cwd)


if __name__ == "__main__":
    unittest.main()
