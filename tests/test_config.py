#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import unittest
from unittest.mock import patch

from script.leetcode.config import AIProvider


class TestAIProviderFromEnv(unittest.TestCase):
    def test_default_moonshot(self) -> None:
        with patch.dict(os.environ, {}, clear=True):
            provider = AIProvider.from_env()
        self.assertEqual(provider.name, "moonshot")
        self.assertTrue(provider.use_reasoner)

    def test_deepseek_default_thinking_enabled(self) -> None:
        with patch.dict(os.environ, {"AI_PROVIDER": "deepseek"}, clear=True):
            provider = AIProvider.from_env()
        self.assertEqual(provider.name, "deepseek")
        self.assertEqual(provider.model, "deepseek-v4-flash")
        self.assertTrue(provider.use_reasoner)

    def test_deepseek_thinking_disabled(self) -> None:
        with patch.dict(
            os.environ,
            {"AI_PROVIDER": "deepseek", "DEEPSEEK_THINKING": "disabled", "DEEPSEEK_MODEL": "deepseek-v4-flash"},
            clear=True,
        ):
            provider = AIProvider.from_env()
        self.assertEqual(provider.model, "deepseek-v4-flash")
        self.assertFalse(provider.use_reasoner)

    def test_api_key_env_map(self) -> None:
        self.assertEqual(AIProvider.MOONSHOT().api_key_env(), "MOONSHOT_API_KEY")
        self.assertEqual(AIProvider.DEEPSEEK().api_key_env(), "DEEPSEEK_API_KEY")
        custom = AIProvider(name="zhipu", base_url="", model="glm", use_reasoner=False)
        self.assertEqual(custom.api_key_env(), "ZHIPU_API_KEY")


class TestProviderBuildRequestKwargs(unittest.TestCase):
    """provider-specific 请求参数集中构造，消除 solver / submit 里的 if 硬分支"""

    def test_deepseek_thinking_on(self) -> None:
        provider = AIProvider(name="deepseek", base_url="", model="deepseek-v4-pro", use_reasoner=True)
        kwargs = provider.build_request_kwargs()
        self.assertEqual(kwargs.get("reasoning_effort"), "high")
        self.assertEqual(kwargs.get("extra_body"), {"thinking": {"type": "enabled"}})
        self.assertNotIn("temperature", kwargs)

    def test_deepseek_thinking_off_no_temperature(self) -> None:
        provider = AIProvider(name="deepseek", base_url="", model="deepseek-v4-flash", use_reasoner=False)
        kwargs = provider.build_request_kwargs(allow_temperature=False)
        self.assertEqual(kwargs.get("extra_body"), {"thinking": {"type": "disabled"}})
        self.assertNotIn("temperature", kwargs)
        self.assertNotIn("reasoning_effort", kwargs)

    def test_deepseek_thinking_off_with_temperature(self) -> None:
        """thinking 关闭时允许调用方自定义 temperature"""
        provider = AIProvider(name="deepseek", base_url="", model="deepseek-v4-flash", use_reasoner=False)
        kwargs = provider.build_request_kwargs(allow_temperature=True)
        self.assertEqual(kwargs.get("extra_body"), {"thinking": {"type": "disabled"}})
        self.assertEqual(kwargs.get("temperature"), 0.2)

    def test_moonshot_kimi_no_temperature(self) -> None:
        """Moonshot kimi 推理模型不接受自定义 temperature"""
        provider = AIProvider.MOONSHOT()
        kwargs = provider.build_request_kwargs(allow_temperature=True)
        self.assertNotIn("temperature", kwargs)
        self.assertNotIn("extra_body", kwargs)

    def test_custom_provider_allows_temperature_when_not_reasoning(self) -> None:
        provider = AIProvider(name="zhipu", base_url="", model="glm-4", use_reasoner=False)
        kwargs = provider.build_request_kwargs(allow_temperature=True)
        self.assertEqual(kwargs.get("temperature"), 0.2)

    def test_custom_provider_reasoning_no_temperature(self) -> None:
        provider = AIProvider(name="zhipu", base_url="", model="glm-4", use_reasoner=True)
        kwargs = provider.build_request_kwargs(allow_temperature=True)
        self.assertNotIn("temperature", kwargs)


if __name__ == "__main__":
    unittest.main()
