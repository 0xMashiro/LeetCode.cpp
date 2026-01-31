#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 解题模块

使用方式:
    python -m script.leetcode.ai.solver [题目ID]
"""

# 延迟导入以避免循环导入问题
def __getattr__(name):
    if name == "AISolver":
        from script.leetcode.ai.solver import AISolver
        return AISolver
    raise AttributeError(f"module '{__name__}' has no attribute '{name}'")
