#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 自动解题器
使用 DeepSeek API 的 Function Calling 功能自动解决 LeetCode 题目

依赖安装: pip install openai
"""

import os
import json
import subprocess
from pathlib import Path
from typing import Dict, Any, Optional, List
from openai import OpenAI
from dotenv import load_dotenv

from graphql_client import get_client
from core import LeetCodeDB, LeetCodeHelper, ProblemInfo, SignatureParser
from utils import color_text, ColorCode


class AISolver:
    """AI 自动解题器"""
    
    def __init__(self, api_key: Optional[str] = None, base_url: Optional[str] = None):
        """初始化 AI 解题器
        
        Args:
            api_key: DeepSeek API Key，优先级：参数 > 环境变量 > .env 文件
            base_url: API 基础 URL，优先级：参数 > 环境变量 DEEPSEEK_BASE_URL > .env 文件 > 默认值
        """
        # 加载 .env 文件（如果存在）
        # 从项目根目录查找 .env 文件
        project_root = Path(__file__).parent.parent.parent
        env_path = project_root / ".env"
        if env_path.exists():
            load_dotenv(dotenv_path=env_path)
        else:
            # 如果项目根目录没有，尝试当前目录
            load_dotenv()
        
        # 获取 API Key（优先级：参数 > 环境变量 > .env 文件）
        self.api_key = api_key or os.getenv("DEEPSEEK_API_KEY")
        if not self.api_key:
            raise ValueError(
                "请设置 DEEPSEEK_API_KEY：\n"
                "  1. 创建 .env 文件并添加 DEEPSEEK_API_KEY=your_key\n"
                "  2. 或设置环境变量: export DEEPSEEK_API_KEY=your_key\n"
                "  3. 或通过命令行参数: --api-key your_key\n"
                "  参考 env.example 文件"
            )
        
        # 获取 base_url（优先级：参数 > 环境变量 > .env 文件 > 默认值）
        if base_url is None:
            base_url = os.getenv("DEEPSEEK_BASE_URL", "https://api.deepseek.com")
        
        self.client = OpenAI(
            api_key=self.api_key,
            base_url=base_url,
        )
        self.leetcode_client = get_client()
        self.db = LeetCodeDB()
        self.messages: List[Dict[str, Any]] = []
        self.use_reasoner = os.getenv("DEEPSEEK_USE_REASONER", "false").lower() == "true"
        
        # 用于收集思考过程和解题报告
        self.reasoning_log: List[str] = []  # 存储所有思考过程
        self.solution_summary: List[str] = []  # 存储解题摘要
        self.problem_id: Optional[int] = None
        self.problem_title: Optional[str] = None
        self.problem_slug: Optional[str] = None
        
        # 定义工具函数
        self.tools = [
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
        ]
    
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
            
            # 获取题目描述（如果有）
            content = problem_data.get("content", "")
            
            # 读取参考示例文件和核心头文件
            is_design = self.db.is_design_problem(problem_id)
            
            # 生成正确的类名（使用 LeetCodeHelper 的逻辑）
            helper = LeetCodeHelper(problem_info=problem_info, is_design=is_design)
            solution_class_base = helper.solution_class_name  # 例如：DeleteColumnsToMakeSorted
            solution_class_name = f"{solution_class_base}Solution"  # 例如：DeleteColumnsToMakeSortedSolution
            test_class_name = f"{solution_class_base}Test"  # 例如：DeleteColumnsToMakeSortedTest
            
            # 读取 core.h（项目核心头文件，包含所有 STL 和工具类）
            try:
                core_header = Path("include/leetcode/core.h").read_text(encoding='utf-8')
            except Exception:
                core_header = ""
            
            # 读取参考示例文件
            try:
                two_sum_header = Path("include/leetcode/problems/two-sum.h").read_text(encoding='utf-8')
                two_sum_source = Path("src/leetcode/problems/two-sum.cpp").read_text(encoding='utf-8')
                two_sum_test = Path("test/leetcode/problems/two-sum.cpp").read_text(encoding='utf-8')
                
                lru_cache_header = Path("include/leetcode/problems/lru-cache.h").read_text(encoding='utf-8')
                lru_cache_source = Path("src/leetcode/problems/lru-cache.cpp").read_text(encoding='utf-8')
                lru_cache_test = Path("test/leetcode/problems/lru-cache.cpp").read_text(encoding='utf-8')
            except Exception:
                # 如果示例文件不存在，使用空字符串
                two_sum_header = two_sum_source = two_sum_test = ""
                lru_cache_header = lru_cache_source = lru_cache_test = ""
            
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
            
            # 文件路径
            header_path = Path(f"include/leetcode/problems/{problem_info.slug}.h")
            source_path = Path(f"src/leetcode/problems/{problem_info.slug}.cpp")
            test_path = Path(f"test/leetcode/problems/{problem_info.slug}.cpp")
            
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
                if header_path.exists():
                    header_path.unlink()
                    deleted_files.append(str(header_path))
                if source_path.exists():
                    source_path.unlink()
                    deleted_files.append(str(source_path))
                if test_path.exists():
                    test_path.unlink()
                    deleted_files.append(str(test_path))
            
            # 确保目录存在
            header_path.parent.mkdir(parents=True, exist_ok=True)
            source_path.parent.mkdir(parents=True, exist_ok=True)
            test_path.parent.mkdir(parents=True, exist_ok=True)
            
            # 写入文件
            with open(header_path, 'w', encoding='utf-8') as f:
                f.write(header_content)
            
            with open(source_path, 'w', encoding='utf-8') as f:
                f.write(source_content)
            
            with open(test_path, 'w', encoding='utf-8') as f:
                f.write(test_content)
            
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
            import traceback
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
                timeout=120
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
            helper = LeetCodeHelper(problem_info=problem_info)
            
            result = subprocess.run(
                ["python3", "script/leetcode/cli.py", "test", str(problem_id)],
                capture_output=True,
                text=True,
                timeout=60
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
        except Exception as e:
            return {
                "success": False,
                "error": str(e)
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
            except:
                raise ValueError(error_msg)
    
    def _call_tool(self, tool_call) -> Dict[str, Any]:
        """调用工具函数"""
        function_name = tool_call.function.name
        
        try:
            arguments = self._parse_tool_arguments(tool_call.function.arguments)
        except ValueError as e:
            return {"success": False, "error": str(e)}
        
        # 路由到对应的工具函数
        tool_map = {
            "get_problem_info": self.get_problem_info,
            "generate_all_files": self.generate_all_files,
            "build_project": self.build_project,
            "run_tests": self.run_tests,
        }
        
        if function_name in tool_map:
            return tool_map[function_name](**arguments)
        else:
            return {"success": False, "error": f"未知工具函数: {function_name}"}
    
    def solve_daily_challenge(self) -> None:
        """解决每日一题"""
        print(color_text("🚀 开始解决每日一题", ColorCode.CYAN.value))
        print()
        
        # 获取每日一题
        try:
            daily = self.leetcode_client.get_daily_challenge()
            question = daily["question"]
            problem_id = int(question["questionFrontendId"])
            
            self.problem_id = problem_id
            self.problem_title = question['title']
            self.problem_slug = question['titleSlug']
            
            print(color_text(f"📋 今日题目: [{problem_id}] {question['title']}", ColorCode.BLUE.value))
            print(color_text(f"🔗 URL: https://leetcode.com/problems/{question['titleSlug']}/", ColorCode.BLUE.value))
            print()
            
            # 记录题目信息到解题报告
            self.reasoning_log.append(f"# LeetCode 每日一题：{problem_id}. {question['title']}\n")
            self.reasoning_log.append(f"**题目链接**: https://leetcode.com/problems/{question['titleSlug']}/\n")
            self.reasoning_log.append(f"**难度**: {question.get('difficulty', 'Unknown')}\n\n")
            
            # 检查文件是否已存在
            problem_info = self.db.get_by_id(problem_id)
            header_path = Path(f"include/leetcode/problems/{problem_info.slug}.h")
            source_path = Path(f"src/leetcode/problems/{problem_info.slug}.cpp")
            test_path = Path(f"test/leetcode/problems/{problem_info.slug}.cpp")
            
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
                return
            else:
                self.reasoning_log.append("## 解题过程\n\n")
            
            # 初始化对话
            self.messages = [{
                "role": "system",
                "content": """你是一个专业的 C++ 算法工程师，擅长解决 LeetCode 题目。

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

