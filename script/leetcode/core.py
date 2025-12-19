import os
import json
import re
from dataclasses import dataclass
from typing import Optional, Tuple, List, Set
from pathlib import Path

from config import FileTypeConfig
from template import SOLVED_PROBLEM_DOC_HEADER
from utils import color_text, ColorCode
from graphql_client import get_client
from cache import CacheManager


@dataclass
class ProblemInfo:
    """LeetCode 题目信息"""
    id: int
    title: str
    slug: str
    
    @property
    def url(self) -> str:
        return f"https://leetcode.com/problems/{self.slug}/"


class LeetCodeDB:
    """LeetCode 题目数据库（使用 GraphQL API，仅使用文件缓存）"""

    def __init__(self):
        """初始化数据库"""
        self.client = get_client()

    def is_design_problem(self, problem_id: int) -> bool:
        """判断是否是设计类题目"""
        return self.client.is_design_problem(problem_id)

    def get_by_id(self, problem_id: int) -> ProblemInfo:
        """通过 ID 获取题目信息"""
        problem_data = self.client.get_problem_by_id(problem_id)
        return self._convert_to_problem_info(problem_data)

    def get_by_slug(self, slug: str) -> ProblemInfo:
        """通过 slug 获取题目信息"""
        problem_data = self.client.get_problem_by_slug(slug)
        return self._convert_to_problem_info(problem_data)

    def get_by_title(self, title: str) -> ProblemInfo:
        """通过标题获取题目信息"""
        all_problems = self.client.get_all_problems()
        for problem_data in all_problems:
            if problem_data.get("title") == title:
                return self._convert_to_problem_info(problem_data)
        
        raise ValueError(f"题目标题 '{title}' 不存在")

    @staticmethod
    def _convert_to_problem_info(problem_data: dict) -> ProblemInfo:
        """将 GraphQL 返回的数据转换为 ProblemInfo"""
        return ProblemInfo(
            id=int(problem_data["questionFrontendId"]),
            title=problem_data["title"],
            slug=problem_data["titleSlug"]
        )


@dataclass
class FunctionParameter:
    """函数参数信息"""
    type: str
    name: str
    
    def __str__(self) -> str:
        return f"{self.type} {self.name}"


@dataclass
class FunctionSignature:
    """函数签名信息"""
    return_type: str
    name: str
    parameters: List[FunctionParameter]
    
    @property
    def param_types(self) -> str:
        """参数类型列表，用逗号分隔"""
        return ", ".join(p.type for p in self.parameters)
    
    @property
    def param_names(self) -> str:
        """参数名称列表，用逗号分隔"""
        return ", ".join(p.name for p in self.parameters)
    
    @property
    def param_declaration(self) -> str:
        """参数声明"""
        return ", ".join(str(p) for p in self.parameters)
    
    def __str__(self) -> str:
        return f"{self.return_type} {self.name}({self.param_declaration})"


