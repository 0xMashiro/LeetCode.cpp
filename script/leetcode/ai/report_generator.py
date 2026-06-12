#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
解题报告生成器：把解题过程落盘成 SOLUTION_REPORT_{id}.md。

从 AISolver 中拆出，目的：
  - AISolver 专注主循环编排；
  - 报告涉及的 LLM 调用、模板拼接、降级路径集中在此，便于单测与审计。
"""

from pathlib import Path
from typing import Any, Dict, List

from openai import OpenAI

from script.leetcode.ai.prompts import REPORT_GENERATION_PROMPT
from script.leetcode.config import AIProvider
from script.leetcode.utils import ColorCode, color_text

SKIP_CONTENT = "## 状态\n\n✅ **题目已解决**，文件已存在，跳过自动解题。\n"
FOOTER = "---\n\n*本报告由 AI 自动生成。*\n"
BLOG_FALLBACK = "## 解题思路\n\n（详细的解题思路请参考源代码和测试用例中的注释）\n"

REPORT_FILENAME_TEMPLATE = "SOLUTION_REPORT_{problem_id}.md"


class ReportGenerator:
    """根据解题历史构建完整报告（固定模板 + AI 博客正文）。"""

    def __init__(self, client: OpenAI, provider: AIProvider):
        self.client = client
        self.provider = provider

    def generate(
        self,
        *,
        problem_id: int,
        problem_title: str,
        problem_slug: str,
        problem_difficulty: str,
        problem_tags: List[str],
        reasoning_log: List[str],
        is_skip: bool = False,
    ) -> Path:
        """生成完整报告并写入 SOLUTION_REPORT_{problem_id}.md，返回目标路径。"""
        print()
        print(color_text("📝 正在生成专业解题报告...", ColorCode.CYAN.value))

        header = self._header(
            problem_id, problem_title, problem_slug, problem_difficulty, problem_tags
        )
        content = SKIP_CONTENT if is_skip else self._generate_blog(reasoning_log)

        path = Path(REPORT_FILENAME_TEMPLATE.format(problem_id=problem_id))
        path.write_text(f"{header}\n{content}\n{FOOTER}", encoding="utf-8")
        print(color_text(f"✅ 解题报告已保存: {path}", ColorCode.GREEN.value))
        return path

    @staticmethod
    def _header(
        problem_id: int,
        title: str,
        slug: str,
        difficulty: str,
        tags: List[str],
    ) -> str:
        tags_str = ", ".join(tags) if tags else "暂无"
        return f"""# LeetCode {problem_id}. {title}

## 题目信息

| 属性 | 内容 |
|------|------|
| **题目链接** | https://leetcode.com/problems/{slug}/ |
| **难度** | {difficulty or "Unknown"} |
| **标签** | {tags_str} |

## 文件位置

- 头文件：`include/leetcode/problems/{slug}.h`
- 源文件：`src/leetcode/problems/{slug}.cpp`
- 测试文件：`test/leetcode/problems/{slug}.cpp`

---

"""

    def _generate_blog(self, reasoning_log: List[str]) -> str:
        """调 LLM 根据解题历史生成博客正文；失败时降级到静态文本。"""
        history = "\n".join(reasoning_log)
        user_prompt = (
            "这是这道题的完整解题历史记录（包含题目描述、代码片段和思考过程）：\n\n"
            f"{history}\n\n"
            "请基于上述材料，按照 System Prompt 中的要求，写出那篇技术博客。"
            "直接开始写正文，不要有任何开场白。"
        )

        # 报告生成不需要思考链路，临时关闭以节省 token
        report_provider = AIProvider(
            name=self.provider.name,
            base_url=self.provider.base_url,
            model=self.provider.model,
            use_reasoner=False,
        )
        params: Dict[str, Any] = {
            "model": self.provider.model,
            "messages": [
                {"role": "system", "content": REPORT_GENERATION_PROMPT},
                {"role": "user", "content": user_prompt},
            ],
            "stream": False,
        }
        params.update(report_provider.build_request_kwargs(allow_temperature=True))

        try:
            response = self.client.chat.completions.create(**params)
            return response.choices[0].message.content
        except Exception as e:
            print(color_text(f"⚠️ AI 博客生成失败: {e}，使用基础描述", ColorCode.YELLOW.value))
            return BLOG_FALLBACK
