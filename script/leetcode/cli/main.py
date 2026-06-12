#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CLI 入口 + 子命令派发。"""

import argparse
import sys
import traceback
from pathlib import Path

from script.leetcode.api import ProblemRepository
from script.leetcode.cli import add_cmd, doc_cmd, rm_cmd, test_cmd
from script.leetcode.cli._printers import error

__version__ = "2.0.0"


def main() -> None:
    args = _parse_args()
    _require_project_root()

    repo = ProblemRepository()
    try:
        if args.operation == "add":
            add_cmd.run(repo, args.target, force=args.force, verbose=args.verbose)
        elif args.operation == "rm":
            rm_cmd.run(repo, args.target, verbose=args.verbose)
        elif args.operation == "test":
            test_cmd.run(repo, args.target, verbose=args.verbose)
        elif args.operation == "doc":
            doc_cmd.run(repo, args.output, verbose=args.verbose)
        else:
            error(f"未知操作: {args.operation}")
            sys.exit(1)
    except KeyboardInterrupt:
        print()
        error("操作已中断")
        sys.exit(130)
    except Exception as e:
        if args.verbose:
            traceback.print_exc()
        error(f"发生错误: {e}")
        sys.exit(1)


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        prog="leetcode-cli",
        description="LeetCode C++ 题目管理工具",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  %(prog)s add 1                    # 添加题目 1
  %(prog)s add two-sum              # 添加题目 two-sum
  %(prog)s add 146 --force          # 强制添加题目 146
  %(prog)s rm 1                     # 删除题目 1
  %(prog)s test 1                   # 测试题目 1
  %(prog)s doc                      # 生成已解决题目文档
        """,
    )
    parser.add_argument("-v", "--version", action="version", version=f"%(prog)s {__version__}")
    parser.add_argument("--verbose", "-V", action="store_true", help="显示详细输出")

    sub = parser.add_subparsers(dest="operation", required=True, metavar="COMMAND", help="操作类型")

    add_p = sub.add_parser("add", help="添加新题目", description="添加新的 LeetCode 题目")
    add_p.add_argument("target", help="题目 ID 或 slug")
    add_p.add_argument("--force", "-f", action="store_true", help="强制覆盖已存在的文件")

    rm_p = sub.add_parser("rm", help="删除题目")
    rm_p.add_argument("target", help="题目 ID 或 slug")

    test_p = sub.add_parser("test", help="运行测试")
    test_p.add_argument("target", help="题目 ID 或 slug")

    doc_p = sub.add_parser("doc", help="生成已解决题目文档")
    doc_p.add_argument("--output", "-o", default="./SOLVED.md", help="输出文件路径")

    return parser.parse_args()


def _require_project_root() -> None:
    if not Path("CMakeLists.txt").exists():
        error("请在项目根目录运行此命令（未找到 CMakeLists.txt）")
        sys.exit(1)
