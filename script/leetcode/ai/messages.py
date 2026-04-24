#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
对话消息与工具调用的数据结构。

从 solver.py 抽出：
  - `Message` 代表一次 API 流式响应组装完毕后的快照（content + reasoning + tool_calls）
  - `ToolCall` 代表单次工具调用的规范化视图，屏蔽 OpenAI SDK 返回里的增量 delta 结构
"""

from dataclasses import dataclass
from typing import Any, Dict, List, Optional


@dataclass
class Message:
    """一次 API 响应组装完成后的快照。"""
    content: str = ""
    reasoning_content: Optional[str] = None
    # 没有工具调用时为 None；有则是非空列表。与 `_to_tool_calls` 的返回语义保持一致。
    tool_calls: Optional[List[Dict[str, Any]]] = None


@dataclass
class ToolCall:
    """一次工具调用的规范化视图。"""
    id: str
    type: str
    function_name: str
    function_arguments: str
