#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`leetcode-cli test <target>` 实现：按题 slug 过滤 gtest 跑测。

三个测试二进制都可能存在（just single / just multi / just build 各生成一个），
挑时间最新的跑。都不存在就让用户先 build。
"""

import subprocess
import sys
from pathlib import Path

from script.leetcode.api import ProblemRepository
from script.leetcode.cli._printers import error, info, success


def run(repo: ProblemRepository, target: str, *, verbose: bool = False) -> None:
    problem_info = repo.resolve_target(target)

    print()
    info(f"题目: [{problem_info.id}] {problem_info.title}")
    info("正在运行测试...")
    print()

    project_root = _project_root()
    test_bins = {
        "single": project_root / "build/bin/single_problem_test",
        "multi": project_root / "build/bin/multi_problem_test",
        "full": project_root / "build/bin/problem_set_tests",
    }

    mtimes = {name: (p.stat().st_mtime if p.exists() else 0) for name, p in test_bins.items()}
    if not any(mtimes.values()):
        error("测试二进制文件未找到")
        error(f"  单题编译: {test_bins['single']} (just single <ID>)")
        error(f"  多题编译: {test_bins['multi']} (just multi <ID>)")
        error(f"  全量编译: {test_bins['full']} (just build)")
        error("请先构建项目")
        sys.exit(1)

    latest_name = max(mtimes, key=mtimes.get)
    test_bin = test_bins[latest_name]
    if verbose:
        info(f"使用测试二进制: {test_bin.name} ({latest_name})")

    class_base = "".join(word.capitalize() for word in problem_info.slug.split("-"))
    result = subprocess.run([str(test_bin), f"--gtest_filter=LeetCode*{class_base}Test*"])

    print()
    if result.returncode == 0:
        success("所有测试通过")
    else:
        error("测试失败")
        sys.exit(1)


def _project_root() -> Path:
    """`CMakeLists.txt` 所在目录。当前目录优先，否则脚本所在根。"""
    current = Path.cwd()
    if (current / "CMakeLists.txt").exists():
        return current
    script_dir = Path(__file__).parent.parent.parent.parent
    if (script_dir / "CMakeLists.txt").exists():
        return script_dir
    return current
