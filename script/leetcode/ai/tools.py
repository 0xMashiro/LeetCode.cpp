#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 工具函数定义和实现
"""

import json
import subprocess
import traceback
from pathlib import Path
from typing import Dict, Any, Optional, List, Callable

from script.leetcode.api import ProblemRepository
from script.leetcode.services import SignatureParser
from script.leetcode.config import ProjectPaths, AIConfig
from script.leetcode.exceptions import LeetCodeError
from script.leetcode.utils import color_text, ColorCode


class ToolDefinition:
    """工具定义"""
    
    @classmethod
    def get_all(cls) -> List[Dict[str, Any]]:
        """获取所有工具定义"""
        return [
            cls._fetch_problem_metadata(),
            cls._create_or_update_file(),
            cls._retrieve_file_content(),
            cls._append_test_case(),
            cls._compile_project(),
            cls._execute_test_suite(),
            cls._fetch_structure_definition(),
        ]
    
    @staticmethod
    def _fetch_problem_metadata() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "fetch_problem_metadata",
                "description": """获取题目完整信息，包括：
- 题目描述（HTML格式）
- 函数签名（从代码模板自动提取）
- 题目难度、URL
- 是否为设计类题目
- 推荐的类名、测试类名、命名空间
- 参考示例代码（Two Sum普通题、LRU Cache设计题）
- core.h 头文件内容
这是解题的第一步，必须先调用此工具获取上下文。""",
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
        }
    
    @staticmethod
    def _create_or_update_file() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "create_or_update_file",
                "description": """生成文件。支持单次生成一个文件，或一次性批量生成三个文件（推荐）。

使用方式：
1. **批量生成（推荐）**：一次性生成 header、source、test 三个文件
2. **单次生成**：先生成 header/source 进行编译验证，测试文件稍后生成

策略：
- 首次生成：overwrite_existing=false（默认），如果文件已存在会报错
- 修复后重新生成：overwrite_existing=true，会覆盖旧文件""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID"
                        },
                        "files": {
                            "type": "array",
                            "description": "要生成的文件列表。支持批量生成多个文件，例如 [{file_category: \"header\", content: \"...\"}, {file_category: \"source\", content: \"...\"}, {file_category: \"test\", content: \"...\"}]",
                            "items": {
                                "type": "object",
                                "properties": {
                                    "file_category": {
                                        "type": "string",
                                        "description": "文件类型",
                                        "enum": ["header", "source", "test"]
                                    },
                                    "content": {
                                        "type": "string",
                                        "description": "文件完整内容"
                                    }
                                },
                                "required": ["file_category", "content"]
                            }
                        },
                        "overwrite_existing": {
                            "type": "boolean",
                            "description": "是否强制覆盖已存在的文件。首次生成为false，修复后重新生成为true",
                            "default": False
                        }
                    },
                    "required": ["problem_id", "files"],
                    "additionalProperties": False
                }
            }
        }
    
    @staticmethod
    def _retrieve_file_content() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "retrieve_file_content",
                "description": "读取已生成的文件内容。测试失败或编译错误时，使用此工具查看当前文件内容进行分析",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID"
                        },
                        "file_category": {
                            "type": "string",
                            "description": "文件类型",
                            "enum": ["header", "source", "test"]
                        }
                    },
                    "required": ["problem_id", "file_category"],
                    "additionalProperties": False
                }
            }
        }
    
    @staticmethod
    def _append_test_case() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "append_test_case",
                "description": """向现有测试文件追加新的测试用例。

使用场景：
- LeetCode 提交失败后，将失败的测试用例添加到本地测试文件
- 修复特定边界情况的测试

特点：
- 只追加，不覆盖已有测试用例
- 自动处理命名空间和测试类结构
- 自动添加 TEST_P 宏和必要的包含头""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID"
                        },
                        "test_name": {
                            "type": "string",
                            "description": "测试用例名称，建议使用描述性名称（如 WrongAnswerCase1, EdgeCaseEmptyArray）"
                        },
                        "test_code": {
                            "type": "string",
                            "description": "测试代码内容，只需要 TEST_P 宏内部的代码，不需要完整的 TEST_P 包装"
                        }
                    },
                    "required": ["problem_id", "test_name", "test_code"],
                    "additionalProperties": False
                }
            }
        }
    
    @staticmethod
    def _compile_project() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "compile_project",
                "description": """编译项目。
