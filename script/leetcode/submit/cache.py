#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""LeetCode 提交格式 AI 翻译的内容寻址缓存。

源码没变时复用上次翻译（单次 ~25s → 0s）。命中条件:
  (slug, solution_num, sha256(source_content)) 三元组一致。
LeetCode 返回 Compile Error 时调用 ``invalidate`` 丢弃缓存条目，强制重译。
"""

import hashlib
import re
from pathlib import Path
from typing import Callable, Optional

from script.leetcode.utils import ColorCode, log_with_time

_CACHE_DIR = Path(".leetcode-cache/submit")

_BLOCK_COMMENT = re.compile(r"/\*.*?\*/", re.DOTALL)
_LINE_COMMENT = re.compile(r"//[^\n]*")


def _normalize(source: str) -> str:
    """归一化后再 hash：注释 / 空白变化不会触发重译。"""
    stripped = _BLOCK_COMMENT.sub("", source)
    stripped = _LINE_COMMENT.sub("", stripped)
    # 折叠所有连续空白为单个空格，消除缩进 / 空行差异
    return " ".join(stripped.split())


def _cache_key(slug: str, solution_num: int, source_content: str) -> str:
    h = hashlib.sha256(_normalize(source_content).encode("utf-8")).hexdigest()[:12]
    return f"{slug}_n{solution_num}_{h}"


def _cache_path(key: str) -> Path:
    return _CACHE_DIR / f"{key}.cpp"


def get_or_translate(
    slug: str,
    solution_num: int,
    source_content: str,
    translate_fn: Callable[[], Optional[str]],
) -> Optional[str]:
    _CACHE_DIR.mkdir(parents=True, exist_ok=True)
    key = _cache_key(slug, solution_num, source_content)
    path = _cache_path(key)
    if path.exists():
        log_with_time(f"💾 翻译缓存命中: {path.name}", ColorCode.CYAN)
        return path.read_text(encoding="utf-8")

    translated = translate_fn()
    if translated:
        path.write_text(translated, encoding="utf-8")
    return translated


def invalidate(slug: str, solution_num: int, source_content: str) -> None:
    key = _cache_key(slug, solution_num, source_content)
    path = _cache_path(key)
    if path.exists():
        path.unlink()
        log_with_time(f"🗑️  清除翻译缓存: {path.name}", ColorCode.YELLOW)
