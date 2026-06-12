#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""LeetCode 原始 HTTP 接口：cookie 校验、代码提交、判题轮询、结果解析。

纯 HTTP 层，不做翻译 / 编排 / 用户交互格式化（只有最小必要日志）。构造时传入
cookie + csrf_token，调用方已做过 None 判断。
"""

import json
import time
import urllib.error
import urllib.request
from datetime import datetime
from typing import Dict, Optional, Tuple

from script.leetcode.cookie import USER_AGENT as _USER_AGENT
from script.leetcode.submit.result import SubmissionResult
from script.leetcode.utils import ColorCode, color_text, log_with_time


def validate_cookie(cookie: str, csrf_token: Optional[str]) -> bool:
    """GraphQL `userStatus.isSignedIn` 检查，最多重试 3 次。"""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{timestamp}] 🔍 正在验证 LEETCODE_COOKIE...", end=" ", flush=True)

    headers = {
        "Cookie": cookie,
        "Content-Type": "application/json",
        "User-Agent": _USER_AGENT,
        "Referer": "https://leetcode.com/",
        "x-csrftoken": csrf_token or "",
    }
    body = json.dumps({
        "query": "query globalData { userStatus { isSignedIn username userId } }",
        "variables": {},
    }).encode("utf-8")

    for attempt in range(3):
        if attempt > 0:
            print(f"\n   重试 {attempt}/3...", end=" ", flush=True)
        try:
            req = urllib.request.Request(
                "https://leetcode.com/graphql", data=body, headers=headers, method="POST",
            )
            with urllib.request.urlopen(req, timeout=15) as response:
                data = json.loads(response.read().decode("utf-8"))
                if "errors" in data:
                    msg = data["errors"][0].get("message", "Unknown error")
                    print(color_text(f"❌ Cookie 无效 ({msg})", ColorCode.RED.value))
                    return False
                status = data.get("data", {}).get("userStatus", {})
                if status.get("isSignedIn") and status.get("username"):
                    print(color_text(
                        f"✅ Cookie 有效 (用户: {status['username']})", ColorCode.GREEN.value
                    ))
                    return True
                print(color_text("❌ Cookie 无效 (未登录)", ColorCode.RED.value))
                return False
        except urllib.error.HTTPError as e:
            if e.code in (401, 403):
                print(color_text(f"❌ Cookie 无效 (HTTP {e.code})", ColorCode.RED.value))
                return False
            if attempt == 2:
                print(color_text(f"⚠️  HTTP {e.code}", ColorCode.YELLOW.value))
                return False
        except urllib.error.URLError as e:
            if attempt == 2:
                print(color_text(f"⚠️  网络错误: {e.reason}", ColorCode.YELLOW.value))
                return False
        except Exception as e:
            if attempt == 2:
                print(color_text(f"⚠️  验证出错: {e}", ColorCode.YELLOW.value))
                return False
    return False


class LeetCodeHttpClient:
    def __init__(self, cookie: str, csrf_token: Optional[str]):
        self._cookie = cookie
        self._csrf = csrf_token or ""

    def submit(self, slug: str, question_id: str, code: str) -> SubmissionResult:
        """提交代码 → 返回最终判题 SubmissionResult；内部包括"提交 + 轮询"。"""
        log_with_time("🌐 正在提交到 LeetCode...")
        submit_url = f"https://leetcode.com/problems/{slug}/submit/"
        payload = {"lang": "cpp", "question_id": question_id, "typed_code": code}
        headers = {
            "Accept": "application/json, text/javascript, */*; q=0.01",
            "Content-Type": "application/json",
            "Cookie": self._cookie,
            "Origin": "https://leetcode.com",
            "X-CSRFToken": self._csrf,
            "Referer": f"https://leetcode.com/problems/{slug}/",
            "User-Agent": _USER_AGENT,
            "X-Requested-With": "XMLHttpRequest",
        }
        try:
            req = urllib.request.Request(
                submit_url,
                data=json.dumps(payload).encode("utf-8"),
                headers=headers,
                method="POST",
            )
            with urllib.request.urlopen(req, timeout=30) as response:
                data = json.loads(response.read().decode("utf-8"))
                submission_id = data.get("submission_id")
                if not submission_id:
                    return SubmissionResult(
                        status="Error",
                        status_code=-1,
                        error_message=f"提交失败: {data}",
                        error_type="submit_response_missing_id",
                    )
                log_with_time(f"✅ 提交成功，ID: {submission_id}")
                log_with_time("⏳ 等待判题结果...")
                return self._poll_verdict(submission_id)
        except urllib.error.HTTPError as e:
            error_type, message = _format_http_error(e)
            return SubmissionResult(
                status="Error", status_code=e.code, error_message=message, error_type=error_type
            )
        except urllib.error.URLError as e:
            return SubmissionResult(
                status="Error",
                status_code=-1,
                error_message=f"网络错误: {e.reason}",
                error_type="network_error",
            )
        except Exception as e:
            return SubmissionResult(
                status="Error", status_code=-1, error_message=str(e), error_type="unexpected_error"
            )

    def _poll_verdict(self, submission_id: str, max_wait: int = 60) -> SubmissionResult:
        check_url = f"https://leetcode.com/submissions/detail/{submission_id}/check/"
        headers = {
            "Cookie": self._cookie,
            "Referer": "https://leetcode.com/",
            "User-Agent": _USER_AGENT,
        }
        start = time.time()
        dots = 0
        while time.time() - start < max_wait:
            try:
                req = urllib.request.Request(check_url, headers=headers)
                with urllib.request.urlopen(req, timeout=10) as response:
                    data = json.loads(response.read().decode("utf-8"))
                    if data.get("state") == "SUCCESS":
                        print()
                        return _parse_verdict(data)
                    dots = (dots + 1) % 4
                    ts = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    print(f"\r[{ts}] ⏳ 判题中{'.' * dots}{' ' * (3 - dots)}", end="", flush=True)
                    time.sleep(1)
            except urllib.error.HTTPError as e:
                if e.code in (401, 403, 429, 499):
                    error_type, message = _format_http_error(e)
                    return SubmissionResult(
                        status="Error",
                        status_code=e.code,
                        error_message=message,
                        error_type=error_type,
                    )
                time.sleep(1)
            except Exception:
                time.sleep(1)
        return SubmissionResult(
            status="Timeout",
            status_code=-1,
            error_message="等待结果超时",
            error_type="poll_timeout",
        )


def _parse_verdict(raw: Dict) -> SubmissionResult:
    status_code = raw.get("status_code", 0)
    status_msg = raw.get("status_msg", "Unknown")
    failed = None
    if status_code == 11:  # Wrong Answer
        failed = {
            "input": raw.get("input", "N/A"),
            "actual": raw.get("code_output", "N/A"),
            "expected": raw.get("expected_output", "N/A"),
        }
    return SubmissionResult(
        status=status_msg,
        status_code=status_code,
        total_test_cases=raw.get("total_testcases", 0),
        passed_test_cases=raw.get("total_correct", 0),
        failed_test_case=failed,
        runtime_ms=raw.get("status_runtime"),
        memory_mb=raw.get("status_memory"),
        error_message=raw.get("full_runtime_error") or raw.get("compile_error"),
    )


def _format_http_error(error: urllib.error.HTTPError) -> Tuple[str, str]:
    body = "<none>"
    try:
        raw = error.read()
        if raw:
            body = raw.decode("utf-8", errors="replace")[:1000]
    except Exception:
        pass
    return f"http_{error.code}", f"HTTP {error.code}: {body}"


def print_verdict(result: SubmissionResult) -> bool:
    """把 SubmissionResult 按 LeetCode 状态类型打印给人看；返回是否 Accepted。"""
    print()
    if result.status == "Accepted":
        log_with_time("✅ Accepted!", ColorCode.GREEN)
        log_with_time(f"   执行用时: {result.runtime_ms}")
        log_with_time(f"   内存消耗: {result.memory_mb}")
        return True
    if result.status == "Wrong Answer" and result.failed_test_case:
        log_with_time("❌ Wrong Answer", ColorCode.RED)
        log_with_time("\n输入:")
        log_with_time(result.failed_test_case.get("input", "N/A"))
        log_with_time("\n输出:")
        log_with_time(result.failed_test_case.get("actual", "N/A"))
        log_with_time("\n期望:")
        log_with_time(result.failed_test_case.get("expected", "N/A"))
        return False
    if result.status == "Time Limit Exceeded":
        log_with_time("⏱️  Time Limit Exceeded", ColorCode.YELLOW)
        return False
    if result.status == "Runtime Error":
        log_with_time("💥 Runtime Error", ColorCode.RED)
        log_with_time(f"错误信息: {result.error_message or 'N/A'}")
        return False
    log_with_time(f"❌ {result.status}", ColorCode.RED)
    if result.error_message:
        log_with_time(f"详情: {result.error_message}")
    return False