支持两种模式：
1. **增量编译**（推荐）：提供 problem_id 参数，只编译指定题目（快速）
2. **全量编译**：不提供参数，编译整个项目（包括所有历史题目，较慢）

优先使用增量编译，速度更快且不受 CMake GLOB 缓存影响。""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID（如 1, 2, 461）。如果提供，只编译该题目（增量编译，更快）"
                        }
                    },
                    "required": [],
                    "additionalProperties": False
                }
            }
        }
    
    @staticmethod
    def _execute_test_suite() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "execute_test_suite",
                "description": """运行指定题目的测试用例。
返回结果包含：
- is_successful: 是否通过
- error_type: 错误类型（内存错误/断言失败/超时/编译错误）
- error_message: 详细错误描述
- suggestion: 修复建议
- output: 完整输出""",
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
        }
    
    @staticmethod
    def _fetch_structure_definition() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "fetch_structure_definition",
                "description": """获取项目中预定义数据结构的实现代码。
处理涉及树、链表、队列、栈的题目时，必须先调用此工具了解：
1. 数据结构的定义（成员变量、构造函数）
2. 内存管理方式（是否需要手动delete）
3. 可用的辅助函数（如constructTree、constructLinkedList）
支持类型：tree（TreeNode）、linked-list（ListNode/MyLinkedList）、queue（MyQueue）、stack（MyStack）""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "structure_type": {
                            "type": "string",
                            "description": "数据结构名称",
                            "enum": ["tree", "linked-list", "queue", "stack"]
                        }
                    },
                    "required": ["structure_type"],
                    "additionalProperties": False
                }
            }
        }


class ToolExecutor:
    """工具执行器"""
    
    def __init__(self, repository: ProblemRepository):
        self.repository = repository
    
    def execute(self, name: str, arguments: Dict[str, Any]) -> Dict[str, Any]:
        """执行工具函数"""
        executors: Dict[str, Callable] = {
            "fetch_problem_metadata": self._fetch_problem_metadata,
            "create_or_update_file": self._create_or_update_file,
            "retrieve_file_content": self._retrieve_file_content,
            "append_test_case": self._append_test_case,
            "compile_project": self._compile_project,
            "execute_test_suite": self._execute_test_suite,
            "fetch_structure_definition": self._fetch_structure_definition,
        }
        
        executor = executors.get(name)
        if not executor:
            return {"is_successful": False, "error_message": f"未知工具函数: {name}"}
        
        try:
            return executor(**arguments)
        except Exception as e:
            return {
                "is_successful": False, 
                "error_message": f"{str(e)}\n{traceback.format_exc()}"
            }
    
    def _fetch_problem_metadata(self, problem_id: int) -> Dict[str, Any]:
        """获取题目信息"""
        try:
            problem_data = self.repository.get_detail_by_id(problem_id, include_code=True)
            problem_info = self.repository.get_by_id(problem_id)
            
            # 提取函数签名
            code_template = problem_data.get_cpp_code_template()
            signature = None
            if code_template:
                signature = SignatureParser.extract_from_code_template(code_template)
            
            # 读取参考示例文件
            examples = self._load_reference_implementations()
            
            # 读取 core.h
            core_header = self._read_file_safe(Path(ProjectPaths.CORE_HEADER))
            
            # 计算类名
            class_base = self._convert_to_class_name(problem_info.slug)
            
            return {
                "is_successful": True,
                "problem_id": problem_id,
                "title": problem_data.title,
                "slug": problem_data.slug,
                "difficulty": problem_data.difficulty,
                "url": f"https://leetcode.com/problems/{problem_data.slug}/",
                "function_signature": signature,
                "code_template": code_template,
                "content": problem_data.content,
                "is_design": self.repository.is_design_problem(problem_id),
                "solution_class_name": f"{class_base}Solution",
                "solution_class_base": class_base,
                "test_class_name": f"{class_base}Test",
                "namespace": f"problem_{problem_id}",
                "core_header": core_header,
                **examples
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}
    
    def _create_or_update_file(
        self, 
        problem_id: int, 
        files: list,
        overwrite_existing: bool = False
    ) -> Dict[str, Any]:
        """生成文件（支持批量生成）"""
        try:
            problem_info = self.repository.get_by_id(problem_id)
            
            generated_files = []
            errors = []
            
            for file_info in files:
                file_category = file_info["file_category"]
                content = file_info["content"]
                
                # 根据文件类型确定路径
                if file_category == "header":
                    file_path = Path(f"{ProjectPaths.INCLUDE_PROBLEMS}/{problem_info.slug}.h")
                elif file_category == "source":
                    file_path = Path(f"{ProjectPaths.SRC_PROBLEMS}/{problem_info.slug}.cpp")
                elif file_category == "test":
                    file_path = Path(f"{ProjectPaths.TEST_PROBLEMS}/{problem_info.slug}.cpp")
                else:
                    errors.append(f"未知文件类型: {file_category}")
                    continue
                
                # 检查文件是否已存在
                if file_path.exists() and not overwrite_existing:
                    errors.append(f"文件已存在: {file_path}")
                    continue
                
                # 确保目录存在
                file_path.parent.mkdir(parents=True, exist_ok=True)
                
                # 写入文件
                file_path.write_text(content, encoding='utf-8')
                generated_files.append({
                    "file_category": file_category,
                    "file_path": str(file_path)
                })
            
            if errors:
                return {
                    "is_successful": False,
                    "error_message": "; ".join(errors),
                    "generated_files": generated_files
                }
            
            return {
                "is_successful": True,
                "status_message": f"已生成 {len(generated_files)} 个文件" + ("（覆盖旧文件）" if overwrite_existing else ""),
                "generated_files": generated_files
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}
    
    def _retrieve_file_content(self, problem_id: int, file_category: str) -> Dict[str, Any]:
        """读取文件内容"""
        try:
            problem_info = self.repository.get_by_id(problem_id)
            
            if file_category == "header":
                file_path = Path(f"{ProjectPaths.INCLUDE_PROBLEMS}/{problem_info.slug}.h")
            elif file_category == "source":
                file_path = Path(f"{ProjectPaths.SRC_PROBLEMS}/{problem_info.slug}.cpp")
            elif file_category == "test":
                file_path = Path(f"{ProjectPaths.TEST_PROBLEMS}/{problem_info.slug}.cpp")
            else:
                return {"is_successful": False, "error_message": f"未知文件类型: {file_category}"}
            
            if not file_path.exists():
                return {
                    "is_successful": False,
                    "error_message": f"文件不存在: {file_path}"
                }
            
            content = file_path.read_text(encoding='utf-8')
            
            return {
                "is_successful": True,
                "file_category": file_category,
                "file_path": str(file_path),
                "content": content
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}
    
    def _append_test_case(self, problem_id: int, test_name: str, test_code: str) -> Dict[str, Any]:
        """向测试文件追加新的测试用例"""
        try:
            problem_info = self.repository.get_by_id(problem_id)
            test_path = Path(f"{ProjectPaths.TEST_PROBLEMS}/{problem_info.slug}.cpp")
            
            # 生成类名（从 slug 转换）
            class_base = self._convert_to_class_name(problem_info.slug)
            
            if not test_path.exists():
                return {
                    "is_successful": False,
                    "error_message": f"测试文件不存在: {test_path}"
                }
            
            # 读取现有内容
            content = test_path.read_text(encoding='utf-8')
            
            # 在 INSTANTIATE_TEST_SUITE_P 之前插入新的测试用例
            # 查找 INSTANTIATE_TEST_SUITE_P 的位置
            import re
            match = re.search(r'INSTANTIATE_TEST_SUITE_P\(', content)
            if not match:
                return {
                    "is_successful": False,
                    "error_message": "无法找到 INSTANTIATE_TEST_SUITE_P 标记"
                }
            
            insert_pos = match.start()
            
            # 处理 test_code 的缩进（确保每行有 2 空格缩进）
            indented_code = '\n'.join(
                '  ' + line if line.strip() else line
                for line in test_code.strip().split('\n')
            )
            
            # 构建新的测试用例代码
            # 格式示例：
            # 
            # TEST_P(ClassNameTest, TestName) {
            #   // test body indented by 2 spaces
            # }
            # 
            test_case = f'''
// LeetCode 失败用例: {test_name}
TEST_P({class_base}Test, {test_name}) {{
{indented_code}
}}
'''
            
            # 插入新测试用例
            new_content = content[:insert_pos] + test_case + content[insert_pos:]
            
            # 写回文件
            test_path.write_text(new_content, encoding='utf-8')
            
            return {
                "is_successful": True,
                "message": f"测试用例 '{test_name}' 已添加到 {test_path}",
                "test_file": str(test_path)
            }
            
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}
    
    def _compile_project(self, problem_id: Optional[int] = None) -> Dict[str, Any]:
        """编译项目
        
        Args:
            problem_id: 如果指定，使用增量编译只编译该题目；否则全量编译
        """
        try:
            if problem_id:
                # 增量编译：只编译指定题目（使用 just multi，更快且不受 GLOB 缓存影响）
                result = subprocess.run(
                    ["just", "multi", str(problem_id)],
                    capture_output=True,
                    text=True,
                    timeout=AIConfig.BUILD_TIMEOUT
                )
            else:
                # 全量编译：编译整个项目
                # 强制重新配置 CMake，确保能检测到新添加的文件
                cmake_cache = Path("build/CMakeCache.txt")
                if cmake_cache.exists():
                    cmake_cache.unlink()
                
                result = subprocess.run(
                    ["just", "build"],
                    capture_output=True,
                    text=True,
                    timeout=AIConfig.BUILD_TIMEOUT
                )
            
            if result.returncode == 0:
                return {
                    "is_successful": True,
                    "status_message": "编译成功",
                    "output": result.stdout[-2000:] if len(result.stdout) > 2000 else result.stdout
                }
            else:
                # 分析编译错误
                error_analysis = self._classify_compilation_error(result.stderr + result.stdout)
                
                return {
                    "is_successful": False,
                    "error_message": "编译失败",
                    "error_type": error_analysis["type"],
                    "error_details": error_analysis["details"],
                    "suggestion": error_analysis["suggestion"],
                    "output": result.stderr + result.stdout
                }
        except subprocess.TimeoutExpired:
            return {
                "is_successful": False,
                "error_message": "编译超时",
                "error_type": "timeout",
                "suggestion": "编译时间过长，可能是代码有无限递归或其他问题"
            }
        except Exception as e:
            return {"is_successful": False, "error_message": str(e)}
    
    def _classify_compilation_error(self, output: str) -> Dict[str, str]:
        """分析编译错误"""
        output_lower = output.lower()
        
        # 语法错误
        if any(x in output_lower for x in ['syntax error', 'expected', 'before', 'after']):
            return {
                'type': '语法错误',
                'details': 'C++ 语法错误',
                'suggestion': '检查语法：括号匹配、分号、类型定义等'
            }
        
        # 未定义引用
        if 'undefined reference' in output_lower or 'undefined symbol' in output_lower:
            return {
                'type': '链接错误',
                'details': '函数或变量未定义',
                'suggestion': '检查函数声明和定义是否匹配，是否缺少实现'
            }
        
        # 类型不匹配
        if any(x in output_lower for x in ['cannot convert', 'no matching function', 'invalid conversion']):
            return {
                'type': '类型错误',
                'details': '类型不匹配',
                'suggestion': '检查函数参数类型、返回值类型是否与声明一致'
            }
        
        # 头文件找不到
        if 'no such file' in output_lower or 'cannot find' in output_lower:
            return {
                'type': '头文件错误',
                'details': '找不到头文件',
                'suggestion': '检查 #include 路径是否正确'
            }
        
        return {
            'type': '编译错误',
            'details': '编译失败',
            'suggestion': '查看详细错误信息进行修复'
        }
    
    def _execute_test_suite(self, problem_id: int) -> Dict[str, Any]:
        """运行测试"""
        import sys
        try:
            result = subprocess.run(
                [sys.executable, "-m", "script.leetcode.cli", "test", str(problem_id)],
                capture_output=True,
                text=True,
                timeout=AIConfig.TEST_TIMEOUT
            )
            
            output = result.stdout + result.stderr
            
            if result.returncode == 0:
                return {
                    "is_successful": True,
                    "status_message": "所有测试通过",
                    "output": output
                }
            else:
                # 分析失败类型
                error_analysis = self._analyze_test_failure(output)
                
                return {
                    "is_successful": False,
                    "error_message": f"测试失败: {error_analysis['type']}",
                    "error_type": error_analysis["type"],
                    "error_details": error_analysis["details"],
                    "output": output,
                    "suggestion": error_analysis["suggestion"]
                }
        except subprocess.TimeoutExpired:
            return {
                "is_successful": False, 
                "error_message": "测试超时",
                "error_type": "timeout",
                "suggestion": "算法可能存在无限循环或时间复杂度过高，请检查循环条件和算法复杂度"
            }
        except Exception as e:
            return {
                "is_successful": False, 
                "error_message": str(e),
                "error_type": "exception"
            }
    
    def _analyze_test_failure(self, output: str) -> Dict[str, str]:
        """分析测试失败类型"""
        output_lower = output.lower()
        
        # 段错误/内存错误
        if any(x in output_lower for x in ['segmentation fault', 'sigsegv', 'core dumped', 'double free']):
            return {
                'type': '内存错误',
                'details': '程序发生段错误或内存访问错误',
                'suggestion': '检查数组越界、空指针访问、迭代器失效、双重释放等问题。使用 valgrind 或地址消毒器可以帮助定位'
            }
        
        # 断言失败
        if 'expect' in output_lower or 'assert' in output_lower:
            return {
                'type': '结果错误',
                'details': '测试结果与预期不符',
                'suggestion': '1. 检查算法逻辑是否正确\n2. 检查边界条件处理（空输入、单元素、最大值等）\n3. 检查返回值是否符合题目要求\n4. 检查自己构造的测试用例是否正确'
            }
        
        # 编译错误（虽然应该在 build 阶段捕获）
        if any(x in output_lower for x in ['error:', 'undefined reference', 'cannot find']):
            return {
                'type': '编译错误',
                'details': '代码编译失败',
                'suggestion': '检查头文件包含、函数签名一致性、语法错误等'
            }
        
        # 超时
        if 'timeout' in output_lower or 'time limit' in output_lower:
            return {
                'type': '超时',
                'details': '测试运行时间超过限制',
                'suggestion': '算法时间复杂度过高，需要优化。考虑使用更高效的数据结构或算法'
            }
        
        # 默认
        return {
            'type': '未知错误',
            'details': '测试失败，具体原因不明',
            'suggestion': '请仔细查看输出信息，检查代码逻辑和测试用例'
        }
    
    def _fetch_structure_definition(self, structure_type: str) -> Dict[str, Any]:
        """获取数据结构实现"""
        supported = ["tree", "linked-list", "queue", "stack"]
        
        if structure_type not in supported:
            return {
                "is_successful": False,
                "error_message": f"未知的数据结构: {structure_type}。支持: {', '.join(supported)}"
            }
        
        header_path = Path(f"{ProjectPaths.INCLUDE_UTILS}/{structure_type}.h")
        source_path = Path(f"{ProjectPaths.SRC_UTILS}/{structure_type}.cpp")
        
        if not header_path.exists():
            return {
                "is_successful": False,
                "error_message": f"头文件不存在: {header_path}"
            }
        
        return {
            "is_successful": True,
            "structure_type": structure_type,
            "header_file": str(header_path),
            "header_content": self._read_file_safe(header_path),
            "source_file": str(source_path) if source_path.exists() else None,
            "source_content": self._read_file_safe(source_path) if source_path.exists() else None
        }
    
    def _load_reference_implementations(self) -> Dict[str, Any]:
        """读取示例文件"""
        from script.leetcode.config import ExampleProblems
        
        ordinary = self._read_example(ExampleProblems.ORDINARY_SLUG)
        design = self._read_example(ExampleProblems.DESIGN_SLUG)
        
        return {
            "example_ordinary": {
                **ordinary,
                "description": "普通题目示例（Two Sum - 题目 ID 1）：使用 SolutionBase 模式，支持多策略实现"
            },
            "example_design": {
                **design,
                "description": "设计类题目示例（LRU Cache - 题目 ID 146）：直接实现类方法，不使用 SolutionBase"
            }
        }
    
    def _read_example(self, slug: str) -> Dict[str, str]:
        """读取单个示例"""
        header_path = Path(f"{ProjectPaths.INCLUDE_PROBLEMS}/{slug}.h")
        source_path = Path(f"{ProjectPaths.SRC_PROBLEMS}/{slug}.cpp")
        test_path = Path(f"{ProjectPaths.TEST_PROBLEMS}/{slug}.cpp")
        
        return {
            "header": self._read_file_safe(header_path),
            "source": self._read_file_safe(source_path),
            "test": self._read_file_safe(test_path),
        }
    
    @staticmethod
    def _read_file_safe(file_path: Path) -> str:
        """安全读取文件"""
        try:
            return file_path.read_text(encoding='utf-8')
        except (FileNotFoundError, IOError):
            return ""
    
    @staticmethod
    def _convert_to_class_name(slug: str) -> str:
        """将 slug 转换为类名"""
        return "".join(word.capitalize() for word in slug.split("-"))
