#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
LeetCode GraphQL API 客户端
"""

import json
import time
import urllib.request
import urllib.error
from typing import Dict, Any, Optional, List, Set

from script.leetcode.config import APIConfig, CacheConfig
from script.leetcode.exceptions import APIError, NetworkError, ProblemNotFoundError
from script.leetcode.models import ProblemData
from script.leetcode.api.cache import CacheManager


class GraphQLClient:
    """LeetCode GraphQL API 客户端"""
    
    def __init__(self, base_url: str = APIConfig.GRAPHQL_URL):
        self.base_url = base_url
        self._cache = CacheManager()
        self._design_problem_ids: Optional[Set[int]] = None
    
    def query(
        self, 
        query: str, 
        variables: Optional[Dict[str, Any]] = None, 
        max_retries: int = APIConfig.MAX_RETRIES
    ) -> Dict[str, Any]:
        """发送 GraphQL 查询请求（带重试机制）"""
        payload = {"query": query}
        if variables:
            payload["variables"] = variables
        
        headers = {
            'Content-Type': 'application/json',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
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
                
                with urllib.request.urlopen(req, timeout=APIConfig.REQUEST_TIMEOUT) as response:
                    return json.loads(response.read().decode('utf-8'))
                    
            except (urllib.error.HTTPError, urllib.error.URLError) as e:
                last_exception = e
                if attempt < max_retries - 1:
                    delay = APIConfig.RETRY_DELAY_BASE ** attempt
                    time.sleep(delay)
                    continue
                else:
                    if isinstance(e, urllib.error.HTTPError):
                        error_body = e.read().decode('utf-8') if e.fp else "无错误详情"
                        raise APIError(f"HTTP 错误 {e.code}: {error_body}", e.code)
                    else:
                        raise NetworkError(f"网络错误: {e}")
            except json.JSONDecodeError as e:
                raise APIError(f"JSON 解析错误: {e}")
        
        if last_exception:
            raise last_exception
        raise APIError("未知错误")
    
    def get_problem_by_slug(
        self, 
        slug: str, 
        include_code_snippets: bool = False
    ) -> ProblemData:
        """通过 slug 获取题目信息"""
        cache_key = f"problem_slug_{slug}_with_code" if include_code_snippets else f"problem_slug_{slug}"
        
        def fetch():
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
                content
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
                raise APIError(f"GraphQL 错误: {result['errors']}")
            
            question = result.get("data", {}).get("question")
            if not question:
                raise ProblemNotFoundError(slug)
            
            return question
        
        data = self._cache.get_or_compute(cache_key, fetch)
        return ProblemData.from_api_response(data)
    
    def get_all_problems(self) -> List[ProblemData]:
        """获取所有题目列表"""
        def fetch():
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
                raise APIError(f"GraphQL 错误: {result['errors']}")
            
            return result.get("data", {}).get("allQuestions", [])
        
        data_list = self._cache.get_or_compute("all_problems", fetch)
        return [ProblemData.from_api_response(d) for d in data_list]
    
    def get_design_problems(self) -> List[ProblemData]:
        """获取所有设计类题目"""
        def fetch():
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
            limit = APIConfig.DEFAULT_PAGE_SIZE
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
                    raise APIError(f"GraphQL 错误: {result['errors']}")
                
                data = result.get("data", {}).get("problemsetQuestionList", {})
                questions = data.get("questions", [])
                total = data.get("total", 0)
                
                all_design_problems.extend(questions)
                
                if len(all_design_problems) >= total or len(questions) < limit:
                    break
                
                skip += limit
            
            return all_design_problems
        
        data_list = self._cache.get_or_compute("design_problems", fetch)
        return [ProblemData.from_api_response(d) for d in data_list]
    
    def get_problem_by_id(
        self, 
        problem_id: int, 
        include_code_snippets: bool = False
    ) -> ProblemData:
        """通过题目 ID 获取题目信息"""
        # 使用 ID -> slug 映射缓存
        id_to_slug = self._get_id_to_slug_map()
        
        if problem_id not in id_to_slug:
            raise ProblemNotFoundError(str(problem_id))
        
        return self.get_problem_by_slug(id_to_slug[problem_id], include_code_snippets)
    
    def _get_id_to_slug_map(self) -> Dict[int, str]:
        """获取 ID 到 slug 的映射"""
        cache_key = "id_to_slug_map"
        
        def build():
            all_problems = self.get_all_problems()
            return {p.id: p.slug for p in all_problems}
        
        result = self._cache.get_or_compute(cache_key, build)
        
        # JSON 序列化会将整数键转为字符串，需要转回整数
        if result and isinstance(next(iter(result.keys())), str):
            result = {int(k): v for k, v in result.items()}
            # 更新缓存为正确的格式
            self._cache.save(cache_key, result)
        
        return result
    
    def is_design_problem(self, problem_id: int) -> bool:
        """判断题目是否是设计类题目"""
        if self._design_problem_ids is None:
            try:
                design_problems = self.get_design_problems()
                self._design_problem_ids = {p.id for p in design_problems}
            except Exception:
                self._design_problem_ids = set()
                return False
        
        return problem_id in self._design_problem_ids
    
    def get_daily_challenge(self) -> Dict[str, Any]:
        """获取今日每日一题"""
        def fetch():
            query = """
            query {
              activeDailyCodingChallengeQuestion {
                date
                userStatus
                link
                question {
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
                  content
                  codeSnippets {
                    lang
                    langSlug
                    code
                  }
                }
              }
            }
            """
            
            result = self.query(query)
            
            if "errors" in result:
                raise APIError(f"GraphQL 错误: {result['errors']}")
            
            daily = result.get("data", {}).get("activeDailyCodingChallengeQuestion")
            if not daily:
                raise APIError("无法获取每日一题")
            
            return daily
        
        return self._cache.get_or_compute(
            "daily_challenge", 
            fetch, 
            expiry_seconds=CacheConfig.DAILY_CHALLENGE_EXPIRY
        )
    
    def clear_cache(self):
        """清除缓存"""
        self._cache.clear()
        self._design_problem_ids = None
