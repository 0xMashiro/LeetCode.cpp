#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`python -m script.leetcode.submit` 的命令行入口。"""

import argparse
import sys

from script.leetcode.submit.submitter import LeetCodeSubmitter
from script.leetcode.utils import ColorCode, color_text, log_with_time


def main() -> None:
    parser = argparse.ArgumentParser(
        description="将本地代码转换为 LeetCode 格式并提交验证",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 转换并提交题目 1
  python -m script.leetcode.submit 1

  # 使用第2个解法
  python -m script.leetcode.submit 1 --solution 2

  # 所有策略都提交一遍（走翻译缓存 + 6s 节流）
  python -m script.leetcode.submit 1 --all

  # 只交指定策略
  python -m script.leetcode.submit 1 --strategies 2,3
        """,
    )
    parser.add_argument("id", type=int, help="题目 ID")
    parser.add_argument(
        "--solution", "-n",
        type=int, default=0,
        help="使用第 n 个 registerStrategy;默认 0 表示最后一个 = 按项目约定的最优解",
    )
    parser.add_argument(
        "--all",
        action="store_true",
        help="把源文件里每个 registerStrategy 都翻译并提交一遍",
    )
    parser.add_argument(
        "--strategies",
        type=lambda s: [int(x.strip()) for x in s.split(",") if x.strip()],
        default=None,
        help="逗号分隔的 1-indexed 策略列表，例如 --strategies 2,3；与 --all 配合使用表示'仅提交这些'",
    )

    args = parser.parse_args()
    try:
        submitter = LeetCodeSubmitter()
        if args.all or args.strategies:
            _run_multi(submitter, args)
            return
        success = submitter.submit_problem(args.id, args.solution)
        sys.exit(0 if success else 1)
    except Exception as e:
        print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
        sys.exit(1)


def _run_multi(submitter: LeetCodeSubmitter, args: argparse.Namespace) -> None:
    results = submitter.submit_all_solutions(args.id, strategies=args.strategies)
    print()
    log_with_time("━━━ 全策略提交汇总 ━━━", ColorCode.MAGENTA)
    bad = 0
    for n, r, expected in results:
        match = r.status == expected
        mark = "✅" if match else "❌"
        note = "" if expected == "Accepted" else f" [预期 {expected}]"
        extra = (
            f" ({r.passed_test_cases}/{r.total_test_cases})"
            if r.status == "Wrong Answer"
            else ""
        )
        log_with_time(f"  解 {n}: {mark} {r.status}{note}{extra}", ColorCode.CYAN)
        if not match:
            bad += 1
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
