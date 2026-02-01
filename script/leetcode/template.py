#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
模板定义（保留向后兼容）

注意：新的模板系统已在 services/template_renderer.py 中实现
此文件保留以兼容可能直接导入模板字符串的代码
"""

from script.leetcode.services.template_renderer import (
    INCLUDE_TEMPLATE,
    SOURCE_TEMPLATE,
    TEST_TEMPLATE,
    DESIGN_INCLUDE_TEMPLATE,
    DESIGN_SOURCE_TEMPLATE,
    DESIGN_TEST_TEMPLATE,
    SOLVED_PROBLEM_DOC_HEADER,
)

__all__ = [
    "INCLUDE_TEMPLATE",
    "SOURCE_TEMPLATE", 
    "TEST_TEMPLATE",
    "DESIGN_INCLUDE_TEMPLATE",
    "DESIGN_SOURCE_TEMPLATE",
    "DESIGN_TEST_TEMPLATE",
    "SOLVED_PROBLEM_DOC_HEADER",
]
