#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
数据模型定义
"""

from dataclasses import dataclass
from typing import List, Optional


@dataclass(frozen=True)
class ProblemInfo:
    """LeetCode 题目信息"""
    id: int
    title: str
    slug: str
    
    @property
    def url(self) -> str:
        return f"https://leetcode.com/problems/{self.slug}/"


@dataclass
class FunctionParameter:
    """函数参数信息"""
    type: str
    name: str
    
    def __str__(self) -> str:
        return f"{self.type} {self.name}"


@dataclass
class FunctionSignature:
    """函数签名信息"""
    return_type: str
    name: str
    parameters: List[FunctionParameter]
    
    @property
    def param_types(self) -> str:
        """参数类型列表，用逗号分隔"""
        return ", ".join(p.type for p in self.parameters)
    
    @property
    def param_names(self) -> str:
        """参数名称列表，用逗号分隔"""
        return ", ".join(p.name for p in self.parameters)
    
    @property
    def param_declaration(self) -> str:
        """参数声明"""
        return ", ".join(str(p) for p in self.parameters)
    
    def __str__(self) -> str:
        return f"{self.return_type} {self.name}({self.param_declaration})"


@dataclass
class DesignMethod:
    """设计类题目的方法信息"""
    return_type: str
    name: str
    params: str
    is_constructor: bool


@dataclass
class DesignClassDefinition:
    """设计类题目的类定义"""
    class_name: str
    class_body: str
    methods: List[DesignMethod]


@dataclass
class ProblemData:
    """LeetCode API 返回的原始题目数据"""
    question_id: str
    question_frontend_id: str
    title: str
    title_slug: str
    difficulty: str
    is_paid_only: bool
    content: Optional[str] = None
    code_snippets: Optional[List[dict]] = None
    topic_tags: Optional[List[dict]] = None
    
    @classmethod
    def from_api_response(cls, data: dict) -> "ProblemData":
        """从 API 响应创建实例"""
        return cls(
            question_id=data.get("questionId", ""),
            question_frontend_id=data.get("questionFrontendId", ""),
            title=data.get("title", ""),
            title_slug=data.get("titleSlug", ""),
            difficulty=data.get("difficulty", "Unknown"),
            is_paid_only=data.get("isPaidOnly", False),
            content=data.get("content"),
            code_snippets=data.get("codeSnippets"),
            topic_tags=data.get("topicTags"),
        )
    
    @property
    def id(self) -> int:
        """获取题目 ID（整数）"""
        try:
            return int(self.question_frontend_id)
        except (ValueError, TypeError):
            return 0
    
    @property
    def slug(self) -> str:
        """获取题目 slug"""
        return self.title_slug
    
    def get_cpp_code_template(self) -> Optional[str]:
        """获取 C++ 代码模板"""
        if not self.code_snippets:
            return None
        for snippet in self.code_snippets:
            if snippet.get("langSlug") == "cpp":
                return snippet.get("code")
        return None
