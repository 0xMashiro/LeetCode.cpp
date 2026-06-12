#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""对话守卫：防止模型陷入无效循环。"""

from dataclasses import dataclass
from typing import Any, Dict, List, Optional

from script.leetcode.config import AIConfig
from script.leetcode.utils import ColorCode, log_with_time


@dataclass
class GuardState:

    no_file_change_rounds: int = 0
    repeat_error_signature_count: int = 0
    last_error_signature: Optional[str] = None

    def reset(self) -> None:
        self.no_file_change_rounds = 0
        self.repeat_error_signature_count = 0
        self.last_error_signature = None


def should_abort(tool_summary: Dict[str, Any], state: GuardState) -> bool:
    """判定是否应提前终止解题。"""
    file_mutated = bool(tool_summary.get("file_mutated"))
    error_signatures: List[str] = tool_summary.get("error_signatures", [])

    if file_mutated:
        state.reset()
    else:
        state.no_file_change_rounds += 1

    max_no_change = getattr(AIConfig, "MAX_NO_FILE_CHANGE_ROUNDS", 4)
    if state.no_file_change_rounds >= max_no_change:
        log_with_time(
            f"⚠️ 连续 {state.no_file_change_rounds} 轮无文件修改，判定为无效循环，停止处理",
            ColorCode.YELLOW,
        )
        return True

    max_repeat = getattr(AIConfig, "MAX_REPEAT_ERROR_SIGNATURE", 3)
    for signature in error_signatures:
        if signature == state.last_error_signature:
            state.repeat_error_signature_count += 1
        else:
            state.last_error_signature = signature
            state.repeat_error_signature_count = 1

        if state.repeat_error_signature_count >= max_repeat:
            log_with_time(
                f"⚠️ 检测到同类错误连续出现 {state.repeat_error_signature_count} 次，停止处理",
                ColorCode.YELLOW,
            )
            return True

    return False
