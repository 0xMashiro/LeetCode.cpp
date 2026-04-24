#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""`fetch_structure_definition` 工具：返回项目预定义数据结构的源文件。"""

from pathlib import Path
from typing import Any, Dict

from script.leetcode.ai.tools._utils import read_file
from script.leetcode.config import ProjectPaths


_SUPPORTED = ("tree", "linked-list", "queue", "stack")


def fetch_structure_definition(structure_type: str) -> Dict[str, Any]:
    if structure_type not in _SUPPORTED:
        return {
            "is_successful": False,
            "error_message": f"未知的数据结构: {structure_type}。支持: {', '.join(_SUPPORTED)}",
        }

    header_path = Path(f"{ProjectPaths.INCLUDE_UTILS}/{structure_type}.h")
    source_path = Path(f"{ProjectPaths.SRC_UTILS}/{structure_type}.cpp")

    if not header_path.exists():
        return {"is_successful": False, "error_message": f"头文件不存在: {header_path}"}

    return {
        "is_successful": True,
        "structure_type": structure_type,
        "header_file": str(header_path),
        "header_content": read_file(header_path),
        "source_file": str(source_path) if source_path.exists() else None,
        "source_content": read_file(source_path) if source_path.exists() else None,
    }
