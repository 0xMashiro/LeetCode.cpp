#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
LeetCode C++ 题目管理 CLI 工具
提供命令行接口用于管理 LeetCode 题目
"""

import argparse
import sys
from pathlib import Path

from core import LeetCodeHelper, LeetCodeDB, SignatureParser
from graphql_client import get_client
from utils import color_text, ColorCode


__version__ = "1.0.0"


def print_error(message: str):
    """打印错误信息"""
    print(f"{color_text('错误:', ColorCode.RED.value)} {message}", file=sys.stderr)


def print_success(message: str):
    """打印成功信息"""
    print(color_text(f"✓ {message}", ColorCode.GREEN.value))


def print_info(message: str):
    """打印信息"""
    print(color_text(f"ℹ {message}", ColorCode.BLUE.value))


def print_warning(message: str):
    """打印警告信息"""
    print(color_text(f"⚠ {message}", ColorCode.YELLOW.value))


def parse_args():
    """解析命令行参数"""
    parser = argparse.ArgumentParser(
        prog="leetcode-cli",
        description="LeetCode C++ 题目管理工具",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  %(prog)s add 1                    # 添加题目 1（自动识别设计类题目）
  %(prog)s add two-sum              # 添加题目 two-sum
  %(prog)s add 146                  # 添加题目 146（自动识别为设计类）
  %(prog)s rm 1                     # 删除题目 1
  %(prog)s test 1                   # 测试题目 1
  %(prog)s doc                      # 生成已解决题目文档

更多信息请访问: https://github.com/your-repo/LeetCode.cpp
        """
    )
    
    parser.add_argument(
        '-v', '--version',
        action='version',
        version=f'%(prog)s {__version__}'
    )
    
    parser.add_argument(
        '--verbose', '-V',
        action='store_true',
        help='显示详细输出'
    )
    
    subparsers = parser.add_subparsers(
        dest='operation',
        help='操作类型',
        required=True,
        metavar='COMMAND'
    )
    
    # add 命令
    add_parser = subparsers.add_parser(
        'add',
        help='添加新题目（自动识别设计类题目）',
        description='添加新的 LeetCode 题目，自动生成头文件、源文件和测试文件'
    )
    add_parser.add_argument(
        'target',
        help='题目 ID 或 slug（例如: 1 或 two-sum）'
    )
    add_parser.add_argument(
        '--force', '-f',
        action='store_true',
        help='强制覆盖已存在的文件'
    )
    
    # rm 命令
    rm_parser = subparsers.add_parser(
        'rm',
        help='删除题目',
        description='删除指定题目的所有相关文件'
    )
    rm_parser.add_argument(
        'target',
        help='题目 ID 或 slug（例如: 1 或 two-sum）'
    )
    
    # test 命令
    test_parser = subparsers.add_parser(
        'test',
        help='运行测试',
        description='运行指定题目的测试用例'
    )
    test_parser.add_argument(
        'target',
        help='题目 ID 或 slug（例如: 1 或 two-sum）'
    )
    
    # doc 命令
    doc_parser = subparsers.add_parser(
        'doc',
        help='生成已解决题目文档',
        description='生成已解决题目的 Markdown 文档'
    )
    doc_parser.add_argument(
        '--output', '-o',
        default='./SOLVED.md',
        help='输出文件路径（默认: ./SOLVED.md）'
    )
    
    return parser.parse_args()


def resolve_problem_info(db: LeetCodeDB, target: str, verbose: bool = False) -> tuple:
    """解析题目信息并自动检测是否为设计类题目"""
    if verbose:
        print_info(f"正在解析题目: {target}")
    
    try:
        if target.isnumeric():
            problem_id = int(target)
            problem_info = db.get_by_id(problem_id)
            is_design = db.is_design_problem(problem_id)
        else:
            problem_info = db.get_by_slug(target)
            is_design = db.is_design_problem(problem_info.id)
        
        if verbose:
            print_success(f"找到题目: [{problem_info.id}] {problem_info.title}")
        
        return problem_info, is_design
    except ValueError as e:
        print_error(f"无法找到题目 '{target}': {e}")
        print_info("提示：可以使用题目 ID（如 1）或 slug（如 two-sum）")
        sys.exit(1)
    except Exception as e:
        print_error(f"解析题目时出错: {e}")
        sys.exit(1)


