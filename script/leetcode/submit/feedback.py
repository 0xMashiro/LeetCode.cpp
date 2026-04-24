#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""按 LeetCode 判题状态生成给模型看的修复提示（纯函数，无状态）。"""

from typing import Any, List


def build(result: Any, *, self_authored_tests_locally_passed: bool = False) -> str:
    body = _HANDLERS.get(result.status, _generic)(result)
    lines = ["LeetCode 提交失败，需要修复。", ""]
    if result.status == "Wrong Answer" and self_authored_tests_locally_passed:
        lines += [
            "ℹ️ 本地有 SelfAuthored* TEST_P 且全部通过，但 LeetCode 判 Wrong Answer。通常有两种原因，按可能性排：",
            "  1）**本地测试覆盖不够**——SelfAuthored 没涵盖 LeetCode 用的那类输入（常见）。",
            "     → 按下面『添加失败用例到本地』流程走，把 LeetCode 的失败 case 补进测试、修算法。",
            "  2）算法 bug 和某个 SelfAuthored 的 expected 刚好错在同一方向，两者互抵→本地绿、LeetCode 毙（罕见）。",
            "     → 仅当你按 (1) 改完后 LeetCode 还继续 WA，才回头审一遍 SelfAuthored expected。",
            "",
        ]
    lines += [*body, "", "请开始修复。"]
    return "\n".join(lines)


def _wrong_answer(result: Any) -> List[str]:
    passed = result.passed_test_cases or 0
    total = result.total_test_cases or 0
    header = f"❌ Wrong Answer (通过了 {passed}/{total} 个测试用例)"
    ratio_hint = _pass_ratio_diagnosis(passed, total)
    if not result.failed_test_case:
        return [header] + ([ratio_hint] if ratio_hint else [])
    failed = result.failed_test_case
    return [
        header,
        *([ratio_hint] if ratio_hint else []),
        "",
        "失败的测试用例:",
        f"- 输入: {failed.get('input', 'N/A')}",
        f"- 输出: {failed.get('actual', 'N/A')}",
        f"- 期望: {failed.get('expected', 'N/A')}",
        "",
        "请按以下步骤修复：",
        "",
        "**步骤 1: 添加失败的测试用例到本地**",
        "使用 `append_test_case` 工具将此测试用例添加到本地测试文件。",
        "test_name 建议使用描述性名称如 'WrongAnswerCase1' 或 'EdgeCaseEmptyArray'",
        "test_code 格式示例（注意缩进为2个空格）：",
        "```",
        "  // 输入: nums = [1,2,3], target = 4",
        "  // 期望: [0,1]",
        "  vector<int> nums = {{1, 2, 3}};",
        "  int target = 4;",
        "  vector<int> expected = {{0, 1}};",
        "  vector<int> result = solution.twoSum(nums, target);",
        "  EXPECT_EQ(expected, result);",
        "```",
        "",
        "**步骤 2: 分析并修复代码**",
        "使用 `retrieve_file_content` 查看当前代码，分析失败原因，",
        "然后使用 `create_or_update_file` 修复源文件中的问题。",
        "",
        "**步骤 3: 验证修复**",
        "调用 `compile_and_test` 确保修复后的代码通过所有测试。",
    ]


def _pass_ratio_diagnosis(passed: int, total: int) -> str:
    """通过率给模型一个"改算法 vs 修边界"的方向信号。"""
    if total <= 0:
        return ""
    ratio = passed / total
    if ratio < 0.3:
        return (
            "⚠️ 通过率 < 30%：大概率是**算法范式选错**或核心递推不对，"
            "不要在当前算法上小改——回阶段 0 重选一条路径。"
        )
    if ratio > 0.95:
        return "📍 通过率 > 95%：算法方向大致正确，多半是某个**边界 / 特殊输入**漏了，针对失败用例对症改即可。"
    return ""


def _runtime_error(result: Any) -> List[str]:
    lines = ["💥 Runtime Error"]
    if result.error_message:
        lines.append(f"错误信息: {result.error_message}")
    lines += [
        "",
        "请分析错误原因（数组越界？空指针？除以零？），然后：",
        "1. 使用 `retrieve_file_content` 查看代码",
        "2. 修复问题并使用 `create_or_update_file` 更新代码",
        "3. 调用 `compile_and_test` 验证修复",
    ]
    return lines


def _time_limit_exceeded(_: Any) -> List[str]:
    return [
        "⏱️ Time Limit Exceeded",
        "",
        "算法时间复杂度过高，请考虑：",
        "1. 优化算法（例如使用更高效的数据结构）",
        "2. 减少冗余计算",
        "3. 使用 `retrieve_file_content` 查看当前实现并改进",
    ]


def _compile_error(result: Any) -> List[str]:
    lines = ["❌ Compile Error"]
    if result.error_message:
        lines.append(f"编译错误信息: {result.error_message}")
    lines += ["", "请检查代码语法并修复编译错误。"]
    return lines


def _generic(result: Any) -> List[str]:
    lines = [f"❌ {result.status}"]
    if result.error_message:
        lines.append(f"错误信息: {result.error_message}")
    return lines


_HANDLERS = {
    "Wrong Answer": _wrong_answer,
    "Runtime Error": _runtime_error,
    "Time Limit Exceeded": _time_limit_exceeded,
    "Compile Error": _compile_error,
}
