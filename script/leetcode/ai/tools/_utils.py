#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`tools/` 内部各模块共享的小 helper。"""

from pathlib import Path


def read_file(path: Path) -> str:
    """安全读文件；不存在 / 权限失败返回空串。"""
    try:
        return path.read_text(encoding="utf-8")
    except (FileNotFoundError, IOError):
        return ""


def class_name_from_slug(slug: str) -> str:
    """`two-sum` → `TwoSum`。"""
    return "".join(word.capitalize() for word in slug.split("-"))
