#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 自动解题器
使用 Kimi (Moonshot AI) API 的 Function Calling 功能自动解决 LeetCode 题目

依赖安装: pip install openai
"""

import json
import subprocess
import traceback
from pathlib import Path
from typing import Dict, Any, Optional, List, Tuple
from openai import OpenAI
from dotenv import load_dotenv

from graphql_client import get_client
from core import LeetCodeDB, LeetCodeHelper, ProblemInfo, SignatureParser
from utils import color_text, ColorCode


# 辅助类：用于模拟 API 响应对象
class Message:
    """模拟 API 响应的 Message 对象"""
    def __init__(self, content: str = "", reasoning_content: Optional[str] = None, tool_calls: Optional[List] = None):
        self.content = content
        self.reasoning_content = reasoning_content
        self.tool_calls = tool_calls or []


class ToolCall:
    """模拟 API 响应的 ToolCall 对象"""
    def __init__(self, call_id: str, call_type: str, function_name: str, function_arguments: str):
        self.id = call_id
        self.type = call_type
        self.function = type('obj', (object,), {
            'name': function_name,
            'arguments': function_arguments
        })()


class AISolver:
    """AI 自动解题器"""
    
    # 路径常量
    PATH_INCLUDE_PROBLEMS = "include/leetcode/problems"
    PATH_SRC_PROBLEMS = "src/leetcode/problems"
    PATH_TEST_PROBLEMS = "test/leetcode/problems"
    PATH_INCLUDE_UTILS = "include/leetcode/utils"
    PATH_SRC_UTILS = "src/leetcode/utils"
    PATH_CORE_HEADER = "include/leetcode/core.h"
    
    # 示例文件常量
    EXAMPLE_ORDINARY_SLUG = "two-sum"
    EXAMPLE_DESIGN_SLUG = "lru-cache"
    
    # 配置常量
    MAX_ITERATIONS = 20
    BUILD_TIMEOUT = 120
    TEST_TIMEOUT = 60
    DEFAULT_BASE_URL = "https://api.moonshot.cn/v1"
    
    def __init__(self, api_key: Optional[str] = None, base_url: Optional[str] = None):
        """初始化 AI 解题器
        
        Args:
            api_key: Moonshot API Key，优先级：参数 > 环境变量 > .env 文件
            base_url: API 基础 URL，优先级：参数 > 环境变量 MOONSHOT_BASE_URL > .env 文件 > 默认值
        """
        self._load_env()
        self.api_key = self._get_api_key(api_key)
        base_url = base_url or self._get_base_url()
        
        self.client = OpenAI(api_key=self.api_key, base_url=base_url)
        self.leetcode_client = get_client()
        self.db = LeetCodeDB()
        self.messages: List[Dict[str, Any]] = []
        self.use_reasoner = self._get_use_reasoner()
        
        # 用于收集思考过程和解题报告
        self.reasoning_log: List[str] = []
        self.solution_summary: List[str] = []
        self.problem_id: Optional[int] = None
        self.problem_title: Optional[str] = None
        self.problem_slug: Optional[str] = None
        self._current_reasoning: str = ""
    
    def _load_env(self) -> None:
        """加载 .env 文件"""
        project_root = Path(__file__).parent.parent.parent
        env_path = project_root / ".env"
        if env_path.exists():
            load_dotenv(dotenv_path=env_path)
        else:
            load_dotenv()
    
    def _get_api_key(self, api_key: Optional[str] = None) -> str:
        """获取 API Key"""
        import os
        api_key = api_key or os.getenv("MOONSHOT_API_KEY")
        if not api_key:
            raise ValueError(
                "请设置 MOONSHOT_API_KEY：\n"
                "  1. 创建 .env 文件并添加 MOONSHOT_API_KEY=your_key\n"
                "  2. 或设置环境变量: export MOONSHOT_API_KEY=your_key\n"
                "  3. 或通过命令行参数: --api-key your_key\n"
                "  参考 .env.example 文件"
            )
        return api_key
    
    def _get_base_url(self) -> str:
        """获取 base URL"""
        import os
        return os.getenv("MOONSHOT_BASE_URL", self.DEFAULT_BASE_URL)
    
    def _get_use_reasoner(self) -> bool:
        """获取是否启用深度思考模式"""
        import os
        # kimi-k2.5 默认启用思考能力，不需要特殊设置
        # 其他模型可以通过 MOONSHOT_ENABLE_THINKING 控制
        model = os.getenv("MOONSHOT_MODEL", "kimi-k2.5")
        # kimi-k2.5 和 kimi-k2-thinking 系列默认启用思考
        if "kimi-k2.5" in model or "thinking" in model:
            return True
        return os.getenv("MOONSHOT_ENABLE_THINKING", "false").lower() == "true"
    
    @classmethod
    def _get_tools(cls) -> List[Dict[str, Any]]:
        """获取工具函数定义"""
        return [
            {
                "type": "function",
                "function": {
                    "name": "get_problem_info",
                    "description": "获取题目的详细信息，包括题目描述、函数签名、示例等",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "problem_id": {
                                "type": "integer",
                                "description": "题目 ID（如 1, 2, 146）"
                            }
                        },
                        "required": ["problem_id"],
                        "additionalProperties": False
                    }
                }
            },
            {
                "type": "function",
                "function": {
                    "name": "generate_all_files",
                    "description": """生成题目的完整三个文件（头文件、源文件、测试文件）。

