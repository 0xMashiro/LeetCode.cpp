#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
从本机浏览器读取 LeetCode Cookie，并更新 GitHub Secret。

依赖：
  pip install browser-cookie3
  gh auth login
"""

import argparse
import http.cookiejar
import os
import subprocess
import sys
from pathlib import Path
from typing import Dict, Iterable, Optional, Tuple

from dotenv import load_dotenv

try:
    from script.ci.check_leetcode_cookie import validate_cookie
except ModuleNotFoundError:
    # 兼容直接以脚本路径执行：python script/ci/sync_leetcode_cookie.py
    from check_leetcode_cookie import validate_cookie


def load_project_env() -> None:
    project_root = Path(__file__).resolve().parents[2]
    env_file = project_root / ".env"
    if env_file.exists():
        load_dotenv(dotenv_path=env_file)
    else:
        load_dotenv()


def load_cookiejar(browser: str) -> http.cookiejar.CookieJar:
    try:
        import browser_cookie3  # type: ignore
    except ImportError as e:
        raise RuntimeError(
            "缺少依赖 browser-cookie3。请先执行: pip install browser-cookie3"
        ) from e

    if browser == "auto":
        if sys.platform.startswith("linux"):
            candidates = ["chrome", "chromium", "edge", "firefox", "brave", "opera"]
        elif sys.platform == "darwin":
            candidates = ["chrome", "edge", "firefox", "brave", "opera", "safari"]
        else:
            candidates = ["chrome", "edge", "firefox", "brave", "opera"]
    else:
        candidates = [browser]

    errors: Dict[str, str] = {}
    for name in candidates:
        loader = getattr(browser_cookie3, name, None)
        if loader is None:
            continue
        try:
            jar = loader(domain_name="leetcode.com")
            return jar
        except Exception as e:  # noqa: BLE001
            errors[name] = str(e)
            continue

    if errors:
        reason = "; ".join(f"{k}={v}" for k, v in errors.items())
        raise RuntimeError(
            "无法从浏览器读取 Cookie。"
            f"可尝试指定浏览器参数 --browser <name>。详细原因: {reason}"
        )
    raise RuntimeError("未找到可用的浏览器 Cookie 读取器")


def collect_leetcode_cookie(jar: Iterable) -> Tuple[str, Dict[str, str]]:
    cookie_map: Dict[str, str] = {}
    for c in jar:
        domain = getattr(c, "domain", "") or ""
        if "leetcode.com" not in domain:
            continue
        name = getattr(c, "name", "")
        value = getattr(c, "value", "")
        if name and value:
            cookie_map[name] = value

    required = ["csrftoken", "LEETCODE_SESSION"]
    missing = [k for k in required if k not in cookie_map]
    if missing:
        raise RuntimeError(
            f"缺少关键 Cookie: {', '.join(missing)}。请先在浏览器登录 leetcode.com。"
        )

    cookie_parts = [f"csrftoken={cookie_map['csrftoken']}", f"LEETCODE_SESSION={cookie_map['LEETCODE_SESSION']}"]
    for k in ("cf_clearance", "INGRESSCOOKIE"):
        if k in cookie_map:
            cookie_parts.append(f"{k}={cookie_map[k]}")

    return "; ".join(cookie_parts), cookie_map


def update_github_secret(secret_name: str, secret_value: str, repo: Optional[str]) -> None:
    cmd = ["gh", "secret", "set", secret_name, "--body", secret_value]
    if repo:
        cmd.extend(["--repo", repo])
    subprocess.run(cmd, check=True)


def main() -> int:
    load_project_env()

    parser = argparse.ArgumentParser(description="Sync LeetCode cookie to GitHub secret.")
    parser.add_argument("--browser", default="auto", help="auto/chrome/chromium/edge/firefox/brave/opera/safari")
    parser.add_argument("--secret-name", default="LEETCODE_COOKIE", help="GitHub secret name")
    parser.add_argument(
        "--repo",
        default=os.getenv("GITHUB_REPO"),
        help="GitHub repo, e.g. owner/name. Defaults to GITHUB_REPO in .env if set.",
    )
    parser.add_argument("--dry-run", action="store_true", help="Only validate cookie; do not update secret")
    args = parser.parse_args()

    jar = load_cookiejar(args.browser)
    cookie, cookie_map = collect_leetcode_cookie(jar)

    valid, reason, username = validate_cookie(cookie)
    if not valid:
        print(f"读取到的 Cookie 无效: {reason}", file=sys.stderr)
        return 1

    print(f"Cookie 有效，用户: {username}")
    print(f"已读取字段: {', '.join(sorted(cookie_map.keys()))}")

    if args.dry_run:
        print("dry-run 模式：未更新 GitHub Secret")
        return 0

    update_github_secret(args.secret_name, cookie, args.repo)
    print(f"已更新 GitHub Secret: {args.secret_name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
