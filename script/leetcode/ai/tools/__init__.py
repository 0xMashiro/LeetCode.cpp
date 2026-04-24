#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
工具包：向模型暴露的 JSON Schema 定义 + 执行器。

- `ToolDefinition`：面向 OpenAI Tool Calling 规范的工具元数据集合。
- `ToolExecutor`：把模型发来的工具调用派发到真实操作（文件读写、编译、测试等）。
"""

from script.leetcode.ai.tools.definitions import ToolDefinition
from script.leetcode.ai.tools.executor import ToolExecutor

__all__ = ["ToolDefinition", "ToolExecutor"]