根据题目信息和参考示例，生成完整的、可直接编译和测试的代码文件。
这是推荐的方式，比单独生成代码更可靠。

如果文件已存在，默认会拒绝生成。如果编译或测试失败需要重新生成，可以设置 force_regenerate=true 来自动删除旧文件并重新生成。""",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "problem_id": {
                                "type": "integer",
                                "description": "题目 ID"
                            },
                            "header_content": {
                                "type": "string",
                                "description": "完整的头文件内容（.h 文件）"
                            },
                            "source_content": {
                                "type": "string",
                                "description": "完整的源文件内容（.cpp 文件）"
                            },
                            "test_content": {
                                "type": "string",
                                "description": "完整的测试文件内容（test/*.cpp 文件）"
                            },
                            "force_regenerate": {
                                "type": "boolean",
                                "description": "如果为 true，当文件已存在时会自动删除旧文件并重新生成。用于编译或测试失败后重新生成代码。默认为 false。",
                                "default": False
                            }
                        },
                        "required": ["problem_id", "header_content", "source_content", "test_content"],
                        "additionalProperties": False
                    }
                }
            },
            {
                "type": "function",
                "function": {
                    "name": "build_project",
                    "description": "编译项目，检查代码是否能成功编译",
                    "parameters": {
                        "type": "object",
                        "properties": {},
                        "required": [],
                        "additionalProperties": False
                    }
                }
            },
            {
                "type": "function",
                "function": {
                    "name": "run_tests",
                    "description": "运行测试用例，验证解决方案是否正确",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "problem_id": {
                                "type": "integer",
                                "description": "题目 ID"
                            }
                        },
                        "required": ["problem_id"],
                        "additionalProperties": False
                    }
                }
            },
            {
                "type": "function",
                "function": {
                    "name": "get_data_structure_implementation",
                    "description": "获取项目中数据结构的实现代码。当需要了解数据结构的内存管理方式、析构函数实现或其他实现细节时，可以使用此工具。支持的数据结构包括：tree（TreeNode）、linked-list（ListNode、MyLinkedList）、queue（MyQueue）、stack（MyStack）等。",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "data_structure": {
                                "type": "string",
                                "description": "要查看的数据结构名称，可选值：tree、linked-list、queue、stack",
                                "enum": ["tree", "linked-list", "queue", "stack"]
                            }
                        },
                        "required": ["data_structure"],
                        "additionalProperties": False
                    }
                }
            },
        ]
    
    @property
    def tools(self) -> List[Dict[str, Any]]:
        """获取工具函数列表"""
        return self._get_tools()
    
    def _get_file_paths(self, slug: str) -> Tuple[Path, Path, Path]:
        """获取题目的三个文件路径
        
        Args:
            slug: 题目 slug
            
        Returns:
            (header_path, source_path, test_path)
        """
        header_path = Path(f"{self.PATH_INCLUDE_PROBLEMS}/{slug}.h")
        source_path = Path(f"{self.PATH_SRC_PROBLEMS}/{slug}.cpp")
        test_path = Path(f"{self.PATH_TEST_PROBLEMS}/{slug}.cpp")
        return header_path, source_path, test_path
    
    def _read_file_safe(self, file_path: Path) -> str:
        """安全读取文件，如果不存在返回空字符串
        
        Args:
            file_path: 文件路径
            
        Returns:
            文件内容，如果文件不存在返回空字符串
        """
        try:
            return file_path.read_text(encoding='utf-8')
        except (FileNotFoundError, IOError):
            return ""
    
    def _read_example_files(self, slug: str) -> Tuple[str, str, str]:
        """读取示例文件的三个文件内容
        
        Args:
            slug: 示例题目 slug
            
        Returns:
            (header_content, source_content, test_content)
        """
        header_path, source_path, test_path = self._get_file_paths(slug)
        return (
            self._read_file_safe(header_path),
            self._read_file_safe(source_path),
            self._read_file_safe(test_path)
        )
    
    def get_problem_info(self, problem_id: int) -> Dict[str, Any]:
        """获取题目信息（工具函数）"""
        try:
            problem_data = self.leetcode_client.get_problem_by_id(problem_id, include_code_snippets=True)
            problem_info = self.db.get_by_id(problem_id)
            
            # 获取代码模板
            code_template = self.leetcode_client.get_cpp_code_template(problem_data["titleSlug"])
            
            # 提取函数签名
            signature = None
            if code_template:
                signature = SignatureParser.extract_from_code_template(code_template)
            
            # 获取题目描述
            content = problem_data.get("content", "")
            
            # 读取参考示例文件和核心头文件
            is_design = self.db.is_design_problem(problem_id)
            
            # 生成正确的类名
            helper = LeetCodeHelper(problem_info=problem_info, is_design=is_design)
            solution_class_base = helper.solution_class_name
            solution_class_name = f"{solution_class_base}Solution"
            test_class_name = f"{solution_class_base}Test"
            
            # 读取 core.h
            core_header = self._read_file_safe(Path(self.PATH_CORE_HEADER))
            
            # 读取参考示例文件
            two_sum_header, two_sum_source, two_sum_test = self._read_example_files(self.EXAMPLE_ORDINARY_SLUG)
            lru_cache_header, lru_cache_source, lru_cache_test = self._read_example_files(self.EXAMPLE_DESIGN_SLUG)
            
            return {
                "success": True,
                "problem_id": problem_id,
                "title": problem_data["title"],
                "slug": problem_data["titleSlug"],
                "difficulty": problem_data.get("difficulty", "Unknown"),
                "url": f"https://leetcode.com/problems/{problem_data['titleSlug']}/",
                "function_signature": signature,
                "code_template": code_template,
                "content": content if content else None,
                "is_design": is_design,
                "solution_class_name": solution_class_name,
                "solution_class_base": solution_class_base,
                "test_class_name": test_class_name,      
                "namespace": f"problem_{problem_id}",
                "core_header": core_header,
                "example_ordinary": {
                    "header": two_sum_header,
                    "source": two_sum_source,
                    "test": two_sum_test,
                    "description": "普通题目示例（Two Sum - 题目 ID 1）：使用 SolutionBase 模式，支持多策略实现"
                },
                "example_design": {
                    "header": lru_cache_header,
                    "source": lru_cache_source,
                    "test": lru_cache_test,
                    "description": "设计类题目示例（LRU Cache - 题目 ID 146）：直接实现类方法，不使用 SolutionBase"
                }
            }
        except Exception as e:
            return {
                "success": False,
                "error": str(e)
            }
    
    def generate_all_files(self, problem_id: int, header_content: str, source_content: str, test_content: str, force_regenerate: bool = False) -> Dict[str, Any]:
        """生成完整的三个文件（工具函数）"""
        try:
            problem_info = self.db.get_by_id(problem_id)
            header_path, source_path, test_path = self._get_file_paths(problem_info.slug)
            
            # 检查文件是否已存在
            files_exist = header_path.exists() and source_path.exists() and test_path.exists()
            
            if files_exist and not force_regenerate:
                return {
                    "success": False,
                    "error": f"文件已存在，跳过生成。如果编译或测试失败需要重新生成，请设置 force_regenerate=true 来自动删除旧文件并重新生成。",
                    "files": {
                        "header": str(header_path),
                        "source": str(source_path),
                        "test": str(test_path)
                    },
                    "suggestion": "设置 force_regenerate=true 来重新生成文件"
                }
            
            # 如果需要重新生成，先删除旧文件
            deleted_files = []
            if force_regenerate and files_exist:
                for path in [header_path, source_path, test_path]:
                    if path.exists():
                        path.unlink()
                        deleted_files.append(str(path))
            
            # 确保目录存在并写入文件
            for path in [header_path, source_path, test_path]:
                path.parent.mkdir(parents=True, exist_ok=True)
            
            header_path.write_text(header_content, encoding='utf-8')
            source_path.write_text(source_content, encoding='utf-8')
            test_path.write_text(test_content, encoding='utf-8')
            
            message = "三个文件已生成"
            if force_regenerate and deleted_files:
                message += f"（已删除并重新生成 {len(deleted_files)} 个旧文件）"
            
            return {
                "success": True,
                "message": message,
                "files": {
                    "header": str(header_path),
                    "source": str(source_path),
                    "test": str(test_path)
                },
                "deleted_files": deleted_files if force_regenerate else []
            }
        except Exception as e:
            return {
                "success": False,
                "error": f"{str(e)}\n{traceback.format_exc()}"
            }
    
    def build_project(self) -> Dict[str, Any]:
        """编译项目（工具函数）"""
        try:
            result = subprocess.run(
                ["just", "build"],
                capture_output=True,
                text=True,
                timeout=self.BUILD_TIMEOUT
            )
            
            if result.returncode == 0:
                return {
                    "success": True,
                    "message": "编译成功"
                }
            else:
                return {
                    "success": False,
                    "error": result.stderr,
                    "stdout": result.stdout
                }
        except subprocess.TimeoutExpired:
            return {
                "success": False,
                "error": "编译超时"
            }
        except Exception as e:
            return {
                "success": False,
                "error": str(e)
            }
    
    def run_tests(self, problem_id: int) -> Dict[str, Any]:
        """运行测试（工具函数）"""
        try:
            problem_info = self.db.get_by_id(problem_id)
            
            result = subprocess.run(
                ["python3", "script/leetcode/cli.py", "test", str(problem_id)],
                capture_output=True,
                text=True,
                timeout=self.TEST_TIMEOUT
            )
            
            if result.returncode == 0:
                return {
                    "success": True,
                    "message": "所有测试通过",
                    "output": result.stdout
                }
            else:
                return {
                    "success": False,
                    "error": "测试失败",
                    "output": result.stdout + result.stderr
                }
        except subprocess.TimeoutExpired:
            return {
                "success": False,
                "error": "测试超时"
            }
        except Exception as e:
            return {
                "success": False,
                "error": str(e)
            }
    
    def get_data_structure_implementation(self, data_structure: str) -> Dict[str, Any]:
        """获取数据结构实现（工具函数）"""
        try:
            supported_structures = ["tree", "linked-list", "queue", "stack"]
            
            if data_structure not in supported_structures:
                return {
                    "success": False,
                    "error": f"未知的数据结构: {data_structure}。支持的数据结构: {', '.join(supported_structures)}"
                }
            
            header_path = Path(f"{self.PATH_INCLUDE_UTILS}/{data_structure}.h")
            source_path = Path(f"{self.PATH_SRC_UTILS}/{data_structure}.cpp")
            
            if not header_path.exists():
                return {
                    "success": False,
                    "error": f"头文件不存在: {header_path}"
                }
            
            header_content = header_path.read_text(encoding='utf-8')
            source_content = self._read_file_safe(source_path) if source_path.exists() else None
            
            return {
                "success": True,
                "data_structure": data_structure,
                "header_file": str(header_path),
                "header_content": header_content,
                "source_file": str(source_path) if source_path.exists() else None,
                "source_content": source_content
            }
        except Exception as e:
            return {
                "success": False,
                "error": f"{str(e)}\n{traceback.format_exc()}"
            }
    
    def _parse_tool_arguments(self, arguments_str: str) -> Dict[str, Any]:
        """解析工具函数参数，带错误修复"""
        try:
            return json.loads(arguments_str)
        except json.JSONDecodeError as e:
            error_msg = f"JSON 解析错误: {str(e)}\n参数内容: {arguments_str[:200]}..."
            print(color_text(f"   ⚠️ {error_msg}", ColorCode.YELLOW.value))
            # 尝试修复常见的 JSON 问题
            try:
                fixed_args = arguments_str.replace('\n', '\\n').replace('\r', '\\r')
                result = json.loads(fixed_args)
                print(color_text("   ✓ JSON 已修复", ColorCode.GREEN.value))
                return result
            except json.JSONDecodeError:
                raise ValueError(error_msg)
    
    def _call_tool(self, tool_call) -> Dict[str, Any]:
        """调用工具函数"""
        function_name = tool_call.function.name
        
        try:
            arguments = self._parse_tool_arguments(tool_call.function.arguments)
        except ValueError as e:
            return {"success": False, "error": str(e)}
        
        tool_map = {
            "get_problem_info": self.get_problem_info,
            "generate_all_files": self.generate_all_files,
            "build_project": self.build_project,
            "run_tests": self.run_tests,
            "get_data_structure_implementation": self.get_data_structure_implementation,
        }
        
        if function_name in tool_map:
            return tool_map[function_name](**arguments)
        else:
            return {"success": False, "error": f"未知工具函数: {function_name}"}
    
    @staticmethod
    def _get_system_prompt() -> str:
        """获取系统提示词"""
        return """你是一个专业的 C++ 算法工程师，擅长解决 LeetCode 题目。

