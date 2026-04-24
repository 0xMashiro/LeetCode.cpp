#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""从 LeetCode 代码模板里扒出"设计类"（LRU Cache 这种）的结构定义 + 格式化工具。"""

import re
from typing import List, Optional

from script.leetcode.models import DesignClassDefinition, DesignMethod


class DesignClassExtractor:
    @staticmethod
    def extract(code_template: str) -> Optional[DesignClassDefinition]:
        """匹配 `class Name {` 然后手动扫花括号处理嵌套，取出类体 + 方法列表。"""
        class_pattern = re.compile(r"class\s+(\w+)\s*\{", re.MULTILINE)
        match = class_pattern.search(code_template)
        if not match:
            return None

        class_name = match.group(1)
        start_pos = match.end()

        depth = 1
        pos = start_pos
        while pos < len(code_template) and depth > 0:
            if code_template[pos] == "{":
                depth += 1
            elif code_template[pos] == "}":
                depth -= 1
            pos += 1

        if depth != 0:
            return None

        class_body = code_template[start_pos : pos - 1]
        methods = DesignClassExtractor._extract_methods(class_body, class_name)

        return DesignClassDefinition(
            class_name=class_name,
            class_body=class_body.strip(),
            methods=methods,
        )

    @staticmethod
    def _extract_methods(class_body: str, class_name: str) -> List[DesignMethod]:
        methods = []
        method_pattern = re.compile(
            r"(?:(\w+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+)?"
            r"(\w+)\s*"
            r"\(([^)]*)\)\s*\{",
            re.MULTILINE,
        )
        for m in method_pattern.finditer(class_body):
            return_type_group = m.group(1)
            method_name = m.group(2).strip()
            params = m.group(3).strip()
            is_constructor = method_name == class_name
            return_type = "" if is_constructor else (return_type_group.strip() if return_type_group else "")
            methods.append(DesignMethod(
                return_type=return_type,
                name=method_name,
                params=params,
                is_constructor=is_constructor,
            ))
        return methods

    @staticmethod
    def format_method_declarations(class_def: DesignClassDefinition) -> str:
        """给头文件模板用的方法声明列表。"""
        declarations = []
        for m in class_def.methods:
            if m.is_constructor:
                declarations.append(f"  {class_def.class_name}({m.params});")
            else:
                declarations.append(f"  {m.return_type} {m.name}({m.params});")
        return "\n".join(declarations)

    @staticmethod
    def format_method_implementations(class_def: DesignClassDefinition) -> str:
        """给源文件模板用的方法实现骨架（带 TODO 默认返回）。"""
        implementations = []
        class_name = class_def.class_name
        for m in class_def.methods:
            if m.is_constructor:
                implementations.append(
                    f"{class_name}::{class_name}({m.params}) {{\n  // TODO: 实现构造函数\n}}"
                )
            else:
                default_return = "" if m.return_type == "void" else "return {};"
                implementations.append(
                    f"{m.return_type} {class_name}::{m.name}({m.params}) {{\n"
                    f"  // TODO: 实现方法\n"
                    f"  {default_return}\n"
                    f"}}"
                )
        return "\n\n".join(implementations)
