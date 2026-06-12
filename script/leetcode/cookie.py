#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""LeetCode cookie normalization and CSRF refresh helpers."""

import re
import urllib.request
from http.client import HTTPMessage
from typing import Optional, Tuple

USER_AGENT = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36"
COOKIE_ATTR_NAMES = {
    "domain",
    "expires",
    "httponly",
    "max-age",
    "path",
    "samesite",
    "secure",
}


def extract_csrf_token(cookie: str) -> Optional[str]:
    match = re.search(r"(?:^|;\s*)csrftoken=([^;]+)", cookie)
    return match.group(1) if match else None


def normalize_cookie_header(cookie: str) -> str:
    """Return a Cookie request header from browser/Set-Cookie style input."""
    pairs = []
    for part in cookie.split(";"):
        item = part.strip()
        if not item:
            continue
        if "=" not in item:
            if item.lower() not in COOKIE_ATTR_NAMES:
                pairs.append(item)
            continue
        name, value = item.split("=", 1)
        if name.strip().lower() in COOKIE_ATTR_NAMES:
            continue
        pairs.append(f"{name.strip()}={value.strip()}")
    return "; ".join(pairs)


def prepare_cookie(cookie: str) -> Tuple[str, Optional[str]]:
    """Normalize LEETCODE_COOKIE and refresh csrftoken from LeetCode when possible."""
    normalized = normalize_cookie_header(cookie)
    fetched = fetch_csrf_token(normalized)
    if fetched:
        return upsert_cookie(normalized, "csrftoken", fetched), fetched
    return normalized, extract_csrf_token(normalized)


def fetch_csrf_token(cookie: str) -> Optional[str]:
    headers = {
        "Cookie": cookie,
        "User-Agent": USER_AGENT,
        "Referer": "https://leetcode.com/",
    }
    try:
        req = urllib.request.Request("https://leetcode.com/", headers=headers, method="GET")
        with urllib.request.urlopen(req, timeout=15) as response:
            return extract_csrf_from_headers(response.headers)
    except Exception:
        return None


def extract_csrf_from_headers(headers: HTTPMessage) -> Optional[str]:
    set_cookie_headers = headers.get_all("Set-Cookie", []) if headers else []
    for item in set_cookie_headers:
        match = re.search(r"(?:^|,\s*)csrftoken=([^;,]+)", item)
        if match:
            return match.group(1)
    return None


def upsert_cookie(cookie: str, name: str, value: str) -> str:
    parts = []
    replaced = False
    for part in cookie.split(";"):
        item = part.strip()
        if not item:
            continue
        current_name = item.split("=", 1)[0].strip()
        if current_name == name:
            parts.append(f"{name}={value}")
            replaced = True
        else:
            parts.append(item)
    if not replaced:
        parts.insert(0, f"{name}={value}")
    return "; ".join(parts)
