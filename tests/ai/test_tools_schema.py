#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import unittest

from script.leetcode.ai import result_utils
from script.leetcode.ai.tools import ToolExecutor


class DummyRepository:
    pass


class TestToolResultSchema(unittest.TestCase):
    def setUp(self) -> None:
        self.executor = ToolExecutor(DummyRepository())

    def test_unknown_tool_is_normalized(self) -> None:
        result = self.executor.execute("not_exists_tool", {})
        self.assertEqual(result.get("status"), "error")
        self.assertFalse(result.get("is_successful"))
        self.assertEqual(result.get("error_type"), "tool_not_found")
        self.assertIn("message", result)
        self.assertIn("retryable", result)
        self.assertIn("artifacts", result)

    def test_generated_files_are_mapped_to_artifacts(self) -> None:
        normalized = result_utils.normalize(
            {
                "is_successful": True,
                "status_message": "ok",
                "generated_files": [
                    {"file_category": "source", "file_path": "src/a.cpp"},
                    {"file_category": "header", "file_path": "include/a.h"},
                ],
            },
            tool_name="create_or_update_file",
        )
        self.assertEqual(normalized.get("status"), "success")
        self.assertEqual(normalized.get("message"), "ok")
        artifacts = normalized.get("artifacts", [])
        self.assertEqual(len(artifacts), 2)
        self.assertEqual(artifacts[0].get("type"), "file")
        self.assertEqual(artifacts[0].get("category"), "source")
        self.assertEqual(artifacts[0].get("path"), "src/a.cpp")


if __name__ == "__main__":
    unittest.main()
