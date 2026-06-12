#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""LeetCode 提交子包。

入口：`python -m script.leetcode.submit <题号>`
"""

from script.leetcode.submit.classifier import SubmissionClassifier, SubmissionOutcome
from script.leetcode.submit.result import SubmissionResult

__all__ = [
    "SubmissionClassifier",
    "SubmissionOutcome",
    "SubmissionResult",
]
