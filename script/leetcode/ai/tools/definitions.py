#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
模型可见的工具 JSON Schema 集合。

每个静态方法返回一个符合 OpenAI Tool Calling 规范的 function 定义。
`ToolDefinition.get_all()` 汇总后由 solver 喂给 chat.completions API。
"""

from typing import Any, Dict, List


class ToolDefinition:
    """提供给模型的工具 JSON Schema。"""

    @classmethod
    def get_all(cls) -> List[Dict[str, Any]]:
        """返回所有工具定义列表，喂给 chat.completions API 的 tools 参数。"""
        return [
            cls._fetch_problem_metadata(),
            cls._create_or_update_file(),
            cls._retrieve_file_content(),
            cls._append_test_case(),
            cls._compile_and_test(),
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
                    "additionalProperties": False,
                },
            },
        }

    @staticmethod
    def _create_or_update_file() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "create_or_update_file",
                "description": """生成或更新源文件、头文件、测试文件。

🚨 首次生成题目（三个文件都不存在）必须一次性提交全部三个 category（header + source + test）。
缺任何一个会被拒绝并返回引导错误 —— 不要先提交 source 再试图编译，会卡死在编译失败循环里。

后续修复：可以单独更新任意一个或多个文件（必须 overwrite_existing=true）。

示例：
  首次生成 → files=[{category:"header",...},{category:"source",...},{category:"test",...}]
  仅修 source → files=[{category:"source",...}], overwrite_existing=true""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID",
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
                                        "enum": ["header", "source", "test"],
                                    },
                                    "content": {
                                        "type": "string",
                                        "description": "文件完整内容",
                                    },
                                },
                                "required": ["file_category", "content"],
                            },
                        },
                        "overwrite_existing": {
                            "type": "boolean",
                            "description": "是否强制覆盖已存在的文件。首次生成为false，修复后重新生成为true",
                            "default": False,
                        },
                    },
                    "required": ["problem_id", "files"],
                    "additionalProperties": False,
                },
            },
        }

    @staticmethod
    def _retrieve_file_content() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "retrieve_file_content",
                "description": """读取已生成的文件内容。测试失败或编译错误时，使用此工具查看当前文件内容进行分析。

⚠️ 重要约束：
- **retrieve 后必须修改文件！** 禁止「retrieve → compile」不改文件的无效循环
- 如果只是验证修复思路，直接在脑中分析，不要 retrieve
- 只有在不确定当前代码状态、需要确认细节时才 retrieve
- retrieve 后必须调用 create_or_update_file（overwrite_existing=true）更新文件""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID",
                        },
                        "file_category": {
                            "type": "string",
                            "description": "文件类型",
                            "enum": ["header", "source", "test"],
                        },
                    },
                    "required": ["problem_id", "file_category"],
                    "additionalProperties": False,
                },
            },
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
                            "description": "题目 ID",
                        },
                        "test_name": {
                            "type": "string",
                            "description": "测试用例名称，建议使用描述性名称（如 WrongAnswerCase1, EdgeCaseEmptyArray）",
                        },
                        "test_code": {
                            "type": "string",
                            "description": "测试代码内容，只需要 TEST_P 宏内部的代码，不需要完整的 TEST_P 包装",
                        },
                    },
                    "required": ["problem_id", "test_name", "test_code"],
                    "additionalProperties": False,
                },
            },
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
                            "description": "题目 ID（如 1, 2, 461）。如果提供，只编译该题目（增量编译，更快）",
                        }
                    },
                    "required": [],
                    "additionalProperties": False,
                },
            },
        }

    @staticmethod
    def _compile_and_test() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "compile_and_test",
                "description": """编译并测试指定题目（single 模式）。

这是一个组合工具，使用 just single 模式编译指定题目，然后立即运行测试。
相比分开调用 compile_project 和 execute_test_suite，这个工具：
1. 使用 single 模式编译，速度最快
2. 自动运行对应测试，无需额外调用
3. 返回详细的编译和测试结果

使用场景：
- 生成题目代码后，立即验证正确性
- 修复代码后，快速验证修复结果

⚠️ 重要约束：
- **如果上一次调用返回了 "编译成功，所有测试通过"，禁止再次调用！**
- 测试通过后，等待系统处理（LeetCode 提交或生成报告），不要重复测试
- 只有在修改了代码（create_or_update_file）或添加了测试用例（append_test_case）后才再次调用""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID（如 1, 2, 461）",
                        }
                    },
                    "required": ["problem_id"],
                    "additionalProperties": False,
                },
            },
        }

    @staticmethod
    def _execute_test_suite() -> Dict[str, Any]:
        return {
            "type": "function",
            "function": {
                "name": "execute_test_suite",
                "description": """运行指定题目的测试用例。
返回结果包含：
- status: success/error
- message: 结果摘要
- error_type: 错误类型（内存错误/断言失败/超时/编译错误）
- retryable: 是否建议重试
- artifacts: 产物列表（如生成文件）
- 兼容字段：is_successful/error_message/suggestion/output""",
                "parameters": {
                    "type": "object",
                    "properties": {
                        "problem_id": {
                            "type": "integer",
                            "description": "题目 ID",
                        }
                    },
                    "required": ["problem_id"],
                    "additionalProperties": False,
                },
            },
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
                            "enum": ["tree", "linked-list", "queue", "stack"],
                        }
                    },
                    "required": ["structure_type"],
                    "additionalProperties": False,
                },
            },
        }