class DesignClassExtractor:
    """从代码模板中提取设计类定义"""
    
    @staticmethod
    def extract_class_definition(code_template: str) -> Optional[dict]:
        """从代码模板中提取类定义
        
        Args:
            code_template: C++ 代码模板字符串
            
        Returns:
            包含类名和类体的字典，如果未找到则返回 None
            {
                'class_name': 'LRUCache',
                'class_body': 'public:\n    LRUCache(int capacity) {...}',
                'methods': [
                    {'return_type': 'int', 'name': 'get', 'params': 'int key', 'is_constructor': False},
                    ...
                ]
            }
        """
        # 匹配 class ClassName { ... };
        # 需要处理嵌套的花括号，所以手动解析
        class_pattern = re.compile(r'class\s+(\w+)\s*\{', re.MULTILINE)
        match = class_pattern.search(code_template)
        if not match:
            return None
        
        class_name = match.group(1)
        start_pos = match.end()  # 类体开始位置（在 { 之后）
        
        # 手动匹配花括号，处理嵌套
        depth = 1
        pos = start_pos
        while pos < len(code_template) and depth > 0:
            if code_template[pos] == '{':
                depth += 1
            elif code_template[pos] == '}':
                depth -= 1
            pos += 1
        
        if depth != 0:
            return None
        
        # 提取类体（不包括最后的 }）
        class_body = code_template[start_pos:pos-1]
        
        # 提取所有方法（包括构造函数）
        methods = []
        # 匹配方法定义，包括构造函数
        # 构造函数格式: ClassName(params) {
        # 普通方法格式: return_type method_name(params) {
        method_pattern = re.compile(
            r'(?:(\w+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+)?'  # 可选的返回类型
            r'(\w+)\s*'  # 方法名（可能是类名，即构造函数）
            r'\(([^)]*)\)\s*\{',  # 参数列表 + 函数体开始
            re.MULTILINE
        )
        
        for method_match in method_pattern.finditer(class_body):
            return_type_group = method_match.group(1)
            method_name = method_match.group(2).strip()
            params = method_match.group(3).strip()
            
            # 判断是否是构造函数（方法名与类名相同，且没有返回类型）
            is_constructor = (method_name == class_name)
            
            if is_constructor:
                return_type = ""
            else:
                return_type = return_type_group.strip() if return_type_group else ""
            
            methods.append({
                'return_type': return_type,
                'name': method_name,
                'params': params,
                'is_constructor': is_constructor
            })
        
        return {
            'class_name': class_name,
            'class_body': class_body.strip(),
            'methods': methods
        }
    
    @staticmethod
    def format_method_declarations(class_def: dict, class_name: str) -> str:
        """格式化方法声明列表（用于头文件模板）"""
        declarations = []
        for method in class_def['methods']:
            if method['is_constructor']:
                declarations.append(f"  {class_name}({method['params']});")
            else:
                declarations.append(f"  {method['return_type']} {method['name']}({method['params']});")
        return '\n'.join(declarations)
    
    @staticmethod
    def format_method_implementations(class_def: dict, class_name: str) -> str:
        """格式化方法实现列表（用于源文件模板）"""
        implementations = []
        for method in class_def['methods']:
            if method['is_constructor']:
                implementations.append(f"{class_name}::{class_name}({method['params']}) {{\n  // TODO: 实现构造函数\n}}")
            else:
                return_type = method['return_type']
                method_name = method['name']
                params = method['params']
                # 生成默认返回值：void 不需要返回值，其他类型使用统一初始化语法
                # C++ 的 {} 初始化会自动处理：int->0, bool->false, 指针->nullptr, 对象->默认构造
                if return_type == 'void':
                    default_return = ""
                else:
                    default_return = "return {};"
                
                implementations.append(f"{return_type} {class_name}::{method_name}({params}) {{\n  // TODO: 实现方法\n  {default_return}\n}}")
        return '\n\n'.join(implementations)


class SignatureParser:
    """C++ 函数签名解析器"""
    
    # 匹配函数签名的正则表达式
    # 格式: return_type func_name(param1_type param1_name, param2_type param2_name)
    SIGNATURE_PATTERN = re.compile(
        r'^\s*(\S+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+'  # 返回类型
        r'(\w+)\s*'  # 函数名
        r'\((.*?)\)\s*$',  # 参数列表
        re.DOTALL
    )
    
    @classmethod
    def extract_from_code_template(cls, code_template: str) -> Optional[str]:
        """从 C++ 代码模板中提取第一个函数签名
        
        只匹配 class Solution 中 public 部分的函数定义，排除构造函数和初始化列表。
        
        Args:
            code_template: C++ 代码模板字符串
            
        Returns:
            提取的函数签名字符串，如果未找到则返回 None
        """
        # 更精确的正则表达式：匹配返回类型 + 函数名 + 参数列表
        # 排除构造函数（函数名与类名相同的情况）
        # 排除初始化列表（包含 : 的情况）
        pattern = re.compile(
            r'(?:public:|private:|protected:)'  # 访问修饰符
            r'.*?'  # 非贪婪匹配到函数定义
            r'(\w+(?:\s*<[^>]+>)?(?:\s*&|\s*\*)?)\s+'  # 返回类型（支持模板、引用、指针）
            r'(\w+)\s*'  # 函数名
            r'\(([^)]*)\)\s*\{',  # 参数列表 + 函数体开始
            re.MULTILINE | re.DOTALL
        )
        
        matches = list(pattern.finditer(code_template))
        
        if not matches:
            return None
        
        # 找到第一个匹配的函数签名
        # 排除构造函数（函数名是 Solution 的情况）
        for match in matches:
            return_type = match.group(1).strip()
            func_name = match.group(2).strip()
            params = match.group(3).strip()
            
            # 跳过构造函数（函数名与类名相同）
            if func_name == "Solution":
                continue
            
            # 跳过析构函数
            if func_name.startswith("~"):
                continue
            
            # 确保返回类型不是空的或只是符号
            if not return_type or return_type in [":", ",", "{", "}"]:
                continue
            
            return f"{return_type} {func_name}({params})"
        
        return None
    
    @classmethod
    def parse(cls, signature: str) -> FunctionSignature:
        """解析函数签名"""
        signature = signature.strip()
        match = cls.SIGNATURE_PATTERN.match(signature)
        
        if not match:
            raise ValueError(f"无效的函数签名格式: {signature}")
        
        return_type = match.group(1).strip()
        func_name = match.group(2).strip()
        params_str = match.group(3).strip()
        
        # 解析参数列表
        parameters = []
        if params_str:
            # 处理嵌套模板和引用
            params = cls._split_parameters(params_str)
            for param in params:
                param = param.strip()
                if not param:
                    continue
                # 分离类型和名称
                parts = param.rsplit(' ', 1)
                if len(parts) == 2:
                    param_type, param_name = parts
                    parameters.append(FunctionParameter(type=param_type.strip(), name=param_name.strip()))
                else:
                    # 只有类型没有名称（不常见但可能）
                    parameters.append(FunctionParameter(type=param.strip(), name=""))
        
        return FunctionSignature(
            return_type=return_type,
            name=func_name,
            parameters=parameters
        )
    
    @staticmethod
    def _split_parameters(params_str: str) -> List[str]:
        """分割参数列表，处理嵌套模板"""
        params = []
        current = []
        depth = 0
        
        for char in params_str:
            if char == '<':
                depth += 1
                current.append(char)
            elif char == '>':
                depth -= 1
                current.append(char)
            elif char == ',' and depth == 0:
                params.append(''.join(current))
                current = []
            else:
                current.append(char)
        
        if current:
            params.append(''.join(current))
        
        return params


