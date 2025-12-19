#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
LeetCode GraphQL API 客户端
负责 GraphQL 查询和原始数据缓存
"""

import json
import time
import urllib.request
import urllib.error
from typing import Dict, Any, Optional, List, Set

from cache import CacheManager


LEETCODE_GRAPHQL_URL = "https://leetcode.com/graphql/"
MAX_RETRIES = 3  # 最大重试次数
RETRY_DELAY_BASE = 2  # 重试延迟基数（秒）
REQUEST_TIMEOUT = 30  # 请求超时时间（秒）
DEFAULT_PAGE_SIZE = 50  # 默认分页大小


class GraphQLClient:
    """LeetCode GraphQL API 客户端（仅使用文件缓存）"""
    
    def __init__(self, base_url: str = LEETCODE_GRAPHQL_URL):
        self.base_url = base_url
        self._design_problem_ids_cache: Optional[Set[int]] = None  # 设计类题目ID缓存
    
    def query(self, query: str, variables: Optional[Dict[str, Any]] = None, max_retries: int = MAX_RETRIES) -> Dict[str, Any]:
        """发送 GraphQL 查询请求（带重试机制）
        
        Args:
            query: GraphQL 查询字符串
            variables: 查询变量
            max_retries: 最大重试次数
            
        Returns:
            GraphQL 响应数据
            
        Raises:
            Exception: 当所有重试都失败时抛出异常
        """
        payload = {"query": query}
        if variables:
            payload["variables"] = variables
        
        headers = {
            'Content-Type': 'application/json',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
            'Accept': 'application/json',
            'Origin': 'https://leetcode.com',
            'Referer': 'https://leetcode.com/',
        }
        
        last_exception = None
        for attempt in range(max_retries):
            try:
                req = urllib.request.Request(
                    self.base_url,
                    data=json.dumps(payload).encode('utf-8'),
                    headers=headers,
                    method='POST'
                )
                
                with urllib.request.urlopen(req, timeout=REQUEST_TIMEOUT) as response:
                    return json.loads(response.read().decode('utf-8'))
                    
            except (urllib.error.HTTPError, urllib.error.URLError) as e:
                last_exception = e
                if attempt < max_retries - 1:
                    # 指数退避：2^attempt 秒
                    delay = RETRY_DELAY_BASE ** attempt
                    time.sleep(delay)
                    continue
                else:
                    # 最后一次尝试失败
                    if isinstance(e, urllib.error.HTTPError):
                        error_body = e.read().decode('utf-8') if e.fp else "无错误详情"
                        raise Exception(f"HTTP 错误 {e.code} (已重试 {max_retries} 次): {error_body}")
                    else:
                        raise Exception(f"网络错误 (已重试 {max_retries} 次): {e}")
            except json.JSONDecodeError as e:
                # JSON 解析错误通常不需要重试
                raise Exception(f"JSON 解析错误: {e}")
        
        # 理论上不会到达这里，但为了类型检查
        if last_exception:
            raise last_exception
        raise Exception("未知错误")
    
    def get_problem_by_slug(self, slug: str, include_code_snippets: bool = False) -> Dict[str, Any]:
        """通过 slug 获取题目信息（带缓存）
        
        Args:
            slug: 题目 slug
            include_code_snippets: 是否包含代码模板（默认 False，因为代码模板较大）
        """
        cache_key = f"problem_slug_{slug}"
        if include_code_snippets:
            cache_key = f"problem_slug_{slug}_with_code"
        
        # 使用缓存管理器获取或查询
        def fetch_problem():
            code_snippets_field = """
                codeSnippets {
                  lang
                  langSlug
                  code
                }
            """ if include_code_snippets else ""
            
            query = f"""
            query questionData($titleSlug: String!) {{
              question(titleSlug: $titleSlug) {{
                questionId
                questionFrontendId
                title
                titleSlug
                difficulty
                isPaidOnly
                topicTags {{
                  name
                  slug
                }}
                {code_snippets_field}
              }}
            }}
            """
            
            result = self.query(query, {"titleSlug": slug})
            
            if "errors" in result:
                raise ValueError(f"GraphQL 错误: {result['errors']}")
            
            question = result.get("data", {}).get("question")
            if not question:
                raise ValueError(f"题目 '{slug}' 不存在")
            
            return question
        
        return CacheManager.get_or_compute(cache_key, fetch_problem)
    
    def get_cpp_code_template(self, slug: str) -> Optional[str]:
        """获取 C++ 代码模板"""
        problem = self.get_problem_by_slug(slug, include_code_snippets=True)
        code_snippets = problem.get("codeSnippets", [])
        
        for snippet in code_snippets:
            if snippet.get("langSlug") == "cpp":
                return snippet.get("code")
        
        return None
    
    def get_all_problems(self) -> List[Dict[str, Any]]:
        """获取所有题目列表（带文件缓存）"""
        cache_key = "all_problems"
        
        # 使用缓存管理器获取或查询
        def fetch_all_problems():
            query = """
            query {
              allQuestions {
                questionId
                questionFrontendId
                title
                titleSlug
                difficulty
                isPaidOnly
                topicTags {
                  name
                  slug
                }
              }
            }
            """
            
            result = self.query(query)
            
            if "errors" in result:
                raise ValueError(f"GraphQL 错误: {result['errors']}")
            
            return result.get("data", {}).get("allQuestions", [])
        
        return CacheManager.get_or_compute(cache_key, fetch_all_problems)
    
    def get_design_problems(self) -> List[Dict[str, Any]]:
        """获取所有设计类题目（带文件缓存）"""
        cache_key = "design_problems"
        
        # 使用缓存管理器获取或查询
        def fetch_design_problems():
            query = """
            query problemsetQuestionList($categorySlug: String, $limit: Int, $skip: Int, $filters: QuestionListFilterInput) {
              problemsetQuestionList: questionList(
                categorySlug: $categorySlug
                limit: $limit
                skip: $skip
                filters: $filters
              ) {
                total: totalNum
                questions: data {
                  questionId
                  questionFrontendId
                  title
                  titleSlug
                  difficulty
                }
              }
            }
            """
            
            all_design_problems = []
            limit = DEFAULT_PAGE_SIZE
            skip = 0
            
            while True:
                variables = {
                    "categorySlug": "",
                    "limit": limit,
                    "skip": skip,
                    "filters": {"tags": ["Design"]}
                }
                
                result = self.query(query, variables)
                
                if "errors" in result:
                    raise ValueError(f"GraphQL 错误: {result['errors']}")
                
                data = result.get("data", {}).get("problemsetQuestionList", {})
                questions = data.get("questions", [])
                total = data.get("total", 0)
                
                all_design_problems.extend(questions)
                
                if len(all_design_problems) >= total or len(questions) < limit:
                    break
                
                skip += limit
            
            return all_design_problems
        
        return CacheManager.get_or_compute(cache_key, fetch_design_problems)
    
    def get_problem_by_id(self, problem_id: int) -> Dict[str, Any]:
        """通过题目 ID 获取题目信息"""
        # 建立 ID -> slug 的映射缓存
        cache_key = "id_to_slug_map"
        
        def build_id_map():
            all_problems = self.get_all_problems()
            # 确保键是整数类型
            return {int(p["questionFrontendId"]): p["titleSlug"] for p in all_problems if p.get("questionFrontendId")}
        
        # 加载缓存，并处理 JSON 序列化导致的字符串键问题
        cached_map = CacheManager.load(cache_key)
        if cached_map is not None:
            # JSON 会将整数键转换为字符串，需要转换回来
            if isinstance(cached_map, dict) and cached_map:
                first_key = next(iter(cached_map.keys()))
                if isinstance(first_key, str) and first_key.isdigit():
                    # 转换字符串键为整数键
                    id_to_slug = {int(k): v for k, v in cached_map.items()}
                    # 保存修复后的映射
                    CacheManager.save(cache_key, id_to_slug)
                else:
                    id_to_slug = cached_map
            else:
                id_to_slug = cached_map
        else:
            # 缓存不存在，构建新的映射
            id_to_slug = build_id_map()
            CacheManager.save(cache_key, id_to_slug)
        
        if problem_id not in id_to_slug:
            raise ValueError(f"题目 ID {problem_id} 不存在")
        
        return self.get_problem_by_slug(id_to_slug[problem_id])
    
    def is_design_problem(self, problem_id: int) -> bool:
        """判断题目是否是设计类题目（带缓存）
        
        Args:
            problem_id: 题目 ID
            
        Returns:
            如果是设计类题目返回 True，否则返回 False
        """
        # 使用缓存避免重复查询
        if self._design_problem_ids_cache is None:
            try:
                design_problems = self.get_design_problems()
                self._design_problem_ids_cache = {
                    int(p["questionFrontendId"]) for p in design_problems
                }
            except Exception:
                # 如果查询失败，返回 False 并清空缓存以便下次重试
                self._design_problem_ids_cache = set()
                return False
        
        return problem_id in self._design_problem_ids_cache
    
    def clear_cache(self):
        """清除文件缓存"""
        CacheManager.clear()


# 全局客户端实例
_client: Optional[GraphQLClient] = None


def get_client() -> GraphQLClient:
    """获取全局 GraphQL 客户端实例"""
    global _client
    if _client is None:
        _client = GraphQLClient()
    return _client
