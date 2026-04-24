#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
纯配置模块，不导入其他业务模块以避免循环导入
"""

from dataclasses import dataclass
from enum import Enum
import os
from typing import Any, ClassVar, Dict, FrozenSet


@dataclass(frozen=True)
class ProjectPaths:
    """项目路径配置"""
    INCLUDE_PROBLEMS = "include/leetcode/problems"
    SRC_PROBLEMS = "src/leetcode/problems"
    TEST_PROBLEMS = "test/leetcode/problems"
    INCLUDE_UTILS = "include/leetcode/utils"
    SRC_UTILS = "src/leetcode/utils"
    CORE_HEADER = "include/leetcode/core.h"

    CACHE_DIR = ".leetcode-cache"


@dataclass(frozen=True)
class ExampleProblems:
    """示例题目"""
    ORDINARY_SLUG = "two-sum"  # 普通题目示例
    DESIGN_SLUG = "lru-cache"  # 设计类题目示例


@dataclass(frozen=True)
class APIConfig:
    """API 配置"""
    GRAPHQL_URL = "https://leetcode.com/graphql/"
    MAX_RETRIES = 3
    RETRY_DELAY_BASE = 2  # 秒
    REQUEST_TIMEOUT = 30  # 秒
    DEFAULT_PAGE_SIZE = 50


@dataclass(frozen=True)
class CacheConfig:
    """缓存配置"""
    EXPIRY_SECONDS = 24 * 60 * 60  # 24 小时
    DAILY_CHALLENGE_EXPIRY = 3600  # 1 小时


@dataclass(frozen=True)
class AIConfig:
    """AI 解题配置"""
    # 主解题循环最大轮数（包含代码生成、编译、本地测试）
    MAX_ITERATIONS = 20

    # LeetCode 提交相关配置
    LEETCODE_SUBMIT_MAX_RETRIES = 5  # LeetCode 提交失败后的最大重试次数
    LEETCODE_SUBMIT_TIMEOUT = 60     # 等待 LeetCode 判题结果的超时时间（秒）

    # 编译和测试超时
    BUILD_TIMEOUT = 120
    TEST_TIMEOUT = 60

    # 修复策略
    MAX_COMPILE_FIX_ATTEMPTS = 5  # 连续编译错误的最大修复次数，超过则放弃
    MAX_LEETCODE_FIX_ATTEMPTS = 3  # LeetCode 验证失败后的最大修复次数，超过则放弃

    # 对话守卫策略（防止无效循环和成本失控）
    # 时间层面不设"总 wall clock 上限",因为那是外部度量,和模型是否在工作无关 ——
    # pro+thinking 可能单轮推 10 分钟但一直在输出 token,硬斩会扔掉真·劳动。
    # 活性通过 STREAM_TIMEOUT_SECONDS(每次 API 调用)和 MAX_NO_FILE_CHANGE_ROUNDS
    # (整体进度)来保证;MAX_ITERATIONS 作为 hard cap 防止无限轮次。
    MAX_REPEAT_ERROR_SIGNATURE = 3  # 同类错误签名连续出现上限
    MAX_NO_FILE_CHANGE_ROUNDS = 6   # 连续无文件修改轮次上限(真·空转信号)

    # 流式响应守卫
    STREAM_TIMEOUT_SECONDS = 60     # 多少秒无新 chunk 判定为超时
    STREAM_MAX_CHUNKS = 100_000     # 单次调用最大 chunk 数，防止死循环

    # 日志截断
    OUTPUT_EXCERPT_CHARS = 1200     # 工具输出摘要最大字符
    OUTPUT_TAIL_CHARS = 600         # 回传模型时保留末尾字符数

    # 实验指标落盘目录（为空表示不落盘，由调用方设置）
    METRICS_DIR_ENV = "AI_SOLVER_METRICS_DIR"


@dataclass(frozen=True)
class AIProvider:
    """AI Provider 配置"""
    name: str
    base_url: str
    model: str
    use_reasoner: bool

    # 已知模型白名单：env/CLI 传入拼错的 model 名会在构造时就报错，
    # 而不是等到 API 调用被远端拒绝才暴露。新增模型时在此登记即可。
    KNOWN_MODELS: ClassVar[Dict[str, FrozenSet[str]]] = {
        "deepseek": frozenset({"deepseek-v4-flash", "deepseek-v4-pro"}),
        "moonshot": frozenset({"kimi-k2.6"}),
    }

    def __post_init__(self) -> None:
        known = self.KNOWN_MODELS.get(self.name)
        if known is not None and self.model not in known:
            raise ValueError(
                f"未知的 {self.name} 模型: {self.model!r}（已知: {sorted(known)}）。"
                f"如需新增，请在 script/leetcode/config.py 的 AIProvider.KNOWN_MODELS 登记。"
            )

    @classmethod
    def MOONSHOT(cls) -> "AIProvider":
        return cls(
            name="moonshot",
            base_url="https://api.moonshot.cn/v1",
            model=os.getenv("MOONSHOT_MODEL", "kimi-k2.6"),
            use_reasoner=True,
        )

    @classmethod
    def DEEPSEEK(cls) -> "AIProvider":
        return cls(
            name="deepseek",
            base_url="https://api.deepseek.com",
            model=os.getenv("DEEPSEEK_MODEL", "deepseek-v4-flash"),
            use_reasoner=os.getenv("DEEPSEEK_THINKING", "enabled").lower() == "enabled",
        )

    @classmethod
    def from_env(cls) -> "AIProvider":
        """从环境变量获取 Provider 配置"""
        provider = os.getenv("AI_PROVIDER", "moonshot").lower()

        if provider == "moonshot":
            return cls.MOONSHOT()
        if provider == "deepseek":
            return cls.DEEPSEEK()
        # 自定义配置（支持其他 OpenAI 兼容的 API）
        return cls(
            name=provider,
            base_url=os.getenv("AI_BASE_URL", cls.MOONSHOT().base_url),
            model=os.getenv("AI_MODEL", cls.MOONSHOT().model),
            use_reasoner=os.getenv("AI_USE_REASONER", "true").lower() == "true",
        )

    def api_key_env(self) -> str:
        """对应的 API Key 环境变量名"""
        env_var_map = {
            "moonshot": "MOONSHOT_API_KEY",
            "deepseek": "DEEPSEEK_API_KEY",
        }
        return env_var_map.get(self.name, f"{self.name.upper()}_API_KEY")

    def build_request_kwargs(self, allow_temperature: bool = False) -> Dict[str, Any]:
        """构造给 chat.completions.create 的 provider-specific 请求参数。

        集中封装各 provider 的思考模式 / temperature 差异，避免在调用点散落 if 分支。

        Args:
            allow_temperature: 非思考场景是否允许自定义 temperature（推理模型恒为 False）

        Returns:
            可直接展开到 create(**kwargs) 的参数字典。
        """
        kwargs: Dict[str, Any] = {}

        if self.name == "deepseek":
            # DeepSeek v4 系列：通过 extra_body 显式控制 thinking；未显式设置时默认 enabled
            if self.use_reasoner:
                kwargs["reasoning_effort"] = "high"
                kwargs["extra_body"] = {"thinking": {"type": "enabled"}}
            else:
                kwargs["extra_body"] = {"thinking": {"type": "disabled"}}
                # 非思考模式允许调用方自定义 temperature
                if allow_temperature:
                    kwargs["temperature"] = 0.2
            return kwargs

        if self.name == "moonshot":
            # Moonshot kimi 推理模型固定 temperature=1，不接受自定义
            return kwargs

        # 其他 provider：默认允许 temperature
        if allow_temperature and not self.use_reasoner:
            kwargs["temperature"] = 0.2
        return kwargs


class FileTypeConfig(Enum):
    """文件类型配置（模板在 template.py 中定义，避免循环导入）"""
    HEADER = ("include/leetcode/problems/", "include/leetcode/problems/{}.h")
    SOURCE = ("src/leetcode/problems/", "src/leetcode/problems/{}.cpp")
    TEST = ("test/leetcode/problems/", "test/leetcode/problems/{}.cpp")

    def __init__(self, folder: str, placeholder: str):
        self.folder = folder
        self.placeholder = placeholder
