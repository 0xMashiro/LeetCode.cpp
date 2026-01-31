#!/usr/bin/env python3
"""获取题目 slug 的简单脚本"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent.parent))

from script.leetcode.api import ProblemRepository
from script.leetcode.exceptions import LeetCodeError


def main():
    if len(sys.argv) != 2:
        print("Usage: python get_slug.py <problem_id>", file=sys.stderr)
        sys.exit(1)

    target = sys.argv[1]
    repository = ProblemRepository()

    try:
        if target.isdigit():
            problem = repository.get_by_id(int(target))
        else:
            problem = repository.get_by_slug(target)
        print(problem.slug)
    except LeetCodeError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
