#!/usr/bin/env python3
"""获取题目 slug 的简单脚本：接 ID 或 slug 都行，返回规范 slug。"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent.parent))

from script.leetcode.api import ProblemRepository
from script.leetcode.exceptions import LeetCodeError


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: python get_slug.py <problem_id_or_slug>", file=sys.stderr)
        sys.exit(1)

    try:
        problem = ProblemRepository().resolve_target(sys.argv[1])
        print(problem.slug)
    except LeetCodeError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
