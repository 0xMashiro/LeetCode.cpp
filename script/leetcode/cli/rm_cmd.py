#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`leetcode-cli rm <target>` 实现：删除该题的三件套。"""

from script.leetcode.api import ProblemRepository
from script.leetcode.cli._printers import info, success
from script.leetcode.services import FileGenerator


def run(repo: ProblemRepository, target: str, *, verbose: bool = False) -> None:
    problem_info = repo.resolve_target(target)
    print()
    info(f"题目: [{problem_info.id}] {problem_info.title}")
    FileGenerator(problem_info).remove_files()
    print()
    success("文件删除完成")
