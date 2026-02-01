#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
函数签名解析器和设计类提取器
"""

import re
from typing import Optional, List

from script.leetcode.models import FunctionSignature, FunctionParameter, DesignClassDefinition, DesignMethod
from script.leetcode.exceptions import SignatureError


class SignatureParser:
    """C++ 函数签名解析器"""
    
    # 匹配函数签名的正则表达式
    SIGNATURE_PATTERN = re.compile(
        r'^\s*(\S+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+'  # 返回类型
        r'(\w+)\s*'  # 函数名
        r'\((.*)\)\s*$',  # 参数列表
        re.DOTALL
    )
    
    @classmethod
    def extract_from_code_template(cls, code_template: str) -> Optional[str]:
        """从 C++ 代码模板中提取第一个函数签名
        
        只匹配 class Solution 中 public 部分的函数定义，排除构造函数和初始化列表。
        """
        pattern = re.compile(
            r'(?:public:|private:|protected:)'  # 访问修饰符
            r'.*?'  # 非贪婪匹配到函数定义
            r'(\w+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+'  # 返回类型
            r'(\w+)\s*'  # 函数名
            r'\(([^)]*)\)\s*\{',  # 参数列表 + 函数体开始
            re.MULTILINE | re.DOTALL
        )
        
        matches = list(pattern.finditer(code_template))
        
        if not matches:
            return None
        
        # 找到第一个匹配的函数签名
        for match in matches:
            return_type = match.group(1).strip()
            func_name = match.group(2).strip()
            params = match.group(3).strip()
            
            # 跳过构造函数（函数名与类名相同）
            if func_name == "Solution":
                continue
            
            # 跳过析构函数
            if func_name.startswith("~"):
                continue
            
            # 确保返回类型不是空的或只是符号
            if not return_type or return_type in [":", ",", "{", "}"]:
                continue
            
            return f"{return_type} {func_name}({params})"
        
        return None
    
    @classmethod
    def parse(cls, signature: str) -> FunctionSignature:
        """解析函数签名"""
        signature = signature.strip()
        match = cls.SIGNATURE_PATTERN.match(signature)
        
        if not match:
            raise SignatureError(f"无效的函数签名格式: {signature}")
        
        return_type = match.group(1).strip()
        func_name = match.group(2).strip()
        params_str = match.group(3).strip()
        
        # 解析参数列表
        parameters = []
        if params_str:
            params = cls._split_parameters(params_str)
            for param in params:
                param = param.strip()
                if not param:
                    continue
                # 分离类型和名称
                parts = param.rsplit(' ', 1)
                if len(parts) == 2:
                    param_type, param_name = parts
                    parameters.append(FunctionParameter(
                        type=param_type.strip(), 
                        name=param_name.strip()
                    ))
                else:
                    # 只有类型没有名称（不常见但可能）
                    parameters.append(FunctionParameter(type=param.strip(), name=""))
        
        return FunctionSignature(
            return_type=return_type,
            name=func_name,
            parameters=parameters
        )
    
    @staticmethod
    def _split_parameters(params_str: str) -> List[str]:
        """分割参数列表，处理嵌套模板"""
        params = []
        current = []
        depth = 0
        
        for char in params_str:
            if char == '<':
                depth += 1
                current.append(char)
            elif char == '>':
                depth -= 1
                current.append(char)
            elif char == ',' and depth == 0:
                params.append(''.join(current))
                current = []
            else:
                current.append(char)
        
        if current:
            params.append(''.join(current))
        
        return params


class DesignClassExtractor:
    """从代码模板中提取设计类定义"""
    
    @staticmethod
    def extract(code_template: str) -> Optional[DesignClassDefinition]:
        """从代码模板中提取类定义"""
        # 匹配 class ClassName {
        class_pattern = re.compile(r'class\s+(\w+)\s*\{', re.MULTILINE)
        match = class_pattern.search(code_template)
        if not match:
            return None
        
        class_name = match.group(1)
        start_pos = match.end()  # 类体开始位置（在 { 之后）
        
        # 手动匹配花括号，处理嵌套
        depth = 1
        pos = start_pos
        while pos < len(code_template) and depth > 0:
            if code_template[pos] == '{':
                depth += 1
            elif code_template[pos] == '}':
                depth -= 1
            pos += 1
        
        if depth != 0:
            return None
        
        # 提取类体（不包括最后的 }）
        class_body = code_template[start_pos:pos-1]
        
        # 提取所有方法（包括构造函数）
        methods = DesignClassExtractor._extract_methods(class_body, class_name)
        
        return DesignClassDefinition(
            class_name=class_name,
            class_body=class_body.strip(),
            methods=methods
        )
    
    @staticmethod
    def _extract_methods(class_body: str, class_name: str) -> List[DesignMethod]:
        """提取类中的方法"""
        methods = []
        method_pattern = re.compile(
            r'(?:(\w+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+)?'  # 可选的返回类型
            r'(\w+)\s*'  # 方法名
            r'\(([^)]*)\)\s*\{',  # 参数列表 + 函数体开始
            re.MULTILINE
        )
        
        for method_match in method_pattern.finditer(class_body):
            return_type_group = method_match.group(1)
            method_name = method_match.group(2).strip()
            params = method_match.group(3).strip()
            
            # 判断是否是构造函数
            is_constructor = (method_name == class_name)
            
            if is_constructor:
                return_type = ""
            else:
                return_type = return_type_group.strip() if return_type_group else ""
            
            methods.append(DesignMethod(
                return_type=return_type,
                name=method_name,
                params=params,
                is_constructor=is_constructor
            ))
        
        return methods
    
    @staticmethod
    def format_method_declarations(class_def: DesignClassDefinition) -> str:
        """格式化方法声明列表（用于头文件模板）"""
        declarations = []
        class_name = class_def.class_name
        
        for method in class_def.methods:
            if method.is_constructor:
                declarations.append(f"  {class_name}({method.params});")
            else:
                declarations.append(f"  {method.return_type} {method.name}({method.params});")
        
        return '\n'.join(declarations)
    
    @staticmethod
    def format_method_implementations(class_def: DesignClassDefinition) -> str:
        """格式化方法实现列表（用于源文件模板）"""
        implementations = []
        class_name = class_def.class_name
        
        for method in class_def.methods:
            if method.is_constructor:
                implementations.append(
                    f"{class_name}::{class_name}({method.params}) {{\n  // TODO: 实现构造函数\n}}"
                )
            else:
                return_type = method.return_type
                method_name = method.name
                params = method.params
                
                # 生成默认返回值
                if return_type == 'void':
                    default_return = ""
                else:
                    default_return = "return {};"
                
                implementations.append(
                    f"{return_type} {class_name}::{method_name}({params}) {{\n"
                    f"  // TODO: 实现方法\n"
                    f"  {default_return}\n"
                    f"}}"
                )
        
        return '\n\n'.join(implementations)
