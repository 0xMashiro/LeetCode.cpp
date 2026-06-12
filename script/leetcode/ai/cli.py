#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""AI 解题器命令行入口。"""

import argparse
import sys
import traceback

from script.leetcode.ai.solver import AISolver
from script.leetcode.utils import ColorCode, color_text, log_with_time


def _build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="AI 自动解决 LeetCode 题目",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 解决每日一题
  python -m script.leetcode.ai.solver

  # 解决指定题目
  python -m script.leetcode.ai.solver 1

  # 生成解题报告（CI 使用）
  python -m script.leetcode.ai.solver --report
  python -m script.leetcode.ai.solver 1 --report

  # 随机挑选未解决的题目（用于测试增量编译）
  python -m script.leetcode.ai.solver --random
  python -m script.leetcode.ai.solver --random --difficulty Easy
  python -m script.leetcode.ai.solver --random --random-count 10 --no-leetcode

  # 自动循环模式（持续解决未完成的题目）
  python -m script.leetcode.ai.solver --auto
  python -m script.leetcode.ai.solver --auto --report
        """,
    )
    parser.add_argument("id", nargs="?", type=int, help="指定要解决的题目 ID")
    parser.add_argument("--random", action="store_true", help="随机挑选未解决的题目")
    parser.add_argument(
        "--random-count",
        type=int,
        default=1,
        help="配合 --random 使用，连续随机解题数量（默认 1；任一题失败即停止）",
    )
    parser.add_argument("--auto", action="store_true", help="自动循环模式：持续解决未完成的题目")
    parser.add_argument("--difficulty", choices=["Easy", "Medium", "Hard"], help="配合 --random 使用")
    parser.add_argument("--api-key", help="AI Provider 的 API Key（不传则按 provider 从环境变量读取）")
    parser.add_argument("--base-url", help="API 基础 URL（覆盖 provider 默认）")
    parser.add_argument("--report", action="store_true", help="生成解题报告（默认关闭以节省 token）")
    parser.add_argument(
        "--scaffold",
        action="store_true",
        help="Scaffold 模式：预生成可编译的三文件模板，AI 只填 solution1/TEST_P 的实现",
    )
    parser.add_argument(
        "--force-new-solution",
        action="store_true",
        help="题目文件已存在时仍强制重新解题（覆盖 AI_SOLVER_FORCE_NEW_SOLUTION）",
    )
    leetcode_group = parser.add_mutually_exclusive_group()
    leetcode_group.add_argument(
        "--no-leetcode",
        dest="require_leetcode",
        action="store_false",
        default=None,
        help="本地模式：编译测试通过即完成，不向 LeetCode 提交判题",
    )
    leetcode_group.add_argument(
        "--require-leetcode",
        dest="require_leetcode",
        action="store_true",
        default=None,
        help="必须提交 LeetCode 判题（默认行为）",
    )
    parser.add_argument(
        "--verify-all-strategies",
        action="store_true",
        default=None,
        help="一题多解时把每个 registerStrategy 都提交 LeetCode 验证（走翻译缓存；会把提交次数 ×N）",
    )
    parser.add_argument(
        "--prefer-multiple-strategies",
        action="store_true",
        default=None,
        help="提示 AI 尽量生成多个不同算法且都预期 Accepted 的策略（本地 TEST_P 会覆盖所有策略）",
    )
    parser.add_argument("--max-retries", type=int, default=3, help="自动模式最大重试次数（默认 3）")
    parser.add_argument("--retry-delay", type=int, default=60, help="自动模式重试间隔秒数（默认 60）")
    parser.add_argument(
        "--fail-streak-limit", type=int, default=3, help="自动模式连续失败暂停阈值（默认 3）"
    )
    parser.add_argument(
        "--fail-streak-pause", type=int, default=60, help="自动模式连续失败暂停秒数（默认 60）"
    )
    return parser


def main() -> None:
    args = _build_parser().parse_args()

    if args.auto:
        _run_auto(args)
        return

    try:
        solver = AISolver(
            api_key=args.api_key,
            base_url=args.base_url,
            enable_report=args.report,
            scaffold_mode=args.scaffold,
            force_new_solution=True if args.force_new_solution else None,
            require_leetcode=args.require_leetcode,
            verify_all_strategies=True if args.verify_all_strategies else None,
            prefer_multiple_strategies=True if args.prefer_multiple_strategies else None,
        )

        if args.id:
            solver.solve_problem(args.id)
        elif args.random:
            _solve_random(solver, args.difficulty, args.random_count)
        else:
            solver.solve_daily_challenge()
    except KeyboardInterrupt:
        print()
        log_with_time("操作已中断", ColorCode.YELLOW)
        sys.exit(130)
    except Exception as e:
        print(color_text(f"错误: {e}", ColorCode.RED.value))
        traceback.print_exc()
        sys.exit(1)


def _run_auto(args: argparse.Namespace) -> None:
    from script.leetcode.ai.auto_solver import AutoSolver

    auto_solver = AutoSolver(
        report=args.report,
        max_retries=args.max_retries,
        retry_delay=args.retry_delay,
        fail_streak_limit=args.fail_streak_limit,
        fail_streak_pause=args.fail_streak_pause,
        api_key=args.api_key,
        base_url=args.base_url,
        require_leetcode=args.require_leetcode,
    )
    try:
        auto_solver.run()
    except KeyboardInterrupt:
        print()
        print(color_text("操作已中断", ColorCode.YELLOW.value))
        sys.exit(130)


def _solve_random(solver: AISolver, difficulty: str, count: int = 1) -> None:
    from script.leetcode.problem_pool import ProblemPool

    if count < 1:
        raise ValueError("--random-count 必须大于等于 1")

    pool = ProblemPool()
    for index in range(count):
        problem_id = pool.get_random(difficulty)
        if not problem_id:
            log_with_time("No unsolved problems found", ColorCode.YELLOW)
            return
        if count > 1:
            log_with_time(f"🎲 Random run {index + 1}/{count}: selected problem {problem_id}", ColorCode.CYAN)
        else:
            log_with_time(f"🎲 Randomly selected problem: {problem_id}", ColorCode.CYAN)
        solver.solve_problem(problem_id)


if __name__ == "__main__":
    main()
