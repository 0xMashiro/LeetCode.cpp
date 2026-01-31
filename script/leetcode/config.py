#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
纯配置模块，不导入其他业务模块以避免循环导入
"""

from dataclasses import dataclass
from enum import Enum


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
    MAX_ITERATIONS = 20
    BUILD_TIMEOUT = 120
    TEST_TIMEOUT = 60
    DEFAULT_BASE_URL = "https://api.moonshot.cn/v1"
    DEFAULT_MODEL = "kimi-k2.5"


class FileTypeConfig(Enum):
    """文件类型配置（模板在 template.py 中定义，避免循环导入）"""
    HEADER = ("include/leetcode/problems/", "include/leetcode/problems/{}.h")
    SOURCE = ("src/leetcode/problems/", "src/leetcode/problems/{}.cpp")
    TEST = ("test/leetcode/problems/", "test/leetcode/problems/{}.cpp")
    
    def __init__(self, folder: str, placeholder: str):
        self.folder = folder
        self.placeholder = placeholder