你的任务是：
1. 分析题目要求
2. 设计算法思路
3. 生成完整的三个文件（头文件、源文件、测试文件）
4. 确保代码能够编译通过
5. 确保代码能够通过所有测试用例

重要：请使用 generate_all_files 工具函数一次性生成完整的三个文件，而不是单独生成代码片段。

项目代码风格要求：
- 使用 Google C++ Style Guide
- 普通题目使用 SolutionBase 模式，参考 TwoSum 示例
- 设计类题目直接实现类方法，参考 LRUCache 示例
- 代码必须完整、可编译、可测试
- 好的代码命名和逻辑就是最好的注释，不要写太多注释！

重要：解题策略选择：
- 对于简单的问题，不需要强行追求一题多解（思路相同只是写法不同只能算一种解法）
- 只有当问题有多种不同的算法思路时（如暴力、动态规划、贪心等），才考虑实现多个策略
- 避免为了多解而多解，保持代码简洁和可读性，优先给出最优雅、最简洁的实现方案

重要：头文件包含规则：
- "leetcode/core.h" 已经包含了所有常用的 STL 头文件和 using namespace std
- 因此不要再包含任何 STL 头文件（如 <vector>, <string>, <algorithm> 等）

重要：数据结构内存管理规则：
- 项目中的数据结构类（如 TreeNode、ListNode、MyLinkedList 等）已经在析构函数中实现了自动内存管理
- TreeNode 的析构函数会自动删除 left 和 right 子树
- MyLinkedList 的析构函数会自动删除所有节点
- **绝对不要**在生成的代码中手动调用 delete 来删除这些数据结构对象，否则会导致双重删除（double delete）和段错误
- **优先查看数据结构实现**：如果题目涉及数据结构（如二叉树、链表等），在开始解题前应该先调用 get_data_structure_implementation 工具函数查看数据结构的实现细节，特别是：
  * 了解数据结构的内存管理方式（析构函数如何工作）
  * 查看可用的辅助函数（如 constructTree、constructLinkedList 等），这些函数可以方便地构造测试用例
  * 了解数据结构的 API 和使用方式，避免重复实现已有功能

