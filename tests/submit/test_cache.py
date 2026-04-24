#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""翻译缓存：命中 / 失效 / hash 分流。"""

import tempfile
import unittest
from pathlib import Path
from unittest.mock import MagicMock, patch

from script.leetcode.submit import cache as translation_cache


class TestTranslationCache(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self._patch = patch.object(translation_cache, "_CACHE_DIR", Path(self._tmp.name))
        self._patch.start()
        self.addCleanup(self._patch.stop)

    def test_first_call_invokes_translator_and_caches(self) -> None:
        translator = MagicMock(return_value="translated code")
        out = translation_cache.get_or_translate("two-sum", 1, "source A", translator)
        self.assertEqual(out, "translated code")
        translator.assert_called_once()

    def test_second_call_with_same_inputs_hits_cache(self) -> None:
        translator = MagicMock(return_value="translated code")
        translation_cache.get_or_translate("two-sum", 1, "source A", translator)
        translator2 = MagicMock(return_value="should NOT be called")
        out = translation_cache.get_or_translate("two-sum", 1, "source A", translator2)
        self.assertEqual(out, "translated code")
        translator2.assert_not_called()

    def test_different_source_content_miss(self) -> None:
        translator1 = MagicMock(return_value="v1")
        translation_cache.get_or_translate("two-sum", 1, "source A", translator1)
        translator2 = MagicMock(return_value="v2")
        out = translation_cache.get_or_translate("two-sum", 1, "source B", translator2)
        self.assertEqual(out, "v2")
        translator2.assert_called_once()

    def test_different_solution_num_miss(self) -> None:
        translator1 = MagicMock(return_value="v1")
        translation_cache.get_or_translate("two-sum", 1, "source A", translator1)
        translator2 = MagicMock(return_value="v2")
        out = translation_cache.get_or_translate("two-sum", 2, "source A", translator2)
        self.assertEqual(out, "v2")
        translator2.assert_called_once()

    def test_invalidate_forces_retranslation(self) -> None:
        translator1 = MagicMock(return_value="bad translation")
        translation_cache.get_or_translate("two-sum", 1, "source A", translator1)
        translation_cache.invalidate("two-sum", 1, "source A")
        translator2 = MagicMock(return_value="fixed translation")
        out = translation_cache.get_or_translate("two-sum", 1, "source A", translator2)
        self.assertEqual(out, "fixed translation")
        translator2.assert_called_once()

    def test_comment_only_change_hits_cache(self) -> None:
        translator1 = MagicMock(return_value="v1")
        translation_cache.get_or_translate("x", 1, "int f() { return 1; }", translator1)
        translator2 = MagicMock(return_value="should not be called")
        source_with_comment = "int f() { return 1; }  // renamed helper"
        out = translation_cache.get_or_translate("x", 1, source_with_comment, translator2)
        self.assertEqual(out, "v1")
        translator2.assert_not_called()

    def test_reindent_only_change_hits_cache(self) -> None:
        """真实场景：代码格式化改了缩进 / 行间距，不触发重译。"""
        translator1 = MagicMock(return_value="v1")
        translation_cache.get_or_translate(
            "x", 1, "int f() {\n  return 1;\n}\n", translator1
        )
        translator2 = MagicMock(return_value="should not be called")
        reindented = "int f() {\n    return 1;\n}\n\n"
        out = translation_cache.get_or_translate("x", 1, reindented, translator2)
        self.assertEqual(out, "v1")
        translator2.assert_not_called()

    def test_block_comment_only_change_hits_cache(self) -> None:
        translator1 = MagicMock(return_value="v1")
        translation_cache.get_or_translate("x", 1, "int f() { return 1; }", translator1)
        translator2 = MagicMock(return_value="should not be called")
        with_block = "/* copyright */\nint f() { return 1; }"
        out = translation_cache.get_or_translate("x", 1, with_block, translator2)
        self.assertEqual(out, "v1")
        translator2.assert_not_called()

    def test_translator_returns_none_does_not_cache(self) -> None:
        translator = MagicMock(return_value=None)
        out = translation_cache.get_or_translate("two-sum", 1, "source A", translator)
        self.assertIsNone(out)
        # 下一次还应该触发翻译（没写入磁盘）
        translator2 = MagicMock(return_value="ok")
        out2 = translation_cache.get_or_translate("two-sum", 1, "source A", translator2)
        self.assertEqual(out2, "ok")
        translator2.assert_called_once()


if __name__ == "__main__":
    unittest.main()
