#!/usr/bin/env python3
"""
题目池管理：从缓存中随机挑选未解决的题目
"""

import json
import random
from pathlib import Path
from typing import List, Optional, Dict, Any


class ProblemPool:
    """题目池：管理所有题目，支持随机挑选未解决的题目"""
    
    CACHE_FILE = Path(".leetcode-cache/all_problems.json")
    
    def __init__(self):
        self._all_problems: List[Dict[str, Any]] = []
        self._solved_slugs: set = set()
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
    
    def _get_unsolved(self) -> List[Dict[str, Any]]:
        """获取未解决的题目列表"""
        return [
            p for p in self._all_problems
            if p.get("titleSlug") not in self._solved_slugs
            and not p.get("isPaidOnly", False)  # 排除付费题
        ]
    
    def get_random(self, difficulty: Optional[str] = None) -> Optional[int]:
        """随机获取一个未解决的题目 ID
        
        Args:
            difficulty: 难度过滤 (Easy/Medium/Hard)，None 表示不限制
        
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
        
        problem = random.choice(candidates)
        # 返回 frontendId (显示给用户的题号)
        return int(problem.get("questionFrontendId", problem.get("questionId", 0)))
    
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
