#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import types
import unittest
from unittest.mock import patch

from script.leetcode.ai import settings


class TestResolveBoolFlag(unittest.TestCase):
    def test_explicit_value_wins(self) -> None:
        with patch.dict(os.environ, {"FLAG": "false"}, clear=True):
            self.assertTrue(settings.resolve_bool_flag(True, "FLAG", default=False))

    def test_empty_env_uses_default(self) -> None:
        with patch.dict(os.environ, {"FLAG": ""}, clear=True):
            self.assertTrue(settings.resolve_bool_flag(None, "FLAG", default=True))

    def test_env_is_case_insensitive(self) -> None:
        with patch.dict(os.environ, {"FLAG": "TRUE"}, clear=True):
            self.assertTrue(settings.resolve_bool_flag(None, "FLAG", default=False))


class TestRequireApiKey(unittest.TestCase):
    def test_provider_key_wins(self) -> None:
        provider = types.SimpleNamespace(api_key_env=lambda: "MODEL_KEY")
        with patch.dict(os.environ, {"MODEL_KEY": "provider-key", "AI_API_KEY": "fallback"}, clear=True):
            self.assertEqual(settings.require_api_key(provider), "provider-key")

    def test_fallback_key_is_used(self) -> None:
        provider = types.SimpleNamespace(api_key_env=lambda: "MODEL_KEY")
        with patch.dict(os.environ, {"AI_API_KEY": "fallback"}, clear=True):
            self.assertEqual(settings.require_api_key(provider), "fallback")

    def test_missing_key_raises_clear_error(self) -> None:
        provider = types.SimpleNamespace(api_key_env=lambda: "MODEL_KEY")
        with patch.dict(os.environ, {}, clear=True):
            with self.assertRaisesRegex(ValueError, "MODEL_KEY"):
                settings.require_api_key(provider)


if __name__ == "__main__":
    unittest.main()
