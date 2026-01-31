#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
题目数据仓库层
提供高层次的题目数据访问接口
"""

from typing import List, Dict, Optional

from script.leetcode.models import ProblemInfo, ProblemData
from script.leetcode.exceptions import ProblemNotFoundError
from script.leetcode.api.client import GraphQLClient


class ProblemRepository:
    """题目数据仓库"""
    
    def __init__(self, client: Optional[GraphQLClient] = None):
        self._client = client or GraphQLClient()
    
    @property
    def client(self) -> GraphQLClient:
        return self._client
    
    def get_by_id(self, problem_id: int) -> ProblemInfo:
        """通过 ID 获取题目信息"""
        problem_data = self._client.get_problem_by_id(problem_id)
        return ProblemInfo(
            id=problem_data.id,
            title=problem_data.title,
            slug=problem_data.slug
        )
    
    def get_by_slug(self, slug: str) -> ProblemInfo:
        """通过 slug 获取题目信息"""
        problem_data = self._client.get_problem_by_slug(slug)
        return ProblemInfo(
            id=problem_data.id,
            title=problem_data.title,
            slug=problem_data.slug
        )
    
    def get_by_title(self, title: str) -> ProblemInfo:
        """通过标题获取题目信息"""
        all_problems = self.get_all_problems()
        for problem in all_problems:
            if problem.title == title:
                return problem
        raise ProblemNotFoundError(title)
    
    def get_all_problems(self) -> List[ProblemInfo]:
        """获取所有题目列表（基础信息）"""
        all_data = self._client.get_all_problems()
        return [
            ProblemInfo(id=p.id, title=p.title, slug=p.slug)
            for p in all_data
        ]
    
    def get_all_problems_raw(self) -> List[ProblemData]:
        """获取所有题目的原始数据"""
        return self._client.get_all_problems()
    
    def get_detail_by_id(self, problem_id: int, include_code: bool = False) -> ProblemData:
        """获取题目详细信息"""
        return self._client.get_problem_by_id(problem_id, include_code)
    
    def get_detail_by_slug(self, slug: str, include_code: bool = False) -> ProblemData:
        """通过 slug 获取题目详细信息"""
        return self._client.get_problem_by_slug(slug, include_code)
    
    def is_design_problem(self, problem_id: int) -> bool:
        """判断是否是设计类题目"""
        return self._client.is_design_problem(problem_id)
    
    def get_cpp_code_template(self, slug: str) -> Optional[str]:
        """获取 C++ 代码模板"""
        problem_data = self._client.get_problem_by_slug(slug, include_code_snippets=True)
        return problem_data.get_cpp_code_template()
    
    def get_daily_challenge(self) -> Dict[str, any]:
        """获取每日一题"""
        return self._client.get_daily_challenge()
    
    def find_by_slug_prefix(self, prefix: str) -> List[ProblemInfo]:
        """通过 slug 前缀搜索题目"""
        all_problems = self.get_all_problems()
        return [p for p in all_problems if p.slug.startswith(prefix)]
    
    def build_slug_map(self) -> Dict[str, ProblemInfo]:
        """构建 slug 到题目信息的映射"""
        all_problems = self.get_all_problems()
        return {p.slug: p for p in all_problems}