class LeetCodeHelper:
    """LeetCode 代码生成助手"""

    def __init__(self, problem_info: Optional[ProblemInfo] = None, signature: Optional[str] = None, is_design: bool = False, code_template: Optional[str] = None):
        self.problem_info = problem_info or ProblemInfo(
            id=1, title="Two Sum", slug="two-sum"
        )
        self.signature = signature or "vector<int> twoSum(vector<int>& nums, int target)"
        self._function_signature: Optional[FunctionSignature] = None
        self.is_design = is_design
        self.code_template = code_template  # 代码模板（用于设计类题目）
        
        if signature and not is_design:
            self._function_signature = SignatureParser.parse(signature)

    @property
    def function_signature(self) -> FunctionSignature:
        """获取解析后的函数签名"""
        if self._function_signature is None:
            self._function_signature = SignatureParser.parse(self.signature)
        return self._function_signature

    def update_signature(self, signature: str):
        """更新函数签名"""
        self.signature = signature
        self._function_signature = SignatureParser.parse(signature)

    def update_problem_info(self, problem_info: ProblemInfo):
        """更新题目信息"""
        self.problem_info = problem_info

    @property
    def solution_class_name(self) -> str:
        """生成解决方案类名（基础类名，不含后缀），例如：two-sum -> TwoSum"""
        words = self.problem_info.slug.split("-")
        return "".join(word.capitalize() for word in words)

    def _get_template_context(self) -> dict:
        """获取模板渲染上下文"""
        base_context = {
            "problem_id": self.problem_info.id,
            "problem_title": self.problem_info.title,
            "problem_slug": self.problem_info.slug,
            "leetcode_url_prefix": "https://leetcode.com/problems/",
            "solution_class_name": self.solution_class_name,
            "solution_class_suffix": "Solution",
            "test_class_suffix": "Test",
        }
        
        if self.is_design:
            # 设计类题目不需要函数签名
            return base_context
        else:
            # 普通题目需要函数签名
            sig = self.function_signature
            base_context.update({
                "solution_return_type": sig.return_type,
                "solution_func_name": sig.name,
                "solution_param": sig.param_declaration,
                "solution_param_type": sig.param_types,
                "solution_param_name": sig.param_names,
            })
            return base_context
    
    def _render_template(self, template: str, context: dict) -> str:
        """渲染模板（使用 format，无需额外依赖）"""
        # 转义花括号，避免与 format 冲突
        # 模板中使用 {{ 和 }} 表示字面量花括号
        return template.format(**context)
    
    def _create_file(self, file_path: Path, template: str, context: dict, force: bool) -> bool:
        """统一的文件创建方法
        
        Args:
            file_path: 文件路径
            template: 模板字符串
            context: 模板上下文
            force: 是否强制覆盖
            
        Returns:
            如果文件已存在且未强制覆盖返回 False，否则返回 True
        """
        highlighted_path = color_text(str(file_path), ColorCode.BLUE.value)
        
        if file_path.exists() and not force:
            print(f"文件已存在: {highlighted_path}")
            return False
        
        # 确保目录存在
        file_path.parent.mkdir(parents=True, exist_ok=True)
        
        # 写入文件
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(self._render_template(template, context))
        
        print(f"已创建文件: {highlighted_path}")
        return True

    def create_files(self, force: bool = False):
        """创建题目文件"""
        # 设计类题目：从代码模板生成
        if self.is_design and self.code_template:
            class_def = DesignClassExtractor.extract_class_definition(self.code_template)
            if class_def:
                # 使用提取的类定义生成文件
                self._create_design_files_from_template(class_def, force)
                return
        
        # 普通题目或设计类题目（无代码模板）：使用模板文件
        context = self._get_template_context()
        
        for config in FileTypeConfig:
            file_path = Path(config.value.placeholder.format(self.problem_info.slug))
            # 选择模板：设计类题目使用 design_template，普通题目使用 template
            template = config.value.design_template if (self.is_design and config.value.design_template) else config.value.template
            self._create_file(file_path, template, context, force)
    
    def _create_design_files_from_template(self, class_def: dict, force: bool = False):
        """从代码模板生成设计类文件"""
        class_name = self.solution_class_name
        
        # 准备模板上下文
        context = self._get_template_context()
        context['method_declarations'] = DesignClassExtractor.format_method_declarations(class_def, class_name)
        context['method_implementations'] = DesignClassExtractor.format_method_implementations(class_def, class_name)
        
        # 生成头文件
        header_path = Path(FileTypeConfig.HEADER.value.placeholder.format(self.problem_info.slug))
        header_template = FileTypeConfig.HEADER.value.design_template
        self._create_file(header_path, header_template, context, force)
        
        # 生成源文件
        source_path = Path(FileTypeConfig.SOURCE.value.placeholder.format(self.problem_info.slug))
        source_template = FileTypeConfig.SOURCE.value.design_template
        self._create_file(source_path, source_template, context, force)
        
        # 生成测试文件
        test_path = Path(FileTypeConfig.TEST.value.placeholder.format(self.problem_info.slug))
        test_template = FileTypeConfig.TEST.value.design_template
        self._create_file(test_path, test_template, context, force)

    def remove_files(self):
        """删除题目文件"""
        for config in FileTypeConfig:
            file_path = Path(config.value.placeholder.format(self.problem_info.slug))
            highlighted_path = color_text(str(file_path), ColorCode.RED.value)
            
            if file_path.exists():
                file_path.unlink()
                print(f"已删除文件: {highlighted_path}")
            else:
                print(f"文件不存在: {highlighted_path}")

    def get_solved_problems(self, db: LeetCodeDB) -> List[ProblemInfo]:
        """获取已解决的题目列表"""
        solved_problems = []
        source_folder = Path(FileTypeConfig.SOURCE.value.folder)
        
        if not source_folder.exists():
            return solved_problems
        
        for cpp_file in source_folder.glob("*.cpp"):
            problem_slug = cpp_file.stem
            try:
                problem_info = db.get_by_slug(problem_slug)
                solved_problems.append(problem_info)
            except ValueError:
                # 忽略无法在数据库中找到的题目
                continue

        solved_problems.sort(key=lambda p: p.id)
        count = color_text(len(solved_problems), ColorCode.GREEN.value)
        print(f"找到 {count} 个已解决的题目")
        return solved_problems

    def generate_solved_problem_md_file(self, solved_problems: List[ProblemInfo], output: str):
        """生成已解决题目的 Markdown 文档"""
        output_path = Path(output)
        solution_folder = Path(FileTypeConfig.SOURCE.value.folder)
        testcase_folder = Path(FileTypeConfig.TEST.value.folder)

        with open(output_path, "w", encoding="utf-8") as f:
            f.write(SOLVED_PROBLEM_DOC_HEADER)
            for problem_info in solved_problems:
                rel_solution_path = (solution_folder / f"{problem_info.slug}.cpp").relative_to(
                    output_path.parent
                ).as_posix()
                rel_testcase_path = (testcase_folder / f"{problem_info.slug}.cpp").relative_to(
                    output_path.parent
                ).as_posix()
                f.write(
                    f"| {problem_info.id} "
                    f"| [{problem_info.title}]({problem_info.url}) "
                    f"| [Code]({rel_solution_path}) / [Test]({rel_testcase_path}) |\n"
                )

        highlighted_path = color_text(str(output_path), ColorCode.BLUE.value)
        print(f"已生成文件: {highlighted_path}")

    def run_test(self):
        """运行测试"""
        test_bin = Path("build/bin/problem_set_tests")
        
        if not test_bin.exists():
            raise FileNotFoundError("测试二进制文件未找到，请先构建项目")
        
        test_filter = f"LeetCode*{self.solution_class_name}Test*"
        
        test_cmd = f"{test_bin} --gtest_filter={test_filter}"
        
        import subprocess
        result = subprocess.run(test_cmd, shell=True)
        return result.returncode == 0
