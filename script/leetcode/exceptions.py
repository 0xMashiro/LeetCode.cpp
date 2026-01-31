#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
自定义异常类
"""


class LeetCodeError(Exception):
    """基础异常类"""
    pass


class ProblemNotFoundError(LeetCodeError):
    """题目不存在"""
    
    def __init__(self, identifier: str):
        self.identifier = identifier
        super().__init__(f"题目 '{identifier}' 不存在")


class APIError(LeetCodeError):
    """API 调用错误"""
    
    def __init__(self, message: str, status_code: int = None):
        self.status_code = status_code
        super().__init__(message)


class NetworkError(LeetCodeError):
    """网络错误"""
    pass


class CacheError(LeetCodeError):
    """缓存错误"""
    pass


class ParseError(LeetCodeError):
    """解析错误"""
    pass


class SignatureError(LeetCodeError):
    """函数签名解析错误"""
    pass


class FileOperationError(LeetCodeError):
    """文件操作错误"""
    pass
