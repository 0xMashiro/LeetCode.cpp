#!/usr/bin/env python3
"""
题目池管理：从缓存中随机挑选未解决的题目
"""

import json
import random
from pathlib import Path
from typing import List, Optional, Dict, Any, Set


class ProblemPool:
    """题目池：管理所有题目，支持随机挑选未解决的题目"""
    
    CACHE_FILE = Path(".leetcode-cache/all_problems.json")
    UNSUPPORTED_CPP_FILE = Path(".leetcode-cache/unsupported_cpp.json")
    
    def __init__(self):
        self._all_problems: List[Dict[str, Any]] = []
        self._solved_slugs: set = set()
        self._unsupported_cpp_slugs: Set[str] = set()
        self._load_data()
    
    def _load_data(self):
        """加载题目数据"""
        # 1. 从缓存加载所有题目
        if self.CACHE_FILE.exists():
            cache = json.loads(self.CACHE_FILE.read_text())
            self._all_problems = cache.get("data", [])
        
        # 2. 扫描已解决的题目
        src_dir = Path("src/leetcode/problems")
        if src_dir.exists():
            for f in src_dir.glob("*.cpp"):
                self._solved_slugs.add(f.stem)
        
        # 3. 加载已知不支持 C++ 的题目
        self._unsupported_cpp_slugs = self._load_unsupported_cpp()
    
    def _load_unsupported_cpp(self) -> Set[str]:
        """加载已知不支持 C++ 的题目列表"""
        if self.UNSUPPORTED_CPP_FILE.exists():
            try:
                data = json.loads(self.UNSUPPORTED_CPP_FILE.read_text())
                return set(data.get("slugs", []))
            except (json.JSONDecodeError, IOError):
                pass
        return set()
    
    def _save_unsupported_cpp(self, slug: str):
        """记录不支持 C++ 的题目"""
        self._unsupported_cpp_slugs.add(slug)
        try:
            self.UNSUPPORTED_CPP_FILE.write_text(
                json.dumps({"slugs": sorted(list(self._unsupported_cpp_slugs))}, indent=2),
                encoding='utf-8'
            )
        except IOError:
            pass  # 忽略写入错误
    
    def _has_cpp_support(self, slug: str) -> bool:
        """检查题目是否支持 C++ 提交
        
        Args:
            slug: 题目的 title slug
            
        Returns:
            True 如果支持 C++，False 如果不支持
        """
        # 已经知道不支持，直接返回
        if slug in self._unsupported_cpp_slugs:
            return False
        
        # 尝试从 API 获取代码片段信息
        try:
            from script.leetcode.api import ProblemRepository
            repo = ProblemRepository()
            data = repo.get_detail_by_slug(slug, include_code=True)
            
            # 检查是否有 C++ 代码片段
            if data.code_snippets:
                for snippet in data.code_snippets:
                    if snippet.get("langSlug") == "cpp":
                        return True
                # 有代码片段但没有 C++，记录为不支持
                self._save_unsupported_cpp(slug)
                return False
            
            # 没有代码片段信息，保守起见认为支持（让后续流程处理）
            return True
            
        except Exception:
            # 出错时默认支持，让后续流程处理
            return True
    
    def _get_unsolved(self) -> List[Dict[str, Any]]:
        """获取未解决的题目列表"""
        return [
            p for p in self._all_problems
            if p.get("titleSlug") not in self._solved_slugs
            and p.get("titleSlug") not in self._unsupported_cpp_slugs  # 排除已知不支持 C++ 的
            and not p.get("isPaidOnly", False)  # 排除付费题
        ]
    
    def get_random(self, difficulty: Optional[str] = None, 
                   max_attempts: int = 10) -> Optional[int]:
        """随机获取一个未解决的题目 ID，确保支持 C++
        
        Args:
            difficulty: 难度过滤 (Easy/Medium/Hard)，None 表示不限制
            max_attempts: 最大尝试次数，避免死循环
        
        Returns:
            题目 ID，如果没有符合条件的题目返回 None
        """
        candidates = self._get_unsolved()
        
        if difficulty:
            candidates = [
                p for p in candidates 
                if p.get("difficulty") == difficulty
            ]
        
        if not candidates:
            return None
        
        # 尝试多次，避免选到不支持 C++ 的题目
        attempts = min(max_attempts, len(candidates))
        for _ in range(attempts):
            if not candidates:
                break
                
            problem = random.choice(candidates)
            slug = problem.get("titleSlug")
            problem_id = int(problem.get("questionFrontendId", problem.get("questionId", 0)))
            
            # 检查是否支持 C++
            if self._has_cpp_support(slug):
                return problem_id
            
            # 不支持 C++，从候选列表移除，继续尝试
            candidates.remove(problem)
            print(f"  ⚠️ 题目 [{problem_id}] {problem.get('title', '')} 不支持 C++，跳过")
        
        # 尝试次数用尽，返回 None
        return None
    
    def get_stats(self) -> Dict:
        """获取统计信息"""
        unsolved = self._get_unsolved()
        total_all = len(self._all_problems)
        total_solved = len(self._solved_slugs)
        
        by_difficulty = {"Easy": 0, "Medium": 0, "Hard": 0}
        for p in unsolved:
            diff = p.get("difficulty", "Unknown")
            by_difficulty[diff] = by_difficulty.get(diff, 0) + 1
        
        return {
            "total_in_cache": total_all,
            "total_solved": total_solved,
            "total_unsolved": len(unsolved),
            "by_difficulty": by_difficulty,
            "cache_file": str(self.CACHE_FILE),
            "cache_exists": self.CACHE_FILE.exists()
        }


def main():
    """CLI for testing"""
    import sys
    
    pool = ProblemPool()
    
    if len(sys.argv) > 1 and sys.argv[1] == "--stats":
        # 显示统计
        stats = pool.get_stats()
        print(f"Cache file: {stats['cache_file']} (exists: {stats['cache_exists']})")
        print(f"Total problems: {stats['total_in_cache']}")
        print(f"Solved: {stats['total_solved']}")
        print(f"Unsolved: {stats['total_unsolved']}")
        print(f"By difficulty: {stats['by_difficulty']}")
    else:
        # 随机挑选一个
        difficulty = sys.argv[1] if len(sys.argv) > 1 else None
        problem_id = pool.get_random(difficulty)
        
        if problem_id:
            print(problem_id)
        else:
            print("No unsolved problems found", file=sys.stderr)
            sys.exit(1)


if __name__ == "__main__":
    main()