def handle_add(db: LeetCodeDB, target: str, force: bool = False, verbose: bool = False):
    """处理 add 操作"""
    problem_info, is_design = resolve_problem_info(db, target, verbose)
    
    print()
    print_info(f"题目: [{problem_info.id}] {problem_info.title}")
    print_info(f"URL: {problem_info.url}")
    
    # 统一获取代码模板
    if verbose:
        print_info("正在获取代码模板...")
    
    client = get_client()
    code_template = None
    try:
        code_template = client.get_cpp_code_template(problem_info.slug)
    except Exception as e:
        if verbose:
            print_warning(f"获取代码模板失败: {e}")
    
    if is_design:
        print()
        print_success("自动识别为设计类题目")
        
        if code_template:
            print_success("已获取代码模板，将从模板生成类定义")
            helper = LeetCodeHelper(problem_info=problem_info, is_design=is_design, code_template=code_template)
        else:
            print_warning("未能获取代码模板，将使用默认模板")
            helper = LeetCodeHelper(problem_info=problem_info, is_design=is_design)
        
        helper.create_files(force=force)
        print()
        print_success("文件创建完成")
    else:
        # 普通题目：尝试从代码模板中自动提取函数签名
        helper = LeetCodeHelper(problem_info=problem_info, is_design=is_design)
        
        extracted_signature = None
        if code_template:
            extracted_signature = SignatureParser.extract_from_code_template(code_template)
            if extracted_signature:
                print()
                print_success("已从代码模板自动提取函数签名")
                print_info(f"函数签名: {color_text(extracted_signature, ColorCode.BLUE.value)}")
        
        # 如果成功提取，直接使用；否则提示用户输入
        if extracted_signature:
            try:
                helper.update_signature(extracted_signature)
                helper.create_files(force=force)
                print()
                print_success("文件创建完成")
            except ValueError as e:
                print_error(f"无效的函数签名: {e}")
                print_info("提示：请检查函数签名格式是否正确")
                sys.exit(1)
        else:
            # 提取失败，提示用户输入
            default_signature = helper.signature
            print()
            colored_signature = color_text(default_signature, ColorCode.BLUE.value)
            prompt = f"请输入函数签名 (默认: {colored_signature}): "
            
            try:
                signature = input(prompt).strip() or default_signature
            except (EOFError, KeyboardInterrupt):
                print()
                print_error("操作已取消")
                sys.exit(1)
            
            try:
                helper.update_signature(signature)
                helper.create_files(force=force)
                print()
                print_success("文件创建完成")
            except ValueError as e:
                print_error(f"无效的函数签名: {e}")
                print_info("提示：函数签名格式应为: return_type function_name(param1_type param1_name, ...)")
                sys.exit(1)


def handle_rm(db: LeetCodeDB, target: str, verbose: bool = False):
    """处理 rm 操作"""
    problem_info, _ = resolve_problem_info(db, target, verbose)
    
    print()
    print_info(f"题目: [{problem_info.id}] {problem_info.title}")
    
    helper = LeetCodeHelper(problem_info=problem_info)
    helper.remove_files()
    
    print()
    print_success("文件删除完成")


def handle_test(db: LeetCodeDB, target: str, verbose: bool = False):
    """处理 test 操作"""
    problem_info, _ = resolve_problem_info(db, target, verbose)
    
    print()
    print_info(f"题目: [{problem_info.id}] {problem_info.title}")
    print_info("正在运行测试...")
    print()
    
    helper = LeetCodeHelper(problem_info=problem_info)
    try:
        success = helper.run_test()
        print()
        if success:
            print_success("所有测试通过")
            sys.exit(0)
        else:
            print_error("测试失败")
            sys.exit(1)
    except FileNotFoundError as e:
        print_error(f"测试二进制文件未找到: {e}")
        print_info("请先运行 'just build' 构建项目")
        sys.exit(1)
    except Exception as e:
        print_error(f"运行测试时出错: {e}")
        sys.exit(1)


def handle_doc(db: LeetCodeDB, output: str, verbose: bool = False):
    """处理 doc 操作"""
    if verbose:
        print_info("正在扫描已解决的题目...")
    
    helper = LeetCodeHelper()
    solved_problems = helper.get_solved_problems(db)
    
    if not solved_problems:
        print_warning("未找到已解决的题目")
        sys.exit(0)
    
    helper.generate_solved_problem_md_file(solved_problems, output)
    
    print()
    print_success(f"文档已生成: {output}")


def check_project_root():
    """检查是否在项目根目录"""
    if not Path("CMakeLists.txt").exists():
        print_error("请在项目根目录运行此命令（未找到 CMakeLists.txt）")
        sys.exit(1)


def main():
    """主函数"""
    args = parse_args()
    
    # 检查是否在正确的目录
    check_project_root()
    
    # 创建数据库实例
    db = LeetCodeDB()
    
    # 根据操作类型分发处理
    try:
        if args.operation == 'add':
            handle_add(db, args.target, force=args.force, verbose=args.verbose)
        elif args.operation == 'rm':
            handle_rm(db, args.target, verbose=args.verbose)
        elif args.operation == 'test':
            handle_test(db, args.target, verbose=args.verbose)
        elif args.operation == 'doc':
            handle_doc(db, args.output, verbose=args.verbose)
        else:
            print_error(f"未知操作: {args.operation}")
            sys.exit(1)
    except KeyboardInterrupt:
        print()
        print_error("操作已中断")
        sys.exit(130)
    except Exception as e:
        if args.verbose:
            import traceback
            traceback.print_exc()
        print_error(f"发生错误: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