重要：测试用例规则：
- 题目自带的测试用例是必须通过的
- 你在自己构造测试用例时需确保你构造的测试用例是正确的，并且能够覆盖所有可能的情况
- 测试用例不在于数量，而在于质量

工作流程：
1. 调用 get_problem_info 获取题目信息、参考示例和**正确的类名、测试类名、命名空间**
2. 根据题目类型（普通/设计类）选择合适的示例
3. 分析题目要求，设计算法
4. 调用 generate_all_files 生成完整的三个文件（严格按照示例格式和提供的类名）
5. 调用 build_project 编译验证
6. 调用 run_tests 运行测试
7. 如果编译或测试失败，根据错误信息修复后，调用 generate_all_files 时设置 force_regenerate=true 来重新生成文件

重要提示：你的思考过程和解题步骤会被记录并作为 GitHub Pull Request 的解题报告。请在思考过程中：
- 描述你对题目和参考示例的理解
- 详细说明算法思路和设计决策（如果有多种算法，先从最容易想到的算法开始，再逐步优化）
- 解释时间复杂度和空间复杂度
- 说明遇到的困难和解决方案
- 总结解题的关键点

你的思考过程也应当以 Markdown 格式输出，以及注意代码和数学公式格式，方便后续生成解题报告。
在最终的解题报告中不需要提到工作流程中的 function calling, 仅描述你的思考过程和解题步骤。

