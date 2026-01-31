#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
LeetCode C++ 题目管理 CLI 工具
"""

import argparse
import subprocess
import sys
from pathlib import Path

from script.leetcode.api import ProblemRepository
from script.leetcode.services import FileGenerator, SignatureParser, DesignClassExtractor
from script.leetcode.models import ProblemInfo
from script.leetcode.config import FileTypeConfig
from script.leetcode.utils import color_text, ColorCode
from script.leetcode.exceptions import LeetCodeError


__version__ = "2.0.0"


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


class LeetCodeCLI:
    """LeetCode CLI 主类"""
    
    def __init__(self):
        self.repository = ProblemRepository()
    
    def resolve_problem(self, target: str) -> ProblemInfo:
        """解析题目标识符（ID 或 slug）为题目信息"""
        try:
            if target.isdigit():
                return self.repository.get_by_id(int(target))
            else:
                return self.repository.get_by_slug(target)
        except LeetCodeError as e:
            print_error(str(e))
            print_info("提示：可以使用题目 ID（如 1）或 slug（如 two-sum）")
            sys.exit(1)
    
    def handle_add(self, target: str, force: bool = False, verbose: bool = False):
        """处理 add 命令"""
        problem_info = self.resolve_problem(target)
        is_design = self.repository.is_design_problem(problem_info.id)
        
        print()
        print_info(f"题目: [{problem_info.id}] {problem_info.title}")
        print_info(f"URL: {problem_info.url}")
        
        # 获取代码模板
        code_template = None
        if verbose:
            print_info("正在获取代码模板...")
        
        try:
            code_template = self.repository.get_cpp_code_template(problem_info.slug)
        except Exception as e:
            if verbose:
                print_warning(f"获取代码模板失败: {e}")
        
        if is_design:
            print()
            print_success("自动识别为设计类题目")
            
            if code_template:
                print_success("已获取代码模板，将从模板生成类定义")
                design_def = DesignClassExtractor.extract(code_template)
                generator = FileGenerator(
                    problem_info=problem_info,
                    is_design=True,
                    design_class_def=design_def
                )
            else:
                print_warning("未能获取代码模板，将使用默认模板")
                generator = FileGenerator(problem_info=problem_info, is_design=True)
            
            generator.generate_files(force=force)
            print()
            print_success("文件创建完成")
        else:
            # 普通题目
            extracted_signature = None
            if code_template:
                extracted_signature = SignatureParser.extract_from_code_template(code_template)
                if extracted_signature:
                    print()
                    print_success(f"已从代码模板自动提取函数签名")
                    print_info(f"函数签名: {color_text(extracted_signature, ColorCode.BLUE.value)}")
            
            if extracted_signature:
                try:
                    func_sig = SignatureParser.parse(extracted_signature)
                    generator = FileGenerator(
                        problem_info=problem_info,
                        is_design=False,
                        function_signature=func_sig
                    )
                    generator.generate_files(force=force)
                    print()
                    print_success("文件创建完成")
                except Exception as e:
                    print_error(f"无效的函数签名: {e}")
                    sys.exit(1)
            else:
                # 提取失败，提示用户输入
                print()
                default_sig = "vector<int> twoSum(vector<int>& nums, int target)"
                colored_sig = color_text(default_sig, ColorCode.BLUE.value)
                
                try:
                    user_input = input(f"请输入函数签名 (默认: {colored_sig}): ").strip()
                    signature = user_input or default_sig
                    
                    func_sig = SignatureParser.parse(signature)
                    generator = FileGenerator(
                        problem_info=problem_info,
                        is_design=False,
                        function_signature=func_sig
                    )
                    generator.generate_files(force=force)
                    print()
                    print_success("文件创建完成")
                except (EOFError, KeyboardInterrupt):
                    print()
                    print_error("操作已取消")
                    sys.exit(1)
                except Exception as e:
                    print_error(f"无效的函数签名: {e}")
                    print_info("提示：函数签名格式应为: return_type function_name(param1_type param1_name, ...)")
                    sys.exit(1)
    
    def handle_rm(self, target: str, verbose: bool = False):
        """处理 rm 命令"""
        problem_info = self.resolve_problem(target)
        
        print()
        print_info(f"题目: [{problem_info.id}] {problem_info.title}")
        
        generator = FileGenerator(problem_info)
        generator.remove_files()
        
        print()
        print_success("文件删除完成")
    
    def handle_test(self, target: str, verbose: bool = False):
        """处理 test 命令"""
        problem_info = self.resolve_problem(target)
        
        print()
        print_info(f"题目: [{problem_info.id}] {problem_info.title}")
        print_info("正在运行测试...")
        print()
        
        test_bin = Path("build/bin/problem_set_tests")
        if not test_bin.exists():
            print_error("测试二进制文件未找到，请先运行 'just build' 构建项目")
            sys.exit(1)
        
        # 构建测试过滤器
        class_base = "".join(word.capitalize() for word in problem_info.slug.split("-"))
        test_filter = f"LeetCode*{class_base}Test*"
        
        result = subprocess.run(
            [str(test_bin), f"--gtest_filter={test_filter}"]
        )
        
        print()
        if result.returncode == 0:
            print_success("所有测试通过")
        else:
            print_error("测试失败")
            sys.exit(1)
    
    def handle_doc(self, output: str, verbose: bool = False):
        """处理 doc 命令"""
        if verbose:
            print_info("正在扫描已解决的题目...")
        
        # 获取所有题目并建立 slug 映射
        all_problems = self.repository.build_slug_map()
        
        # 扫描源文件目录
        source_folder = Path(FileTypeConfig.SOURCE.folder)
        solved_problems = []
        
        if source_folder.exists():
            for cpp_file in source_folder.glob("*.cpp"):
                slug = cpp_file.stem
                problem_info = all_problems.get(slug)
                if problem_info:
                    solved_problems.append(problem_info)
        
        if not solved_problems:
            print_warning("未找到已解决的题目")
            return
        
        solved_problems.sort(key=lambda p: p.id)
        
        # 生成 Markdown 文档
        self._generate_solved_md(solved_problems, output)
        
        count = color_text(len(solved_problems), ColorCode.GREEN.value)
        print()
        print_success(f"找到 {count} 个已解决的题目")
        print_success(f"文档已生成: {output}")
    
    def _generate_solved_md(self, solved_problems: list, output: str):
        """生成已解决题目文档"""
        output_path = Path(output)
        source_folder = Path(FileTypeConfig.SOURCE.folder)
        testcase_folder = Path(FileTypeConfig.TEST.folder)
        
        from script.leetcode.template import SOLVED_PROBLEM_DOC_HEADER
        
        with open(output_path, "w", encoding="utf-8") as f:
            f.write(SOLVED_PROBLEM_DOC_HEADER)
            for problem in solved_problems:
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


def parse_args():
    """解析命令行参数"""
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

更多信息: https://github.com/your-repo/LeetCode.cpp
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
        help='添加新题目',
        description='添加新的 LeetCode 题目'
    )
    add_parser.add_argument('target', help='题目 ID 或 slug')
    add_parser.add_argument('--force', '-f', action='store_true', help='强制覆盖已存在的文件')
    
    # rm 命令
    rm_parser = subparsers.add_parser('rm', help='删除题目')
    rm_parser.add_argument('target', help='题目 ID 或 slug')
    
    # test 命令
    test_parser = subparsers.add_parser('test', help='运行测试')
    test_parser.add_argument('target', help='题目 ID 或 slug')
    
    # doc 命令
    doc_parser = subparsers.add_parser('doc', help='生成已解决题目文档')
    doc_parser.add_argument('--output', '-o', default='./SOLVED.md', help='输出文件路径')
    
    return parser.parse_args()


def check_project_root():
    """检查是否在项目根目录"""
    if not Path("CMakeLists.txt").exists():
        print_error("请在项目根目录运行此命令（未找到 CMakeLists.txt）")
        sys.exit(1)


def main():
    """主函数"""
    args = parse_args()
    
    check_project_root()
    
    cli = LeetCodeCLI()
    
    try:
        if args.operation == 'add':
            cli.handle_add(args.target, force=args.force, verbose=args.verbose)
        elif args.operation == 'rm':
            cli.handle_rm(args.target, verbose=args.verbose)
        elif args.operation == 'test':
            cli.handle_test(args.target, verbose=args.verbose)
        elif args.operation == 'doc':
            cli.handle_doc(args.output, verbose=args.verbose)
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
