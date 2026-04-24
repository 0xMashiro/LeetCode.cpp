#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
编译 / 测试输出的错误分类器。

把 build/test 命令输出里能抓到的典型 C++ 错误模式映射成 `{type, details, suggestion}`
三元组，供工具执行层组装回给模型的消息。
"""

from typing import Dict


def classify_compilation_error(output: str) -> Dict[str, str]:
    """按关键字把编译输出归类为具体的编译错误类型。"""
    text = output.lower()

    if any(x in text for x in ("syntax error", "expected", "before", "after")):
        return {
            "type": "语法错误",
            "details": "C++ 语法错误",
            "suggestion": "检查语法：括号匹配、分号、类型定义等",
        }

    if "undefined reference" in text or "undefined symbol" in text:
        return {
            "type": "链接错误",
            "details": "函数或变量未定义",
            "suggestion": "检查函数声明和定义是否匹配，是否缺少实现",
        }

    if any(x in text for x in ("cannot convert", "no matching function", "invalid conversion")):
        return {
            "type": "类型错误",
            "details": "类型不匹配",
            "suggestion": "检查函数参数类型、返回值类型是否与声明一致",
        }

    if "no such file" in text or "cannot find" in text:
        return {
            "type": "头文件错误",
            "details": "找不到头文件",
            "suggestion": "检查 #include 路径是否正确",
        }

    return {
        "type": "编译错误",
        "details": "编译失败",
        "suggestion": "查看详细错误信息进行修复",
    }


def analyze_test_failure(output: str) -> Dict[str, str]:
    """按关键字把测试失败输出归类为具体的运行时失败类型。"""
    text = output.lower()

    if any(x in text for x in ("segmentation fault", "sigsegv", "core dumped", "double free")):
        return {
            "type": "内存错误",
            "details": "程序发生段错误或内存访问错误",
            "suggestion": (
                "检查数组越界、空指针访问、迭代器失效、双重释放等问题。"
                "使用 valgrind 或地址消毒器可以帮助定位"
            ),
        }

    if "expect" in text or "assert" in text:
        return {
            "type": "结果错误",
            "details": "测试结果与预期不符",
            "suggestion": (
                "1. 检查算法逻辑是否正确\n"
                "2. 检查边界条件处理（空输入、单元素、最大值等）\n"
                "3. 检查返回值是否符合题目要求\n"
                "4. 检查自己构造的测试用例是否正确"
            ),
        }

    if any(x in text for x in ("error:", "undefined reference", "cannot find")):
        return {
            "type": "编译错误",
            "details": "代码编译失败",
            "suggestion": "检查头文件包含、函数签名一致性、语法错误等",
        }

    if "timeout" in text or "time limit" in text:
        return {
            "type": "超时",
            "details": "测试运行时间超过限制",
            "suggestion": "算法时间复杂度过高，需要优化。考虑使用更高效的数据结构或算法",
        }

    return {
        "type": "未知错误",
        "details": "测试失败，具体原因不明",
        "suggestion": "请仔细查看输出信息，检查代码逻辑和测试用例",
    }
