#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""AISolver runtime configuration helpers."""

import os
from pathlib import Path
from typing import Optional

from dotenv import load_dotenv

from script.leetcode.config import AIProvider


def load_project_env() -> None:
    project_root = Path(__file__).parent.parent.parent.parent
    env_path = project_root / ".env"
    if env_path.exists():
        load_dotenv(dotenv_path=env_path)
    else:
        load_dotenv()


def resolve_bool_flag(
    explicit: Optional[bool], env_var: str, *, default: bool
) -> bool:
    """Resolve bool flag from explicit value, environment, then default."""
    if explicit is not None:
        return explicit
    raw = os.getenv(env_var)
    if raw is None or raw == "":
        return default
    return raw.lower() == "true"


def require_api_key(provider: AIProvider) -> str:
    env_var = provider.api_key_env()
    api_key = os.getenv(env_var) or os.getenv("AI_API_KEY")
    if not api_key:
        raise ValueError(
            f"请设置 {env_var}：\n"
            f"  1. 创建 .env 文件并添加 {env_var}=your_key\n"
            f"  2. 或设置环境变量: export {env_var}=your_key\n"
            f"  3. 或使用通用的 AI_API_KEY"
        )
    return api_key
