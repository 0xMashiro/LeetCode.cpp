#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""项目代码 → 标准 LeetCode 单文件格式的 AI 翻译。

带内容寻址缓存（`submit.cache`）：源码不变时跳过翻译。Compile Error 时调用方
负责 `cache.invalidate` 清条目再重试。
"""

import re
from datetime import datetime
from typing import Any, Dict, Optional

from script.leetcode.config import AIProvider
from script.leetcode.models import ProblemData
from script.leetcode.submit import cache
from script.leetcode.utils import ColorCode, color_text, log_with_time

_SYSTEM = "你是 C++ 代码转换专家，擅长将项目代码转换为 LeetCode 格式。只输出代码，不要有其他说明。"


def translate(
    problem_data: ProblemData,
    header_code: Optional[str],
    source_code: str,
    solution_num: int,
    *,
    client: Any,
    provider: AIProvider,
    model: str,
) -> Optional[str]:
    """缓存命中直接返回，否则调模型翻译一次。"""
    return cache.get_or_translate(
        slug=problem_data.slug,
        solution_num=solution_num,
        source_content=source_code,
        translate_fn=lambda: _call_llm(
            problem_data, header_code, source_code, solution_num,
            client=client, provider=provider, model=model,
        ),
    )


def _call_llm(
    problem_data: ProblemData,
    header_code: Optional[str],
    source_code: str,
    solution_num: int,
    *,
    client: Any,
    provider: AIProvider,
    model: str,
) -> Optional[str]:
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{timestamp}] 🤖 正在使用 AI 转换代码格式...", end=" ", flush=True)

    try:
        extra_params: Dict[str, Any] = provider.build_request_kwargs(allow_temperature=True)
        response = client.chat.completions.create(
            model=model,
            messages=[
                {"role": "system", "content": _SYSTEM},
                {"role": "user", "content": _build_prompt(problem_data, header_code, source_code, solution_num)},
            ],
            max_tokens=4000,
            **extra_params,
        )
        raw = response.choices[0].message.content
        code = _extract_code_block(raw)
        print(color_text("✅ 完成", ColorCode.GREEN.value))
        return code.strip()
    except Exception as e:
        log_with_time(f"❌ AI 转换失败: {e}", ColorCode.RED)
        return None


def _build_prompt(problem_data: ProblemData, header_code: Optional[str], source_code: str, solution_num: int) -> str:
    return f"""请将以下 LeetCode C++ 项目代码转换为标准 LeetCode 提交格式。

题目：{problem_data.title}
题目描述：
{problem_data.content[:1500]}...

【原始头文件】
{header_code or "(无头文件)"}

【原始源文件】
{source_code}

【使用策略】使用 solution{solution_num} 函数（默认是第一个解法，可通过 --solution N 指定其他）

【转换要求】
1. 转换为标准 LeetCode class Solution 格式
2. 只包含 public 区域的解题函数，不要多策略注册代码
3. 移除项目特定的命名空间 (leetcode::problem_XXX)
4. 保留所有必要的辅助函数和类定义，但把它们放到 Solution 类内部或改为私有
5. 确保代码可以直接在 LeetCode 上编译运行
6. 只输出最终代码，不要有其他说明文字

【LeetCode 格式示例】
```cpp
class Solution {{
public:
    vector<int> twoSum(vector<int>& nums, int target) {{
        // 实现
    }}
}};
```

请输出转换后的代码："""


def _extract_code_block(raw: str) -> str:
    if "```cpp" in raw:
        m = re.search(r"```cpp\s*(.*?)\s*```", raw, re.DOTALL)
        if m:
            return m.group(1)
    if "```" in raw:
        m = re.search(r"```\s*(.*?)\s*```", raw, re.DOTALL)
        if m:
            return m.group(1)
    return raw
