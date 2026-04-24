#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""C++ 函数签名解析：从 LeetCode 代码模板里扒出返回类型 / 名称 / 参数列表。

处理模板嵌套参数（`vector<pair<int,int>>`）；跳过构造/析构函数；返回结构化
`FunctionSignature`。
"""

import re
from typing import List, Optional

from script.leetcode.exceptions import SignatureError
from script.leetcode.models import FunctionParameter, FunctionSignature


class SignatureParser:
    SIGNATURE_PATTERN = re.compile(
        r"^\s*(\S+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+"  # 返回类型
        r"(\w+)\s*"  # 函数名
        r"\((.*)\)\s*$",  # 参数列表
        re.DOTALL,
    )

    @classmethod
    def extract_from_code_template(cls, code_template: str) -> Optional[str]:
        """从 `class Solution { public: ... }` 里摘第一个非构造/析构的方法签名字符串。"""
        pattern = re.compile(
            r"(?:public:|private:|protected:)"
            r".*?"
            r"(\w+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+"
            r"(\w+)\s*"
            r"\(([^)]*)\)\s*\{",
            re.MULTILINE | re.DOTALL,
        )

        for match in pattern.finditer(code_template):
            return_type = match.group(1).strip()
            func_name = match.group(2).strip()
            params = match.group(3).strip()
            if func_name == "Solution" or func_name.startswith("~"):
                continue
            if not return_type or return_type in {":", ",", "{", "}"}:
                continue
            return f"{return_type} {func_name}({params})"
        return None

    @classmethod
    def parse(cls, signature: str) -> FunctionSignature:
        signature = signature.strip()
        match = cls.SIGNATURE_PATTERN.match(signature)
        if not match:
            raise SignatureError(f"无效的函数签名格式: {signature}")

        return_type = match.group(1).strip()
        func_name = match.group(2).strip()
        params_str = match.group(3).strip()

        parameters = []
        if params_str:
            for param in cls._split_parameters(params_str):
                param = param.strip()
                if not param:
                    continue
                parts = param.rsplit(" ", 1)
                if len(parts) == 2:
                    param_type, param_name = parts
                    parameters.append(FunctionParameter(
                        type=param_type.strip(),
                        name=param_name.strip(),
                    ))
                else:
                    parameters.append(FunctionParameter(type=param.strip(), name=""))

        return FunctionSignature(
            return_type=return_type,
            name=func_name,
            parameters=parameters,
        )

    @staticmethod
    def _split_parameters(params_str: str) -> List[str]:
        """按顶层逗号切参数；`<...>` 内部的逗号保留（用 depth 计数）。"""
        params, current, depth = [], [], 0
        for char in params_str:
            if char == "<":
                depth += 1
                current.append(char)
            elif char == ">":
                depth -= 1
                current.append(char)
            elif char == "," and depth == 0:
                params.append("".join(current))
                current = []
            else:
                current.append(char)
        if current:
            params.append("".join(current))
        return params
