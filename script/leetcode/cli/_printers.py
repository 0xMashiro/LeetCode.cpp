#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CLI 共享的着色打印 helper。"""

import sys

from script.leetcode.utils import ColorCode, color_text


def error(message: str) -> None:
    print(f"{color_text('错误:', ColorCode.RED.value)} {message}", file=sys.stderr)


def success(message: str) -> None:
    print(color_text(f"✓ {message}", ColorCode.GREEN.value))


def info(message: str) -> None:
    print(color_text(f"ℹ {message}", ColorCode.BLUE.value))


def warning(message: str) -> None:
    print(color_text(f"⚠ {message}", ColorCode.YELLOW.value))