重要：测试用例规则：
- 题目自带的测试用例是必须通过的
- 你在自己构造测试用例时需确保你构造的测试用例是正确的，并且能够覆盖所有可能的情况
- 测试用例不在于数量，而在于质量

工作流程：
1. 调用 get_problem_info 获取题目信息、参考示例和**正确的类名、测试类名、命名空间**
2. 如果题目涉及数据结构（如二叉树、链表等），优先调用 get_data_structure_implementation 查看数据结构实现
3. 根据题目类型（普通/设计类）选择合适的示例
4. 分析题目要求，设计算法
5. 调用 generate_all_files 生成完整的三个文件（严格按照示例格式和提供的类名）
6. 调用 build_project 编译验证
7. 调用 run_tests 运行测试
8. 如果编译或测试失败，根据错误信息修复后，调用 generate_all_files 时设置 force_regenerate=true 来重新生成文件

重要提示：你的思考过程和解题步骤会被记录并作为 GitHub Pull Request 的解题报告。请在思考过程中：
- 描述你对题目和参考示例的理解
- 详细说明算法思路和设计决策（如果有多种算法，先从最容易想到的算法开始，再逐步优化）
- 解释时间复杂度和空间复杂度
- 说明遇到的困难和解决方案
- 总结解题的关键点

