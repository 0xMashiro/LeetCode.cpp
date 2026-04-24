#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
解题过程的结构化记录与落盘出口。

把原先散落在 AISolver 里的指标更新 / 失败日志 / 终局摘要收敛到一个出口：
  - `set_failure_reason` 默认保留首次根因（失败链条里后发生的异常往往是噪声）；
  - `record_failure` 把 log + traceback + 指标更新合并成一次调用；
  - `emit_summary` / `persist_if_enabled` 统一终局输出与可选落盘。
"""

import json
import os
import traceback
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any, Dict, Optional

from script.leetcode.config import AIConfig, AIProvider
from script.leetcode.utils import ColorCode, log_with_time


@dataclass
class ExperimentMetrics:
    """单题解题实验指标（结构化落盘，便于对照实验汇总）。

    `leetcode_passed` 用三态表示真实的 LeetCode 判题结果：
      * None  — 未提交 / cookie 失效 / 403/网络超时 等 infra 失败，本次未拿到判题信号
      * True  — LeetCode Accepted
      * False — LeetCode 判题返回 Wrong Answer / Runtime Error / TLE / Compile Error
    之前这里是 bool 默认 False，导致跳过 + infra 失败的路径也会被记成 True，
    汇总时无法区分"真过 / 真挂 / 没判"，是信号污染。
    """
    provider: str
    model: str
    thinking_enabled: bool
    problem_id: Optional[int] = None
    rounds: int = 0
    api_calls: int = 0
    total_api_time: float = 0.0
    total_solve_time: float = 0.0
    success: bool = False
    leetcode_passed: Optional[bool] = None
    failure_reason: Optional[str] = None
    # leetcode_passed=None 时的归因；"local_only" / "no_cookie" / "infra_error" / None
    skip_reason: Optional[str] = None
    # 本次解题累计 token 用量（provider 返 usage 时逐轮相加）
    prompt_tokens: int = 0
    completion_tokens: int = 0
    total_tokens: int = 0

    def to_dict(self) -> Dict[str, Any]:
        return asdict(self)


class SolveJournal:
    """AISolver 的指标与失败日志收敛点。"""

    def __init__(self, provider: AIProvider):
        self._metrics = ExperimentMetrics(
            provider=provider.name,
            model=provider.model,
            thinking_enabled=provider.use_reasoner,
        )

    @property
    def metrics(self) -> ExperimentMetrics:
        return self._metrics

    @property
    def failure_reason(self) -> Optional[str]:
        return self._metrics.failure_reason

    # --- 计数器 / 标量字段 ---
    def increment_api_call(self) -> None:
        self._metrics.api_calls += 1

    def add_api_time(self, elapsed: float) -> None:
        self._metrics.total_api_time += elapsed

    def add_usage(
        self,
        prompt_tokens: Optional[int] = None,
        completion_tokens: Optional[int] = None,
    ) -> None:
        """累加一次 API 的 token 用量；任一字段为 None 时忽略（兼容不返 usage 的 provider）。"""
        if prompt_tokens is not None:
            self._metrics.prompt_tokens += int(prompt_tokens)
        if completion_tokens is not None:
            self._metrics.completion_tokens += int(completion_tokens)
        self._metrics.total_tokens = (
            self._metrics.prompt_tokens + self._metrics.completion_tokens
        )

    def set_round(self, iteration_index: int) -> None:
        """iteration_index 是从 0 开始的计数，对外展示加 1。"""
        self._metrics.rounds = iteration_index + 1

    def set_solve_time(self, elapsed: float) -> None:
        self._metrics.total_solve_time = elapsed

    def set_success(self, value: bool) -> None:
        self._metrics.success = value

    def set_leetcode_passed(self, value: Optional[bool]) -> None:
        """
        True  → 真的 Accepted
        False → 真的被判错(WA/RE/TLE/CE)
        None  → 未提交或 infra 失败,本次没拿到判题信号
        """
        self._metrics.leetcode_passed = value

    def set_skip_reason(self, value: Optional[str]) -> None:
        """记录 leetcode_passed=None 时的归因标签。None 表示拿到了判题信号。"""
        self._metrics.skip_reason = value

    # --- 失败记录 ---
    def set_failure_reason(self, reason: str, *, overwrite: bool = False) -> None:
        """只更新 failure_reason，不打印日志。默认保留首次根因。"""
        if overwrite or not self._metrics.failure_reason:
            self._metrics.failure_reason = reason

    def record_failure(
        self,
        reason: str,
        *,
        exc: Optional[BaseException] = None,
        message: Optional[str] = None,
        overwrite: bool = False,
    ) -> None:
        """失败统一出口：更新 reason + 打印日志 + 可选 traceback。

        Args:
            reason: 机器可读的失败标签（如 ``stream_error:stream_timeout:60s``）
            exc: 异常对象；非 None 时自动 traceback.print_exc()
            message: 给人看的日志行；为 None 时从 reason 派生
            overwrite: 是否覆盖已有 failure_reason，默认 False
        """
        self.set_failure_reason(reason, overwrite=overwrite)
        log_with_time(message or f"❌ {reason}", ColorCode.RED)
        if exc is not None:
            traceback.print_exc()

    # --- 终局输出 ---
    def emit_summary(self) -> None:
        m = self._metrics
        print()
        log_with_time("📊 实验指标摘要", ColorCode.CYAN)
        log_with_time(f"   Provider/模型: {m.provider} / {m.model}", ColorCode.CYAN)
        log_with_time(f"   思考模式: {'开启' if m.thinking_enabled else '关闭'}", ColorCode.CYAN)
        log_with_time(f"   解题成功: {'✅' if m.success else '❌'}", ColorCode.CYAN)
        log_with_time(f"   对话轮数: {m.rounds}", ColorCode.CYAN)
        log_with_time(f"   API 调用次数: {m.api_calls}", ColorCode.CYAN)
        log_with_time(f"   API 总耗时: {m.total_api_time:.1f}s", ColorCode.CYAN)
        log_with_time(f"   解题总耗时: {m.total_solve_time:.1f}s", ColorCode.CYAN)
        if m.total_tokens > 0:
            log_with_time(
                f"   Token 用量: prompt {m.prompt_tokens} + completion {m.completion_tokens} = {m.total_tokens}",
                ColorCode.CYAN,
            )
        log_with_time(f"   LeetCode: {self._leetcode_summary_line()}", ColorCode.CYAN)
        if m.failure_reason:
            log_with_time(f"   失败原因: {m.failure_reason}", ColorCode.YELLOW)

    # 按 leetcode_passed + skip_reason 的组合给出明确文案
    _SKIP_HINTS = {
        "local_only": "⏭️  本地模式(require_leetcode=False,本地测试通过即完成)",
        "no_cookie": "⏭️  已跳过(LEETCODE_COOKIE 未配置)",
        "infra_error": "⚠️ 基础设施失败(cookie 过期 / 403 / 网络错误)",
    }

    def _leetcode_summary_line(self) -> str:
        m = self._metrics
        if m.leetcode_passed is True:
            return "✅ Accepted"
        if m.leetcode_passed is False:
            return "❌ 代码问题(WA/RE/TLE/CE)"
        return self._SKIP_HINTS.get(m.skip_reason, "⚠️ 未拿到判题信号(原因未归类)")

    def persist_if_enabled(self, problem_id: Optional[int]) -> None:
        """设置 AI_SOLVER_METRICS_DIR 时把本次指标落到磁盘。"""
        metrics_dir = os.getenv(AIConfig.METRICS_DIR_ENV)
        if not metrics_dir:
            return
        try:
            self._metrics.problem_id = problem_id
            out_dir = Path(metrics_dir)
            out_dir.mkdir(parents=True, exist_ok=True)
            pid = problem_id or "unknown"
            thinking = "on" if self._metrics.thinking_enabled else "off"
            out_path = (
                out_dir
                / f"metrics_p{pid}_{self._metrics.provider}_{self._metrics.model}_{thinking}.json"
            )
            out_path.write_text(
                json.dumps(self._metrics.to_dict(), ensure_ascii=False, indent=2),
                encoding="utf-8",
            )
            log_with_time(f"💾 指标已写入: {out_path}", ColorCode.CYAN)
        except Exception as e:
            log_with_time(f"⚠️ 指标写盘失败: {e}", ColorCode.YELLOW)
