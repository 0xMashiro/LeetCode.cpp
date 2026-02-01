#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
纯配置模块，不导入其他业务模块以避免循环导入
"""

from dataclasses import dataclass
from enum import Enum
import os


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


@dataclass(frozen=True)
class AIProvider:
    """AI Provider 配置"""
    name: str
    base_url: str
    model: str
    use_reasoner: bool
    
    # 预定义的 Providers
    @classmethod
    def MOONSHOT(cls) -> "AIProvider":
        return cls(
            name="moonshot",
            base_url="https://api.moonshot.cn/v1",
            model="kimi-k2.5",
            use_reasoner=True
        )
    
    @classmethod
    def from_env(cls) -> "AIProvider":
        """从环境变量获取 Provider 配置"""
        provider = os.getenv("AI_PROVIDER", "moonshot").lower()
        
        if provider == "moonshot":
            return cls.MOONSHOT()
        else:
            # 自定义配置（支持其他 OpenAI 兼容的 API）
            return cls(
                name=provider,
                base_url=os.getenv("AI_BASE_URL", cls.MOONSHOT().base_url),
                model=os.getenv("AI_MODEL", cls.MOONSHOT().model),
                use_reasoner=os.getenv("AI_USE_REASONER", "true").lower() == "true"
            )


class FileTypeConfig(Enum):
    """文件类型配置（模板在 template.py 中定义，避免循环导入）"""
    HEADER = ("include/leetcode/problems/", "include/leetcode/problems/{}.h")
    SOURCE = ("src/leetcode/problems/", "src/leetcode/problems/{}.cpp")
    TEST = ("test/leetcode/problems/", "test/leetcode/problems/{}.cpp")
    
    def __init__(self, folder: str, placeholder: str):
        self.folder = folder
        self.placeholder = placeholder
