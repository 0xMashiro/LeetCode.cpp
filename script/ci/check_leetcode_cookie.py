#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
检查 LEETCODE_COOKIE 是否有效。
"""

import argparse
import json
import os
import sys
import urllib.error
import urllib.request
from pathlib import Path
from typing import Optional, Tuple

try:
    from dotenv import load_dotenv
except ModuleNotFoundError:
    load_dotenv = None  # type: ignore[assignment]

try:
    from script.leetcode.cookie import prepare_cookie
except ModuleNotFoundError:
    # 兼容直接以脚本路径执行：python script/ci/check_leetcode_cookie.py
    project_root = Path(__file__).resolve().parents[2]
    sys.path.insert(0, str(project_root))
    from script.leetcode.cookie import prepare_cookie


GRAPHQL_URL = "https://leetcode.com/graphql"


def load_project_env() -> None:
    if load_dotenv is None:
        return
    project_root = Path(__file__).resolve().parents[2]
    env_file = project_root / ".env"
    if env_file.exists():
        load_dotenv(dotenv_path=env_file)
    else:
        load_dotenv()


def validate_cookie(cookie: str, timeout: int = 15) -> Tuple[bool, str, Optional[str]]:
    if not cookie:
        return False, "cookie_missing", None

    cookie, csrf = prepare_cookie(cookie)
    csrf = csrf or ""
    payload = {
        "query": """
            query globalData {
              userStatus {
                isSignedIn
                username
              }
            }
        """,
        "variables": {},
    }
    headers = {
        "Cookie": cookie,
        "Content-Type": "application/json",
        "User-Agent": "Mozilla/5.0",
        "Referer": "https://leetcode.com/",
        "x-csrftoken": csrf,
    }

    try:
        req = urllib.request.Request(
            GRAPHQL_URL,
            data=json.dumps(payload).encode("utf-8"),
            headers=headers,
            method="POST",
        )
        with urllib.request.urlopen(req, timeout=timeout) as resp:
            data = json.loads(resp.read().decode("utf-8"))

        if "errors" in data:
            return False, "graphql_error", None

        user_status = data.get("data", {}).get("userStatus", {})
        if user_status.get("isSignedIn") and user_status.get("username"):
            return True, "ok", user_status.get("username")
        return False, "not_signed_in", None
    except urllib.error.HTTPError as e:
        return False, f"http_{e.code}", None
    except urllib.error.URLError:
        return False, "network_error", None
    except Exception:
        return False, "unknown_error", None


def write_github_output(valid: bool, reason: str, username: Optional[str]) -> None:
    output_path = os.getenv("GITHUB_OUTPUT")
    if not output_path:
        return
    with open(output_path, "a", encoding="utf-8") as f:
        f.write(f"valid={'true' if valid else 'false'}\n")
        f.write(f"reason={reason}\n")
        f.write(f"username={username or ''}\n")


def main() -> int:
    load_project_env()

    parser = argparse.ArgumentParser(description="Check LEETCODE_COOKIE validity.")
    parser.add_argument(
        "--cookie",
        default=os.getenv("LEETCODE_COOKIE", ""),
        help="Cookie string. Defaults to LEETCODE_COOKIE env.",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="Exit non-zero when cookie is invalid.",
    )
    args = parser.parse_args()

    valid, reason, username = validate_cookie(args.cookie)
    write_github_output(valid, reason, username)

    if valid:
        print(f"LEETCODE_COOKIE is valid (user: {username}).")
        return 0

    print(f"LEETCODE_COOKIE is invalid ({reason}).")
    if args.strict:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
