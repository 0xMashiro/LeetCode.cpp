#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""LeetCode 提交判题结果的数据容器。"""

from dataclasses import dataclass
from typing import Dict, Optional


@dataclass
class SubmissionResult:
    status: str  # "Accepted" / "Wrong Answer" / "Runtime Error" / ...
    status_code: int
    total_test_cases: int = 0
    passed_test_cases: int = 0
    failed_test_case: Optional[Dict] = None
    runtime_ms: Optional[float] = None
    memory_mb: Optional[float] = None
    error_message: Optional[str] = None