你的思考过程也应当以 Markdown 格式输出，以及注意代码和数学公式格式，方便后续生成解题报告。
在最终的解题报告中不需要提到工作流程中的 function calling, 仅描述你的思考过程和解题步骤。

请严格按照参考示例的格式和提供的类名生成代码，确保能够直接编译和测试。"""
    
    def solve_daily_challenge(self) -> None:
        """解决每日一题"""
        print(color_text("🚀 开始解决每日一题", ColorCode.CYAN.value))
        print()
        
        try:
            daily = self.leetcode_client.get_daily_challenge()
            question = daily["question"]
            problem_id = int(question["questionFrontendId"])
            
            self._solve_problem_by_id(problem_id, question, is_daily=True)
                
        except Exception as e:
            print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
            traceback.print_exc()
    
    def solve_problem(self, problem_id: int) -> None:
        """解决指定题目
        
        Args:
            problem_id: 题目 ID
        """
        print(color_text(f"🚀 开始解决题目: [{problem_id}]", ColorCode.CYAN.value))
        print()
        
        try:
            # 获取题目信息
            problem_data = self.leetcode_client.get_problem_by_id(problem_id, include_code_snippets=True)
            question = {
                "title": problem_data["title"],
                "titleSlug": problem_data["titleSlug"],
                "difficulty": problem_data.get("difficulty", "Unknown")
            }
            
            self._solve_problem_by_id(problem_id, question, is_daily=False)
                
        except Exception as e:
            print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
            traceback.print_exc()
    
    def _solve_problem_by_id(self, problem_id: int, question: Dict[str, Any], is_daily: bool = False) -> None:
        """解决指定题目的通用方法
        
        Args:
            problem_id: 题目 ID
            question: 题目信息字典，包含 title, titleSlug, difficulty
            is_daily: 是否为每日一题
        """
        self.problem_id = problem_id
        self.problem_title = question['title']
        self.problem_slug = question['titleSlug']
        
        # 打印题目信息
        title_prefix = "📋 今日题目" if is_daily else "📋 题目"
        print(color_text(f"{title_prefix}: [{problem_id}] {question['title']}", ColorCode.BLUE.value))
        print(color_text(f"🔗 URL: https://leetcode.com/problems/{question['titleSlug']}/", ColorCode.BLUE.value))
        print()
        
        # 记录题目信息到解题报告
        self._log_problem_info(problem_id, question, is_daily)
        
        # 检查文件是否已存在
        if self._check_files_exist(problem_id):
            return
        
        self.reasoning_log.append("## 解题过程\n\n")
        
        # 初始化对话
        self._init_conversation(problem_id, is_daily)
        
        # 开始对话循环
        self._run_conversation_loop()
    
    def _log_problem_info(self, problem_id: int, question: Dict[str, Any], is_daily: bool = False) -> None:
        """记录题目信息到解题报告"""
        prefix = "每日一题" if is_daily else "题目"
        self.reasoning_log.append(f"# LeetCode {prefix}：{problem_id}. {question['title']}\n")
        self.reasoning_log.append(f"**题目链接**: https://leetcode.com/problems/{question['titleSlug']}/\n")
        self.reasoning_log.append(f"**难度**: {question.get('difficulty', 'Unknown')}\n\n")
    
    def _check_files_exist(self, problem_id: int) -> bool:
        """检查文件是否已存在，如果存在则处理并返回 True"""
        problem_info = self.db.get_by_id(problem_id)
        header_path, source_path, test_path = self._get_file_paths(problem_info.slug)
        
        files_exist = header_path.exists() and source_path.exists() and test_path.exists()
        
        if files_exist:
            print(color_text("✅ 题目已解决，文件已存在", ColorCode.GREEN.value))
            print(color_text(f"   头文件: {header_path}", ColorCode.CYAN.value))
            print(color_text(f"   源文件: {source_path}", ColorCode.CYAN.value))
            print(color_text(f"   测试文件: {test_path}", ColorCode.CYAN.value))
            print()
            
            # 记录到报告
            self.reasoning_log.append("## 状态\n\n")
            self.reasoning_log.append("✅ **题目已解决**，文件已存在，跳过自动解题。\n\n")
            self.reasoning_log.append("**已存在的文件**:\n")
            self.reasoning_log.append(f"- 头文件: `{header_path}`\n")
            self.reasoning_log.append(f"- 源文件: `{source_path}`\n")
            self.reasoning_log.append(f"- 测试文件: `{test_path}`\n\n")
            
            # 生成报告并退出
            self._generate_solution_report()
            # 创建标记文件，告知 CI 跳过 PR 创建
            skip_pr_file = Path("SKIP_PR")
            skip_pr_file.write_text(f"题目 {problem_id} 已解决，文件已存在，跳过 PR 创建。\n", encoding='utf-8')
            return True
        return False
    
    def _init_conversation(self, problem_id: int, is_daily: bool = False) -> None:
        """初始化对话"""
        user_message = f"请帮我解决 LeetCode 每日一题：题目 ID {problem_id}" if is_daily else f"请帮我解决 LeetCode 题目：题目 ID {problem_id}"
        self.messages = [{
            "role": "system",
            "content": self._get_system_prompt()
        }, {
            "role": "user",
            "content": user_message
        }]
        self._clear_reasoning_content()
    
    def _run_conversation_loop(self) -> None:
        """运行对话循环"""
        import os
        model_name = os.getenv("MOONSHOT_MODEL", "kimi-k2.5")
        self._print_model_info()
        
        for iteration in range(self.MAX_ITERATIONS):
            print(color_text(f"💭 AI 思考中... (第 {iteration + 1} 轮)", ColorCode.YELLOW.value))
            
            request_params = self._build_request_params(model_name)
            
            try:
                message = self._handle_stream_response(request_params)
            except Exception as e:
                print(color_text(f"❌ API 调用错误: {e}", ColorCode.RED.value))
                traceback.print_exc()
                break
            
            # 构建并保存消息
            message_to_save = self._build_message_to_save(message)
            self.messages.append(message_to_save)
            
            # 处理工具调用
            if message.tool_calls:
                self._handle_tool_calls(message.tool_calls)
            else:
                # 没有工具调用，说明 AI 已经完成
                self._print_completion(message)
                self._generate_solution_report()
                break
        else:
            print(color_text("⚠️ 达到最大迭代次数，停止处理", ColorCode.YELLOW.value))
            print(color_text("提示: 可以增加 max_iterations 或检查是否有循环调用", ColorCode.YELLOW.value))
    
    def _build_request_params(self, model_name: str) -> Dict[str, Any]:
        """构建请求参数"""
        request_params = {
            "model": model_name,
            "messages": self.messages,
            "tools": self.tools,
            "stream": True
        }
        
        # kimi-k2.5 默认启用思考能力，不需要额外设置
        # 对于非 k2.5 的其他模型，可以通过 MOONSHOT_ENABLE_THINKING 控制
        if self.use_reasoner and "kimi-k2.5" not in model_name:
            request_params["extra_body"] = {"thinking": {"type": "enabled"}}
        
        return request_params
    
    def _clear_reasoning_content(self) -> None:
        """清除历史消息中的 reasoning_content（节省带宽）"""
        if self.use_reasoner:
            for msg in self.messages:
                if isinstance(msg, dict) and "reasoning_content" in msg:
                    msg["reasoning_content"] = None
    
    def _print_model_info(self) -> None:
        """打印模型信息"""
        import os
        model_name = os.getenv("MOONSHOT_MODEL", "kimi-k2.5")
        if self.use_reasoner:
            print(color_text(f"🧠 使用 {model_name} 模型（思考模式）", ColorCode.CYAN.value))
        else:
            print(color_text(f"💬 使用 {model_name} 模型", ColorCode.CYAN.value))
        print()
    
    def _build_message_to_save(self, message: Message) -> Dict[str, Any]:
        """构建要保存的消息"""
        message_to_save = {
            "role": "assistant",
            "content": message.content or "",
        }
        
        if self.use_reasoner and hasattr(message, 'reasoning_content') and message.reasoning_content:
            message_to_save["reasoning_content"] = message.reasoning_content
        
        if message.tool_calls:
            message_to_save["tool_calls"] = [
                {
                    "id": tc.id,
                    "type": tc.type,
                    "function": {
                        "name": tc.function.name,
                        "arguments": tc.function.arguments
                    }
                }
                for tc in message.tool_calls
            ]
        
        return message_to_save
    
    def _handle_tool_calls(self, tool_calls: List[ToolCall]) -> None:
        """处理工具调用"""
        for tool_call in tool_calls:
            func_name = tool_call.function.name
            print(color_text(f"🔧 调用工具: {func_name}", ColorCode.MAGENTA.value))
            
            # 显示参数预览
            args_preview = tool_call.function.arguments[:100] + "..." if len(tool_call.function.arguments) > 100 else tool_call.function.arguments
            print(f"   参数: {args_preview}")
            
            try:
                result = self._call_tool(tool_call)
                self._print_tool_result(result)
                
                # 将工具结果添加到消息中
                self.messages.append({
                    "role": "tool",
                    "tool_call_id": tool_call.id,
                    "content": json.dumps(result, ensure_ascii=False)
                })
            except Exception as e:
                error_msg = f"工具调用异常: {str(e)}"
                print(color_text(f"   ✗ {error_msg}", ColorCode.RED.value))
                traceback.print_exc()
                # 即使出错也要添加错误结果，让 AI 知道
                self.messages.append({
                    "role": "tool",
                    "tool_call_id": tool_call.id,
                    "content": json.dumps({"success": False, "error": error_msg}, ensure_ascii=False)
                })
    
    def _print_tool_result(self, result: Dict[str, Any]) -> None:
        """打印工具调用结果"""
        if result.get("success"):
            success_msg = result.get('message', '成功')
            print(color_text(f"   ✓ {success_msg}", ColorCode.GREEN.value))
            # 如果有文件信息，显示文件路径
            if "files" in result:
                files = result["files"]
                if isinstance(files, dict):
                    for file_type, file_path in files.items():
                        print(f"      {file_type}: {file_path}")
        else:
            error_msg = result.get("error", "未知错误")
            error_preview = error_msg[:500] + "..." if len(error_msg) > 500 else error_msg
            print(color_text(f"   ✗ 失败: {error_preview}", ColorCode.RED.value))
    
    def _print_completion(self, message: Message) -> None:
        """打印完成信息"""
        print()
        print(color_text("✅ AI 完成", ColorCode.GREEN.value))
        if message.content:
            print(message.content)
    
    def _generate_solution_report(self) -> None:
        """生成解题报告（用于 PR 正文描述）"""
        if not self.problem_id:
            return
        
        report_path = Path(f"SOLUTION_REPORT_{self.problem_id}.md")
        
        # 构建报告内容
        report_content = "".join(self.reasoning_log)
        report_content += "✅ 解题完成！代码已通过编译和测试。\n\n"
        report_content += "---\n\n"
        report_content += "*本报告由 AI 自动生成，包含完整的思考过程和解题步骤。*\n"
        
        # 写入文件
        report_path.write_text(report_content, encoding='utf-8')
        
        print()
        print(color_text(f"📝 解题报告已保存: {report_path}", ColorCode.CYAN.value))
        print(color_text(f"   报告将作为 PR 的解题说明", ColorCode.CYAN.value))
    
    def _handle_stream_response(self, request_params: Dict[str, Any]) -> Message:
        """处理流式响应，实时输出 thinking 和 content"""
        stream = self.client.chat.completions.create(**request_params)
        
        full_reasoning_content = ""
        full_content = ""
        tool_calls = []
        
        # 打印思考过程标题（如果有 reasoner）
        if self.use_reasoner:
            print(color_text("🧠 思考过程:", ColorCode.CYAN.value), end="", flush=True)
        
        # 处理流式数据块
        for chunk in stream:
            if not chunk.choices:
                continue
            
            delta = chunk.choices[0].delta
            
            # 处理 reasoning_content
            if hasattr(delta, 'reasoning_content') and delta.reasoning_content:
                full_reasoning_content, self._current_reasoning = self._process_reasoning_chunk(
                    delta.reasoning_content, full_reasoning_content
                )
            
            # 处理 content
            if hasattr(delta, 'content') and delta.content:
                full_content = self._process_content_chunk(delta.content, full_content, full_reasoning_content)
            
            # 收集 tool_calls
            if hasattr(delta, 'tool_calls') and delta.tool_calls:
                tool_calls = self._process_tool_call_delta(delta.tool_calls, tool_calls)
            
            # 检查是否完成
            if chunk.choices[0].finish_reason:
                break
        
        # 流式输出结束，换行
        print()
        
        # 保存思考过程和回复内容到日志
        self._save_reasoning_to_log(full_reasoning_content, full_content)
        
        # 构建并返回 Message 对象
        return self._build_message_from_stream(full_content, full_reasoning_content, tool_calls)
    
    def _process_reasoning_chunk(self, reasoning_chunk: str, full_reasoning_content: str) -> Tuple[str, str]:
        """处理 reasoning_content 数据块"""
        full_reasoning_content += reasoning_chunk
        if not hasattr(self, '_current_reasoning'):
            self._current_reasoning = ""
        self._current_reasoning += reasoning_chunk
        print(reasoning_chunk, end="", flush=True)
        return full_reasoning_content, self._current_reasoning
    
    def _process_content_chunk(self, content_chunk: str, full_content: str, full_reasoning_content: str) -> str:
        """处理 content 数据块"""
        full_content += content_chunk
        # 如果是第一次输出 content，先换行并打印标题
        if len(full_content) == len(content_chunk):
            if self.use_reasoner and full_reasoning_content:
                print()  # 思考过程结束，换行
            print(color_text("\n💬 回复:", ColorCode.BLUE.value), end="", flush=True)
        # 实时输出
        print(content_chunk, end="", flush=True)
        return full_content
    
    def _process_tool_call_delta(self, tool_call_deltas: List, tool_calls: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
        """处理 tool_call delta"""
        for tool_call_delta in tool_call_deltas:
            index = tool_call_delta.index
            # 确保 tool_calls 列表足够大
            while len(tool_calls) <= index:
                tool_calls.append({
                    "id": "",
                    "type": "function",
                    "function": {"name": "", "arguments": ""}
                })
            
            # 更新 tool_call
            if tool_call_delta.id:
                tool_calls[index]["id"] = tool_call_delta.id
            if tool_call_delta.type:
                tool_calls[index]["type"] = tool_call_delta.type
            if hasattr(tool_call_delta, 'function'):
                if tool_call_delta.function.name:
                    tool_calls[index]["function"]["name"] = tool_call_delta.function.name
                if tool_call_delta.function.arguments:
                    tool_calls[index]["function"]["arguments"] += tool_call_delta.function.arguments
        
        return tool_calls
    
    def _save_reasoning_to_log(self, full_reasoning_content: str, full_content: str) -> None:
        """保存思考过程和回复内容到日志"""
        if hasattr(self, '_current_reasoning') and self._current_reasoning:
            self.reasoning_log.append(f"### 思考过程\n\n{self._current_reasoning}\n\n")
            self._current_reasoning = ""
        
        if full_content:
            self.reasoning_log.append(f"### AI 回复\n\n{full_content}\n\n")
    
    def _build_message_from_stream(self, full_content: str, full_reasoning_content: str, tool_calls: List[Dict[str, Any]]) -> Message:
        """从流式响应构建 Message 对象"""
        converted_tool_calls = None
        if tool_calls:
            converted_tool_calls = [
                ToolCall(
                    tc["id"],
                    tc["type"],
                    tc["function"]["name"],
                    tc["function"]["arguments"]
                )
                for tc in tool_calls if tc["id"] and tc["function"]["name"]
            ]
        
        return Message(
            content=full_content,
            reasoning_content=full_reasoning_content if (self.use_reasoner and full_reasoning_content) else None,
            tool_calls=converted_tool_calls
        )


def main():
    """主函数"""
    import argparse
    
    parser = argparse.ArgumentParser(
        description="AI 自动解决 LeetCode 题目",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 解决每日一题
  python script/leetcode/ai_solver.py
  
  # 解决指定题目
  python script/leetcode/ai_solver.py 1
  python script/leetcode/ai_solver.py --id 1
  python script/leetcode/ai_solver.py 146
        """
    )
    parser.add_argument(
        "id",
        nargs="?",
        type=int,
        help="指定要解决的题目 ID（如果不指定，则解决每日一题）"
    )
    parser.add_argument(
        "--id",
        dest="id_flag",
        type=int,
        help="指定要解决的题目 ID（与位置参数等效）"
    )
    parser.add_argument(
        "--api-key",
        help="Moonshot API Key（优先级：参数 > 环境变量 > .env 文件）"
    )
    parser.add_argument(
        "--base-url",
        default=None,
        help="API 基础 URL（优先级：参数 > 环境变量 MOONSHOT_BASE_URL > .env 文件 > 默认值）"
    )
    
    args = parser.parse_args()
    
    # 优先使用 --id 参数，其次使用位置参数
    problem_id = args.id_flag if args.id_flag is not None else args.id
    
    try:
        solver = AISolver(
            api_key=args.api_key if args.api_key else None,
            base_url=args.base_url if args.base_url else None
        )
        
        if problem_id:
            solver.solve_problem(problem_id)
        else:
            solver.solve_daily_challenge()
    except KeyboardInterrupt:
        print()
        print(color_text("操作已中断", ColorCode.YELLOW.value))
    except Exception as e:
        print(color_text(f"错误: {e}", ColorCode.RED.value))
        traceback.print_exc()


if __name__ == "__main__":
    main()
