#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`leetcode-cli doc` 实现：扫 src/leetcode/problems/，生成 Markdown 清单。"""

from pathlib import Path
from typing import List

from script.leetcode.api import ProblemRepository
from script.leetcode.cli._printers import info, success, warning
from script.leetcode.config import FileTypeConfig
from script.leetcode.models import ProblemInfo
from script.leetcode.template import SOLVED_PROBLEM_DOC_HEADER
from script.leetcode.utils import ColorCode, color_text


def run(repo: ProblemRepository, output: str, *, verbose: bool = False) -> None:
    if verbose:
        info("正在扫描已解决的题目...")

    all_problems = repo.build_slug_map()
    source_folder = Path(FileTypeConfig.SOURCE.folder)
    solved: List[ProblemInfo] = []
    if source_folder.exists():
        for cpp_file in source_folder.glob("*.cpp"):
            problem_info = all_problems.get(cpp_file.stem)
            if problem_info:
                solved.append(problem_info)

    if not solved:
        warning("未找到已解决的题目")
        return

    solved.sort(key=lambda p: p.id)
    _write_markdown(solved, output)

    count = color_text(len(solved), ColorCode.GREEN.value)
    print()
    success(f"找到 {count} 个已解决的题目")
    success(f"文档已生成: {output}")


def _write_markdown(solved: List[ProblemInfo], output: str) -> None:
    output_path = Path(output)
    source_folder = Path(FileTypeConfig.SOURCE.folder)
    testcase_folder = Path(FileTypeConfig.TEST.folder)

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(SOLVED_PROBLEM_DOC_HEADER)
        for problem in solved:
            rel_solution = (source_folder / f"{problem.slug}.cpp").relative_to(
                output_path.parent
            ).as_posix()
            rel_test = (testcase_folder / f"{problem.slug}.cpp").relative_to(
                output_path.parent
            ).as_posix()
            f.write(
                f"| {problem.id} "
                f"| [{problem.title}]({problem.url}) "
                f"| [Code]({rel_solution}) / [Test]({rel_test}) |\n"
            )
