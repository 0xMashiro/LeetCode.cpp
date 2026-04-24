#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
官方 examples → C++ TEST_P body 的 LLM 翻译器。

动机:

LeetCode 题面里 `nums = [2,7,11,15]` / `root = [3,null,9]` / `head = [1,2,3]` 这类
example 文本和 C++ 测试里真正需要的代码差距不小(vector 字面量、constructTree 占位 null、
ListNode 用 traverse 对比)。自己写字符串解析既碎又难覆盖全,但 LLM 本来就擅长这种
"松散格式 → 严格格式"的翻译。

设计:

`translate_examples_to_cpp` 是一次**聚焦**的 LLM 调用:
  - 输入: function signature + 每个 example 的 {input, output} + 项目辅助函数清单
  - 输出: `{example_index: body_source}` 的 dict,body 是 TEST_P 内部代码(不含包裹)
  - 失败时返回空 dict,调用方保留 scaffold 默认的 TODO 占位

翻译和主解题流程**解耦**:
  - 翻译这一步只做一件事,模型没机会"顺手偷懒"
  - 主解题流程看到的 test 文件已是完整可编译的 TEST_P
  - 真 untranslatable 的题目(设计类/原地修改/多解)LLM 返回特殊标记,我们保留 TODO
"""

import json
import re
from typing import Any, Dict, List, Optional


_UTILITY_HINT = """项目已经提供的辅助函数(遇到对应类型优先用,不要自己手动建链表/树):

- `leetcode::constructTree(vector<int>)`:把 LeetCode 层序 + -1 代表 null 的数组构造成 `TreeNode*`
- `leetcode::constructLinkedList(vector<int>)`:构造 `ListNode*`
- `leetcode::traverse(ListNode*)` → `vector<int>`:把链表还原成 vector 方便 EXPECT_EQ 比较
- `leetcode::preorderTraversal / inorderTraversal / postorderTraversal / levelOrderTraversal`:TreeNode 遍历成 vector

LeetCode 用 `null` 表示树空节点,在 C++ 构造函数里用 `-1` 占位。
LeetCode 数组字面量 `[1,2,3]` 对应 C++ `{1, 2, 3}` 列表初始化。
嵌套数组 `[[0,1],[1,2]]` 对应 `{{0, 1}, {1, 2}}`。
字符串用双引号,布尔用 `true`/`false`。

浮点比较用 `EXPECT_NEAR(expected, result, 1e-5)`,整数/字符串/vector 用 `EXPECT_EQ`。
ListNode* 返回值需要先 `traverse(result)` 再和期望的 vector<int> 比。
"""

_UNTRANSLATABLE = "UNTRANSLATABLE"

_SYSTEM_PROMPT = """你是 LeetCode 题面 example → C++ Google Test body 的翻译器。
你只做一件事:根据给定的 function signature 和官方 example 的 Input/Output,生成一段
TEST_P 函数体内的 C++ 代码(不要包含 `TEST_P(ClassName, ExampleN) {` 和结尾 `}`)。

必须遵守:
1. 用 2 空格缩进
2. 严格使用 EXPECT_EQ / EXPECT_NEAR(浮点用 NEAR,公差 1e-5)
3. **直接使用 fixture 已经提供的 `solution` 成员**,**禁止声明本地 Solution 对象**。
   错误写法: `MySolution solution; int r = solution.foo(...)` ← 这会 shadow fixture 成员,
            导致 fixture SetUp 里的 setStrategy 失效,所有策略都用不到。
   正确写法: 直接 `int r = solution.foo(args...);`(solution 是 fixture 成员,已 setStrategy)
4. 调用 method 名来自 signature
5. LeetCode 的 null 要转成 -1(树构造专用)或 nullptr(链表末尾)
6. 字面量嵌套语法要对:`[[0,1]]` → `{{0, 1}}`
7. 如果某 example 因类型表达不出来(设计类多次调用 / 原地修改数组返回长度 / 多解集判等)
   真的翻译不了,就让对应 key 的 value 返回恰好这个字符串:UNTRANSLATABLE

