#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`leetcode-cli add <target>` 实现：拉模板、抽签名、生成三件套。"""

import sys

from script.leetcode.api import ProblemRepository
from script.leetcode.cli._printers import error, info, success, warning
from script.leetcode.models import ProblemInfo
from script.leetcode.services import DesignClassExtractor, FileGenerator, SignatureParser
from script.leetcode.utils import ColorCode, color_text


def run(repo: ProblemRepository, target: str, *, force: bool = False, verbose: bool = False) -> None:
    problem_info = repo.resolve_target(target)
    is_design = repo.is_design_problem(problem_info.id)

    print()
    info(f"题目: [{problem_info.id}] {problem_info.title}")
    info(f"URL: {problem_info.url}")

    code_template = _fetch_template(repo, problem_info, verbose)

    if is_design:
        _generate_design(problem_info, code_template, force)
    else:
        _generate_ordinary(problem_info, code_template, force)


def _fetch_template(repo: ProblemRepository, problem_info: ProblemInfo, verbose: bool):
    if verbose:
        info("正在获取代码模板...")
    try:
        return repo.get_cpp_code_template(problem_info.slug)
    except Exception as e:
        if verbose:
            warning(f"获取代码模板失败: {e}")
        return None


def _generate_design(problem_info: ProblemInfo, code_template, force: bool) -> None:
    print()
    success("自动识别为设计类题目")
    if code_template:
        success("已获取代码模板，将从模板生成类定义")
        design_def = DesignClassExtractor.extract(code_template)
        generator = FileGenerator(
            problem_info=problem_info,
            is_design=True,
            design_class_def=design_def,
        )
    else:
        warning("未能获取代码模板，将使用默认模板")
        generator = FileGenerator(problem_info=problem_info, is_design=True)

    generator.generate_files(force=force)
    print()
    success("文件创建完成")


def _generate_ordinary(problem_info: ProblemInfo, code_template, force: bool) -> None:
    extracted = None
    if code_template:
        extracted = SignatureParser.extract_from_code_template(code_template)
        if extracted:
            print()
            success("已从代码模板自动提取函数签名")
            info(f"函数签名: {color_text(extracted, ColorCode.BLUE.value)}")

    signature = extracted or _prompt_signature()
    try:
        func_sig = SignatureParser.parse(signature)
    except Exception as e:
        error(f"无效的函数签名: {e}")
        info("提示：函数签名格式应为: return_type function_name(param1_type param1_name, ...)")
        sys.exit(1)

    FileGenerator(
        problem_info=problem_info,
        is_design=False,
        function_signature=func_sig,
    ).generate_files(force=force)
    print()
    success("文件创建完成")


def _prompt_signature() -> str:
    print()
    default_sig = "vector<int> twoSum(vector<int>& nums, int target)"
    colored = color_text(default_sig, ColorCode.BLUE.value)
    try:
        user_input = input(f"请输入函数签名 (默认: {colored}): ").strip()
        return user_input or default_sig
    except (EOFError, KeyboardInterrupt):
        print()
        error("操作已取消")
        sys.exit(1)
