#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
OpenAI 兼容 API 的流式调用封装。

把 solver.py 中低级的流消费、chunk 拼接、token 累加等逻辑隔离出去，
让 AISolver 只关心"发一条消息拿一个 Message 回来"。
"""

import time
from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional

from openai import OpenAI

from script.leetcode.ai.messages import Message, ToolCall
from script.leetcode.config import AIConfig, AIProvider
from script.leetcode.exceptions import StreamResponseError
from script.leetcode.utils import ColorCode, color_text, log_with_time


@dataclass
class _StreamResult:

    content: str = ""
    reasoning: str = ""
    tool_calls: List[Dict[str, Any]] = field(default_factory=list)
    aborted_reason: Optional[str] = None
    first_chunk_received: bool = False
    chunk_count: int = 0
    prompt_tokens: Optional[int] = None
    completion_tokens: Optional[int] = None


class AIApiClient:

    def __init__(self, provider: AIProvider, api_key: str, base_url: str):
        self.provider = provider
        self.use_reasoner = provider.use_reasoner
        self.client = OpenAI(api_key=api_key, base_url=base_url)

    def call(
        self,
        messages: List[Dict[str, Any]],
        tools: List[Dict[str, Any]],
        *,
        journal: Any,
        reasoning_log_collector: Optional[Any] = None,
    ) -> Message:
        """流式请求，返回 Message。"""
        start_time = time.time()
        think_label = "(Think ON)" if self.use_reasoner else "(Think OFF)"
        log_with_time(f"⏳ 开始调用 AI API... {think_label}", ColorCode.CYAN)

        params = self._build_api_params(messages, tools)
        stream = self.client.chat.completions.create(**params)
        try:
            result = self._consume_stream(stream, reasoning_log_collector)
        finally:
            try:
                stream.close()
            except Exception:
                pass

        print()
        elapsed = time.time() - start_time
        journal.add_api_time(elapsed)
        journal.add_usage(
            prompt_tokens=result.prompt_tokens,
            completion_tokens=result.completion_tokens,
        )

        if result.aborted_reason:
            raise StreamResponseError(result.aborted_reason)
        if not result.first_chunk_received:
            raise StreamResponseError("no_chunks_received")

        usage_note = ""
        if result.prompt_tokens is not None:
            total = (result.prompt_tokens or 0) + (result.completion_tokens or 0)
            usage_note = (
                f" | tokens: {result.prompt_tokens}+"
                f"{result.completion_tokens or 0}={total}"
            )
        log_with_time(
            f"✅ API 调用完成，耗时 {elapsed:.2f}s{usage_note}", ColorCode.GREEN
        )

        return Message(
            content=result.content,
            reasoning_content=result.reasoning if self.use_reasoner else None,
            tool_calls=self._to_tool_calls(result.tool_calls),
        )

    def _build_api_params(
        self, messages: List[Dict[str, Any]], tools: List[Dict[str, Any]]
    ) -> Dict[str, Any]:
        params: Dict[str, Any] = {
            "model": self.provider.model,
            "messages": messages,
            "tools": tools,
            "stream": True,
            "stream_options": {"include_usage": True},
        }
        params.update(self.provider.build_request_kwargs(allow_temperature=False))
        return params

    def _consume_stream(
        self,
        stream: Any,
        collector: Optional[Any],
    ) -> _StreamResult:
        result = _StreamResult()
        last_chunk_time = time.time()
        current_reasoning = ""

        for chunk in stream:
            result.chunk_count += 1
            if result.chunk_count > AIConfig.STREAM_MAX_CHUNKS:
                result.aborted_reason = f"max_chunks_exceeded:{AIConfig.STREAM_MAX_CHUNKS}"
                print(
                    color_text(
                        f"\n⚠️ 达到最大 chunk 数限制 ({AIConfig.STREAM_MAX_CHUNKS})，强制结束流",
                        ColorCode.YELLOW.value,
                    )
                )
                break

            current_time = time.time()
            if current_time - last_chunk_time > AIConfig.STREAM_TIMEOUT_SECONDS:
                result.aborted_reason = f"stream_timeout:{AIConfig.STREAM_TIMEOUT_SECONDS}s"
                print(
                    color_text(
                        f"\n⚠️ 流响应超时({AIConfig.STREAM_TIMEOUT_SECONDS}秒无数据)，强制结束",
                        ColorCode.YELLOW.value,
                    )
                )
                break

            usage = getattr(chunk, "usage", None)
            if usage is not None:
                result.prompt_tokens = getattr(usage, "prompt_tokens", None)
                result.completion_tokens = getattr(usage, "completion_tokens", None)

            if not chunk.choices:
                continue

            delta = chunk.choices[0].delta
            last_chunk_time = current_time
            current_reasoning = self._absorb_delta(delta, result, current_reasoning)

        # 流结束后把最后的 reasoning/content 落到日志
        if collector is not None:
            collector.record(current_reasoning, result.content)

        return result

    def _absorb_delta(
        self, delta: Any, result: _StreamResult, current_reasoning: str
    ) -> str:
        if not result.first_chunk_received:
            print("\r" + " " * 30 + "\r", end="", flush=True)
            result.first_chunk_received = True
            if self.use_reasoner:
                print(color_text("🧠 思考过程: ", ColorCode.CYAN.value), end="", flush=True)

        reasoning_delta = getattr(delta, "reasoning_content", None)
        if reasoning_delta:
            result.reasoning += reasoning_delta
            current_reasoning += reasoning_delta
            print(reasoning_delta, end="", flush=True)

        content_delta = getattr(delta, "content", None)
        if content_delta:
            if not result.content and self.use_reasoner and result.reasoning:
                print()  # 思考结束换行
            if not result.content:
                print(color_text("\n💬 回复:", ColorCode.BLUE.value), end="", flush=True)
            result.content += content_delta
            print(content_delta, end="", flush=True)

        tool_call_deltas = getattr(delta, "tool_calls", None)
        if tool_call_deltas:
            result.tool_calls = self._merge_tool_calls(
                tool_call_deltas, result.tool_calls
            )

        return current_reasoning

    @staticmethod
    def _merge_tool_calls(deltas: List[Any], existing: List[Dict]) -> List[Dict]:
        result = existing.copy() if existing else []
        for delta in deltas:
            index = delta.index
            while len(result) <= index:
                result.append(
                    {
                        "id": "",
                        "type": "function",
                        "function": {"name": "", "arguments": ""},
                    }
                )
            if delta.id:
                result[index]["id"] = delta.id
            if delta.type:
                result[index]["type"] = delta.type
            if hasattr(delta, "function"):
                if delta.function.name:
                    result[index]["function"]["name"] = delta.function.name
                if delta.function.arguments:
                    result[index]["function"]["arguments"] += delta.function.arguments
        return result

    @staticmethod
    def _to_tool_calls(raw: List[Dict[str, Any]]) -> Optional[List[ToolCall]]:
        if not raw:
            return None
        converted = [
            ToolCall(
                id=tc.get("id", ""),
                type=tc.get("type", "function"),
                function_name=tc.get("function", {}).get("name", ""),
                function_arguments=tc.get("function", {}).get("arguments", ""),
            )
            for tc in raw
            if tc.get("id")
        ]
        return converted or None