输出 **纯 JSON**,key 是 example index 的字符串形式("1"、"2"、"3"),value 是代码 string。
不要 markdown 围栏,不要解释,直接 JSON。"""


def translate_examples_to_cpp(
    client: Any,
    provider: Any,
    *,
    solution_class_name: str,
    function_signature: Optional[str],
    examples: List[Dict[str, Any]],
) -> Dict[int, str]:
    """把官方 examples 翻译成 TEST_P body 代码。

    Args:
        client: OpenAI 兼容客户端(AISolver.client 可直接传)
        provider: AIProvider 实例(用来拼请求参数,翻译这一步强制开 thinking 以提高精度)
        solution_class_name: 类名,如 `TwoSumSolution`
        function_signature: signature 文本,如 `vector<int> twoSum(vector<int>& nums, int target)`
        examples: extract_examples() 的返回

    Returns:
        `{index: body_code}`。翻译失败、结果格式不对、或某个 key 是 UNTRANSLATABLE 时,
        对应 index 在 dict 里缺席(调用方应保留 scaffold 默认 TODO)。
    """
    if not examples or not function_signature:
        return {}

    user_prompt = _build_user_prompt(
        solution_class_name=solution_class_name,
        function_signature=function_signature,
        examples=examples,
    )

    params: Dict[str, Any] = {
        "model": provider.model,
        "messages": [
            {"role": "system", "content": _SYSTEM_PROMPT},
            {"role": "user", "content": user_prompt},
        ],
        "stream": False,
    }
    # 翻译这一步是精细活儿,强制开 thinking(用 provider 已有的 build_request_kwargs 走流程)
    forced_think_provider = _with_thinking_enabled(provider)
    params.update(forced_think_provider.build_request_kwargs(allow_temperature=False))

    try:
        response = client.chat.completions.create(**params)
        text = response.choices[0].message.content or ""
    except Exception:
        return {}

    return _parse_llm_output(text, {ex["index"] for ex in examples})


def _build_user_prompt(
    *,
    solution_class_name: str,
    function_signature: str,
    examples: List[Dict[str, Any]],
) -> str:
    lines = [
        f"Solution class: {solution_class_name}",
        f"Function signature: {function_signature}",
        "",
        "Examples:",
    ]
    for ex in examples:
        idx = ex.get("index")
        inp = ex.get("input", "").strip()
        out = ex.get("output", "").strip()
        lines.append(f"  Example {idx}:")
        lines.append(f"    Input:  {inp}")
        lines.append(f"    Output: {out}")
    lines.append("")
    lines.append(_UTILITY_HINT)
    lines.append("")
    lines.append(
        "请返回 JSON 对象,key 是 example index 字符串,value 是 TEST_P 函数体内部的"
        " C++ 代码(不含 TEST_P 包裹)。无法翻译的 example 用字符串 UNTRANSLATABLE。"
    )
    return "\n".join(lines)


def _with_thinking_enabled(provider: Any) -> Any:
    """返回 thinking 开启的 provider 副本,不影响原 provider 的主解题配置。"""
    try:
        return type(provider)(
            name=provider.name,
            base_url=provider.base_url,
            model=provider.model,
            use_reasoner=True,
        )
    except Exception:
        return provider


_JSON_FENCE_RE = re.compile(r"```(?:json)?\s*(\{.*?\})\s*```", re.DOTALL | re.IGNORECASE)
_RAW_JSON_RE = re.compile(r"(\{.*\})", re.DOTALL)


def _parse_llm_output(text: str, expected_indices: set) -> Dict[int, str]:
    """解析 LLM 返回,抽出 {index: body} 映射。"""
    payload = _extract_json_blob(text)
    if not payload:
        return {}
    try:
        parsed = json.loads(payload)
    except Exception:
        return {}
    if not isinstance(parsed, dict):
        return {}

    result: Dict[int, str] = {}
    for key, value in parsed.items():
        if not isinstance(value, str):
            continue
        if value.strip() == _UNTRANSLATABLE:
            continue
        try:
            index = int(key)
        except (TypeError, ValueError):
            continue
        if index not in expected_indices:
            continue
        # 清理常见污染:前后空行、markdown 代码围栏
        cleaned = _strip_code_fence(value).rstrip() + "\n"
        if cleaned.strip():
            result[index] = cleaned
    return result


def _extract_json_blob(text: str) -> Optional[str]:
    """LLM 可能把 JSON 包在 ```json``` 里或前后带解释文字。尽量健壮地提出 JSON 字符串。"""
    fence = _JSON_FENCE_RE.search(text)
    if fence:
        return fence.group(1)
    raw = _RAW_JSON_RE.search(text)
    if raw:
        return raw.group(1)
    return None


def _strip_code_fence(code: str) -> str:
    """剥掉 LLM 偶尔加的 ```cpp ... ``` 围栏,但保留首行的 2 空格缩进。"""
    if not code.lstrip().startswith("```"):
        return code
    stripped = code.strip()
    stripped = re.sub(r"^```[a-zA-Z]*\s*", "", stripped)
    stripped = re.sub(r"```\s*$", "", stripped)
    return stripped
