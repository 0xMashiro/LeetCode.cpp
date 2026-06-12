#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""读 source 文件里的 strategy verdict 元信息，按 registerStrategy 顺序
映射到 (1-indexed strategy 序号 → LeetCode 全称状态)。

优先读取结构化 `.expected = "..."`；旧 `// @expected: <verdict>` 注释仍可被解析。
没写的解默认 `Accepted`。缩写 TLE/WA/RE/MLE/CE/AC 自动展开成 LeetCode
判题返回的完整字符串，这样多解验证时 actual.status == expected 直接字符串比对。
"""

import re
from typing import Dict

_EXPECT_RE = re.compile(r"//\s*@expected\s*:\s*([A-Za-z][A-Za-z ]*)")
_METADATA_EXPECT_RE = re.compile(r"\.expected\s*=\s*\"([A-Za-z][A-Za-z ]*)\"")
_REGISTER_RE = re.compile(r"\bregisterStrategy\s*\(")

_ALIAS = {
    "AC": "Accepted",
    "Accepted": "Accepted",
    "TLE": "Time Limit Exceeded",
    "TimeLimitExceeded": "Time Limit Exceeded",
    "Time Limit Exceeded": "Time Limit Exceeded",
    "MLE": "Memory Limit Exceeded",
    "MemoryLimitExceeded": "Memory Limit Exceeded",
    "Memory Limit Exceeded": "Memory Limit Exceeded",
    "WA": "Wrong Answer",
    "WrongAnswer": "Wrong Answer",
    "Wrong Answer": "Wrong Answer",
    "RE": "Runtime Error",
    "RuntimeError": "Runtime Error",
    "Runtime Error": "Runtime Error",
    "CE": "Compile Error",
    "CompileError": "Compile Error",
    "Compile Error": "Compile Error",
}


def parse_expected_verdicts(source: str) -> Dict[int, str]:
    """返回 {1-indexed solution num: expected LeetCode status}；未标注的项缺席。

    每个 `registerStrategy` 分别找它的结构化字段或注释，两种注释位置都接受：
      1) 注释与 register 在**同一行**（trailing）—— `regStrat(...);  // @expected: TLE`
      2) 注释在 register 上一行**顶层独立成行**（leading）
    """
    lines = source.splitlines()
    register_line_indices = [
        (i, m.start()) for i, line in enumerate(lines) for m in [_REGISTER_RE.search(line)] if m
    ]
    if not register_line_indices:
        return {}

    result: Dict[int, str] = {}
    for seq, (line_idx, call_start) in enumerate(register_line_indices, start=1):
        call_text = _collect_call_text(lines, line_idx, call_start)
        metadata = _METADATA_EXPECT_RE.search(call_text)
        if metadata:
            canonical = _ALIAS.get(metadata.group(1).strip())
            if canonical:
                result[seq] = canonical
                continue

        current_line = lines[line_idx]
        # 1) trailing: 同一行有 @expected
        trailing = _EXPECT_RE.search(current_line)
        if trailing:
            canonical = _ALIAS.get(trailing.group(1).strip())
            if canonical:
                result[seq] = canonical
                continue
        # 2) leading: 上一行（跳过空行）是独立的 @expected 注释
        j = line_idx - 1
        while j >= 0 and not lines[j].strip():
            j -= 1
        if j >= 0:
            leading = _EXPECT_RE.search(lines[j])
            if leading and lines[j].strip().startswith("//"):
                canonical = _ALIAS.get(leading.group(1).strip())
                if canonical:
                    result[seq] = canonical
    return result


def _collect_call_text(lines: list[str], start_line: int, call_start: int) -> str:
    """Collect one registerStrategy(...) call, enough for metadata field parsing."""
    chunks = []
    balance = 0
    started = False
    for line in lines[start_line:]:
        part = line[call_start:] if not started else line
        started = True
        chunks.append(part)
        balance += part.count("(") - part.count(")")
        if balance <= 0 and ")" in part:
            break
    return "\n".join(chunks)


def resolve_expected(verdicts: Dict[int, str], solution_num: int) -> str:
    """未标注默认 Accepted。"""
    return verdicts.get(solution_num, "Accepted")
