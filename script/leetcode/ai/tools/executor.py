#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""工具派发器。

把模型发来的工具调用映射到四类具体模块：
  - metadata: fetch_problem_metadata
  - file_ops: create_or_update_file / retrieve_file_content / append_test_case
  - build_runner: compile_project / compile_and_test / execute_test_suite
  - structure_ref: fetch_structure_definition

结果统一走 `result_utils.normalize` 归一化。executor 自身只做派发，不藏逻辑。
"""

import traceback
from typing import Any, Callable, Dict

from script.leetcode.ai import result_utils
from script.leetcode.ai.tools.build_runner import BuildRunner
from script.leetcode.ai.tools.file_ops import FileOps
from script.leetcode.ai.tools.metadata import MetadataFetcher
from script.leetcode.ai.tools.structure_ref import fetch_structure_definition
from script.leetcode.api import ProblemRepository


class ToolExecutor:
    def __init__(self, repository: ProblemRepository):
        self.repository = repository
        # MetadataFetcher 写 + FileOps 读的共享缓存；flash 盲目重 fetch 时由此返回
        # cached=True 的精简响应，避免浪费轮次。
        self._metadata_cache: Dict[int, Dict[str, Any]] = {}

        self._metadata = MetadataFetcher(repository, self._metadata_cache)
        self._files = FileOps(repository, self._metadata_cache)
        self._build = BuildRunner()

    def execute(self, name: str, arguments: Dict[str, Any]) -> Dict[str, Any]:
        executors: Dict[str, Callable] = {
            "fetch_problem_metadata": self._metadata.fetch,
            "create_or_update_file": self._files.create_or_update,
            "retrieve_file_content": self._files.retrieve,
            "append_test_case": self._files.append_test_case,
            "compile_and_test": self._build.compile_and_test,
            "compile_project": self._build.compile_project,
            "execute_test_suite": self._build.execute_test_suite,
            "fetch_structure_definition": fetch_structure_definition,
        }

        executor = executors.get(name)
        if not executor:
            return result_utils.normalize(
                {
                    "is_successful": False,
                    "error_message": f"未知工具函数: {name}",
                    "error_type": "tool_not_found",
                },
                tool_name=name,
            )

        try:
            raw = executor(**arguments)
            return result_utils.normalize(raw, tool_name=name)
        except Exception as e:
            return result_utils.normalize(
                {
                    "is_successful": False,
                    "error_message": f"{str(e)}\n{traceback.format_exc()}",
                    "error_type": "execution_exception",
                },
                tool_name=name,
            )
