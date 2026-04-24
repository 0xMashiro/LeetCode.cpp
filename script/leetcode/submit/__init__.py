#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""LeetCode 提交子包：代码翻译、HTTP 提交、判题结果分类。

入口：`python -m script.leetcode.submit <题号>`
"""

from script.leetcode.submit.classifier import SubmissionClassifier, SubmissionOutcome
from script.leetcode.submit.result import SubmissionResult
from script.leetcode.submit.submitter import LeetCodeSubmitter

__all__ = [
    "LeetCodeSubmitter",
    "SubmissionClassifier",
    "SubmissionOutcome",
    "SubmissionResult",
]