请严格按照参考示例的格式和提供的类名生成代码，确保能够直接编译和测试。"""
            }, {
                "role": "user",
                "content": f"请帮我解决 LeetCode 每日一题：题目 ID {problem_id}"
            }]
            
            # 清除历史消息中的 reasoning_content（节省带宽）
            self._clear_reasoning_content()
            
            # 开始对话循环
            max_iterations = 20
            model_name = "deepseek-reasoner" if self.use_reasoner else "deepseek-chat"
            
            self._print_model_info()
            
            for iteration in range(max_iterations):
                print(color_text(f"💭 AI 思考中... (第 {iteration + 1} 轮)", ColorCode.YELLOW.value))
                
                # 准备请求参数（启用流式输出）
                request_params = {
                    "model": model_name,
                    "messages": self.messages,
                    "tools": self.tools,
                    "stream": True  # 启用流式输出
                }
                
                # 如果使用 reasoner 模型，需要启用 thinking mode
                if self.use_reasoner:
                    request_params["extra_body"] = {"thinking": {"type": "enabled"}}
                
                try:
                    # 流式处理响应
                    message = self._handle_stream_response(request_params)
                except Exception as e:
                    print(color_text(f"❌ API 调用错误: {e}", ColorCode.RED.value))
                    import traceback
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
                    # 生成解题报告
                    self._generate_solution_report()
                    break
            else:
                print(color_text("⚠️ 达到最大迭代次数，停止处理", ColorCode.YELLOW.value))
                print(color_text("提示: 可以增加 max_iterations 或检查是否有循环调用", ColorCode.YELLOW.value))
                
        except Exception as e:
            print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
            import traceback
            traceback.print_exc()
    
    def _clear_reasoning_content(self) -> None:
        """清除历史消息中的 reasoning_content（节省带宽）"""
        if self.use_reasoner:
            for msg in self.messages:
                if isinstance(msg, dict) and "reasoning_content" in msg:
                    msg["reasoning_content"] = None
    
    def _print_model_info(self) -> None:
        """打印模型信息"""
        if self.use_reasoner:
            print(color_text("🧠 使用 deepseek-reasoner 模型（思考模式）", ColorCode.CYAN.value))
        else:
            print(color_text("💬 使用 deepseek-chat 模型", ColorCode.CYAN.value))
        print()
    
    def _print_ai_response(self, message) -> None:
        """打印 AI 响应内容"""
        # 显示 reasoning content（如果有）
        if hasattr(message, 'reasoning_content') and message.reasoning_content:
            reasoning_preview = message.reasoning_content[:200] + "..." if len(message.reasoning_content) > 200 else message.reasoning_content
            print(color_text("🧠 思考过程:", ColorCode.CYAN.value))
            print(f"   {reasoning_preview}")
        
        # 显示 content（如果有）
        if message.content:
            content_preview = message.content[:200] + "..." if len(message.content) > 200 else message.content
            print(color_text("💬 回复:", ColorCode.BLUE.value))
            print(f"   {content_preview}")
    
    def _build_message_to_save(self, message) -> Dict[str, Any]:
        """构建要保存的消息"""
        message_to_save = {
            "role": "assistant",
            "content": message.content or "",
        }
        
        # 如果使用 reasoner，保存 reasoning_content
        if self.use_reasoner and hasattr(message, 'reasoning_content') and message.reasoning_content:
            message_to_save["reasoning_content"] = message.reasoning_content
        
        # 如果有 tool_calls，也保存
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
    
    def _handle_tool_calls(self, tool_calls) -> None:
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
                import traceback
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
    
    def _print_completion(self, message) -> None:
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
        with open(report_path, 'w', encoding='utf-8') as f:
            f.write(report_content)
        
        print()
        print(color_text(f"📝 解题报告已保存: {report_path}", ColorCode.CYAN.value))
        print(color_text(f"   报告将作为 PR 的解题说明", ColorCode.CYAN.value))
    
    def _handle_stream_response(self, request_params: Dict[str, Any]) -> Any:
        """处理流式响应，实时输出 thinking 和 content"""
        import sys
        
        # 创建流式响应
        stream = self.client.chat.completions.create(**request_params)
        
        # 用于累积完整消息
        full_reasoning_content = ""
        full_content = ""
        tool_calls = []
        finish_reason = None
        
        # 打印思考过程标题（如果有 reasoner）
        if self.use_reasoner:
            print(color_text("🧠 思考过程:", ColorCode.CYAN.value), end="", flush=True)
        
            # 处理流式数据块
        for chunk in stream:
            if not chunk.choices:
                continue
            
            delta = chunk.choices[0].delta
            
            # 处理 reasoning_content（流式输出）
            if hasattr(delta, 'reasoning_content') and delta.reasoning_content:
                reasoning_chunk = delta.reasoning_content
                full_reasoning_content += reasoning_chunk
                # 记录到思考日志（用于 PR 报告）
                if not hasattr(self, '_current_reasoning'):
                    self._current_reasoning = ""
                self._current_reasoning += reasoning_chunk
                # 实时输出（不换行，流式显示）
                print(reasoning_chunk, end="", flush=True)
            
            # 处理 content（流式输出）
            if hasattr(delta, 'content') and delta.content:
                content_chunk = delta.content
                full_content += content_chunk
                # 如果是第一次输出 content，先换行并打印标题
                if len(full_content) == len(content_chunk):
                    if self.use_reasoner and full_reasoning_content:
                        print()  # 思考过程结束，换行
                    print(color_text("\n💬 回复:", ColorCode.BLUE.value), end="", flush=True)
                # 实时输出
                print(content_chunk, end="", flush=True)
            
            # 收集 tool_calls
            if hasattr(delta, 'tool_calls') and delta.tool_calls:
                for tool_call_delta in delta.tool_calls:
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
            
            # 检查是否完成
            if chunk.choices[0].finish_reason:
                finish_reason = chunk.choices[0].finish_reason
                break
        
        # 流式输出结束，换行
        print()
        
        # 保存思考过程到日志（如果有）
        if hasattr(self, '_current_reasoning') and self._current_reasoning:
            self.reasoning_log.append(f"### 思考过程\n\n{self._current_reasoning}\n\n")
            self._current_reasoning = ""
        
        # 保存回复内容到日志（如果有）
        if full_content:
            self.reasoning_log.append(f"### AI 回复\n\n{full_content}\n\n")
        
        # 构建完整的 message 对象（使用简单的类来模拟 response.choices[0].message）
        class Message:
            def __init__(self, content, reasoning_content=None, tool_calls=None):
                self.content = content
                self.reasoning_content = reasoning_content
                self.tool_calls = tool_calls
        
        class ToolCall:
            def __init__(self, call_id, call_type, function_name, function_arguments):
                self.id = call_id
                self.type = call_type
                self.function = type('obj', (object,), {
                    'name': function_name,
                    'arguments': function_arguments
                })()
        
        # 转换 tool_calls
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
        
        message = Message(
            content=full_content,
            reasoning_content=full_reasoning_content if (self.use_reasoner and full_reasoning_content) else None,
            tool_calls=converted_tool_calls
        )
        
        return message


def main():
    """主函数"""
    import argparse
    
    parser = argparse.ArgumentParser(description="AI 自动解决 LeetCode 每日一题")
    parser.add_argument(
        "--api-key",
        help="DeepSeek API Key（优先级：参数 > 环境变量 > .env 文件）"
    )
    parser.add_argument(
        "--base-url",
        default=None,
        help="API 基础 URL（优先级：参数 > 环境变量 DEEPSEEK_BASE_URL > .env 文件 > 默认值）"
    )
    
    args = parser.parse_args()
    
    try:
        # base_url 如果是 None，让 AISolver 自己处理默认值
        solver = AISolver(
            api_key=args.api_key if args.api_key else None,
            base_url=args.base_url if args.base_url else None
        )
        solver.solve_daily_challenge()
    except KeyboardInterrupt:
        print()
        print(color_text("操作已中断", ColorCode.YELLOW.value))
    except Exception as e:
        print(color_text(f"错误: {e}", ColorCode.RED.value))
        import traceback
        traceback.print_exc()


if __name__ == "__main__":
    main()

