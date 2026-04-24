#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""solver 视角的 LeetCode 判题结果分类器。

AISolver 主循环已在上层决定"要提交"，这里把 HTTP 返回按
"代码问题 vs 基础设施问题"二元分类，顺便做多解聚合，向上返回
`should_continue / accepted / result / skip_reason`。
"""

import os
from dataclasses import dataclass
from typing import Any, Callable, Optional

from script.leetcode.utils import ColorCode, color_text, log_with_time


@dataclass
class SubmissionOutcome:
    """`accepted` 三态：True = AC；False = 真判错（WA/RE/TLE/CE）；None = 没拿到判题信号。

    `skip_reason` 仅在 accepted=None 时有值:
      * "no_cookie"   cookie 没配
      * "infra_error" 提交异常 / 非代码状态（过期、403、网络）
    """
    should_continue: bool
    accepted: Optional[bool] = None
    result: Optional[Any] = None
    error_message: Optional[str] = None
    skip_reason: Optional[str] = None


class SubmissionClassifier:
    """把 LeetCode 返回的原始 SubmissionResult 翻成 solver 能直接用的 outcome。"""

    CODE_FAILURE_STATUSES = {
        "Wrong Answer",
        "Runtime Error",
        "Time Limit Exceeded",
        "Compile Error",
    }

    def __init__(self, submitter_factory: Optional[Callable[[], Any]] = None):
        """`submitter_factory` 仅单测注入用。"""
        self._submitter_factory = submitter_factory or self._default_submitter_factory

    @staticmethod
    def _default_submitter_factory() -> Any:
        from script.leetcode.submit import LeetCodeSubmitter
        return LeetCodeSubmitter()

    def submit_and_classify(self, problem_id: Optional[int]) -> SubmissionOutcome:
        prelude = self._prelude(problem_id)
        if prelude is not None:
            return prelude

        print()
        log_with_time("🌐 正在提交到 LeetCode 验证...", ColorCode.CYAN)

        try:
            submitter = self._submitter_factory()
            # solution_num=0 解析为"最后一个 registerStrategy"(项目约定的最优解)
            result = submitter.submit_problem_with_result(problem_id, solution_num=0)
        except Exception as e:
            log_with_time(
                f"⚠️ 提交到 LeetCode 时出错: {e}, 未拿到判题信号", ColorCode.YELLOW
            )
            return SubmissionOutcome(
                should_continue=True, accepted=None, skip_reason="infra_error"
            )
        return self._classify_single(result)

    def submit_all_and_classify(self, problem_id: Optional[int]) -> SubmissionOutcome:
        """遍历所有 registerStrategy，按 `@expected` 注释对比预期状态后聚合。

        `actual == expected` 即通过（"预期 TLE 真 TLE"也算）；任一不符 → accepted=False，
        把 "solutionN: expected=X actual=Y" 汇总塞进 error_message，模型能看到哪个解挂了。
        """
        prelude = self._prelude(problem_id)
        if prelude is not None:
            return prelude

        print()
        log_with_time("🌐 正在提交所有策略到 LeetCode 验证...", ColorCode.CYAN)

        try:
            submitter = self._submitter_factory()
            results = submitter.submit_all_solutions(problem_id)
        except Exception as e:
            log_with_time(
                f"⚠️ 多策略提交时出错: {e}, 未拿到判题信号", ColorCode.YELLOW
            )
            return SubmissionOutcome(
                should_continue=True, accepted=None, skip_reason="infra_error"
            )

        mismatches = [(n, r, exp) for n, r, exp in results if r.status != exp]
        if not mismatches:
            has_non_ac_expected = any(exp != "Accepted" for _, _, exp in results)
            suffix = "（含预期 TLE 的暴力解）" if has_non_ac_expected else ""
            log_with_time(
                f"✅ 全部 {len(results)} 个策略都符合预期{suffix}!",
                ColorCode.GREEN,
            )
            return SubmissionOutcome(should_continue=True, accepted=True)

        code_failures = [
            (n, r) for n, r, _ in mismatches if r.status in self.CODE_FAILURE_STATUSES
        ]
        summary = " / ".join(
            f"solution{n}: expected={exp} actual={r.status}"
            for n, r, exp in results
        )

        if code_failures:
            n, r = code_failures[0]
            r.error_message = (
                (r.error_message or "") + f"\n[多解验证汇总] {summary}"
            ).strip()
            return SubmissionOutcome(should_continue=False, accepted=False, result=r)

        log_with_time(
            f"⚠️ 多策略提交全是非代码类失败: {summary}", ColorCode.YELLOW
        )
        return SubmissionOutcome(
            should_continue=True, accepted=None, skip_reason="infra_error"
        )

    def _prelude(self, problem_id: Optional[int]) -> Optional[SubmissionOutcome]:
        if not problem_id:
            return SubmissionOutcome(
                should_continue=False, accepted=None, error_message="无法获取题目 ID"
            )
        if not os.getenv("LEETCODE_COOKIE"):
            print()
            print(color_text(
                "💡 提示: 设置 LEETCODE_COOKIE 后可自动提交到 LeetCode 验证",
                ColorCode.CYAN.value,
            ))
            return SubmissionOutcome(
                should_continue=True, accepted=None, skip_reason="no_cookie"
            )
        return None

    def _classify_single(self, result: Any) -> SubmissionOutcome:
        if result.status == "Accepted":
            log_with_time("✅ LeetCode 验证通过!", ColorCode.GREEN)
            return SubmissionOutcome(should_continue=True, accepted=True)
        if result.status in self.CODE_FAILURE_STATUSES:
            return SubmissionOutcome(
                should_continue=False, accepted=False, result=result
            )
        infra_msg = result.error_message or result.status
        log_with_time(
            f"⚠️ LeetCode 在线提交未通过(非代码问题, 未拿到判题信号): {infra_msg}",
            ColorCode.YELLOW,
        )
        return SubmissionOutcome(
            should_continue=True, accepted=None, skip_reason="infra_error"
        )
