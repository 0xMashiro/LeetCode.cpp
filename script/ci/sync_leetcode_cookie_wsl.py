#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
WSL 一键同步 LeetCode Cookie 到 GitHub Secret。

流程：
1) 在 Windows 侧启动 Edge/Chrome（开启 remote debugging）
2) 用户在浏览器里完成 LeetCode 登录（含验证码/2FA）
3) 脚本通过 CDP 读取 leetcode.com cookie
4) 校验有效性并写入 GitHub Secret
"""

import argparse
import json
import os
import shutil
import subprocess
import sys
import time
import urllib.error
import urllib.request
from pathlib import Path
from typing import Dict, List, Optional

from dotenv import load_dotenv

try:
    from script.ci.check_leetcode_cookie import validate_cookie
except ModuleNotFoundError:
    from check_leetcode_cookie import validate_cookie


def load_project_env() -> None:
    project_root = Path(__file__).resolve().parents[2]
    env_file = project_root / ".env"
    if env_file.exists():
        load_dotenv(dotenv_path=env_file)
    else:
        load_dotenv()


def _powershell_available() -> bool:
    return subprocess.run(
        ["bash", "-lc", "command -v powershell.exe >/dev/null 2>&1"],
        capture_output=True,
        text=True,
    ).returncode == 0


def start_windows_browser(debug_port: int, browser: str, url: str) -> None:
    if not _powershell_available():
        raise RuntimeError("WSL 未检测到 powershell.exe，无法拉起 Windows 浏览器。")

    ps = r"""
$ErrorActionPreference = "Stop"
$browser = "%BROWSER%"
$port = "%PORT%"
$url = "%URL%"

function Resolve-BrowserPath($name) {
  $cmd = Get-Command $name -ErrorAction SilentlyContinue
  if ($cmd) { return $cmd.Source }

  $paths = @()
  if ($name -eq "msedge") {
    $paths += "$env:ProgramFiles\Microsoft\Edge\Application\msedge.exe"
    $paths += "${env:ProgramFiles(x86)}\Microsoft\Edge\Application\msedge.exe"
  }
  if ($name -eq "chrome") {
    $paths += "$env:ProgramFiles\Google\Chrome\Application\chrome.exe"
    $paths += "${env:ProgramFiles(x86)}\Google\Chrome\Application\chrome.exe"
  }
  foreach ($p in $paths) {
    if (Test-Path $p) { return $p }
  }
  return $null
}

function Start-Browser($name) {
  $exe = Resolve-BrowserPath $name
  if ($exe) {
    $userDataDir = Join-Path $env:TEMP ("leetcode-cookie-sync-" + $port)
    $argArray = @(
      "--remote-debugging-port=$port",
      "--remote-debugging-address=0.0.0.0",
      "--user-data-dir=$userDataDir",
      "--no-first-run",
      "--no-default-browser-check",
      "--new-window",
      $url
    )
    Start-Process -FilePath $exe -ArgumentList $argArray | Out-Null
    return $true
  }
  return $false
}

if ($browser -eq "edge") {
  if (-not (Start-Browser "msedge")) { throw "msedge not found" }
} elseif ($browser -eq "chrome") {
  if (-not (Start-Browser "chrome")) { throw "chrome not found" }
} else {
  if (-not (Start-Browser "chrome")) {
    if (-not (Start-Browser "msedge")) {
      throw "Neither chrome nor msedge found (PATH and default install paths checked)"
    }
  }
}
"""
    ps = ps.replace("%BROWSER%", browser).replace("%PORT%", str(debug_port)).replace("%URL%", url)
    subprocess.run(
        ["powershell.exe", "-NoProfile", "-ExecutionPolicy", "Bypass", "-Command", ps],
        check=True,
    )


def read_cookies_via_cdp(debug_port: int) -> Dict[str, str]:
    try:
        from playwright.sync_api import sync_playwright  # type: ignore
    except ImportError as e:
        raise RuntimeError(
            "缺少依赖 playwright。请先执行: venv/bin/pip install playwright"
        ) from e

    endpoint = discover_cdp_endpoint(debug_port)
    with sync_playwright() as p:
        browser = p.chromium.connect_over_cdp(endpoint)
        cookie_map: Dict[str, str] = {}
        for ctx in browser.contexts:
            for c in ctx.cookies("https://leetcode.com"):
                name = c.get("name")
                value = c.get("value")
                if name and value:
                    cookie_map[name] = value
        browser.close()
        return cookie_map


def discover_cdp_endpoint(debug_port: int) -> str:
    candidates: List[str] = ["127.0.0.1", "localhost"]
    host_from_env = os.getenv("WSL_HOST_IP", "").strip()
    if host_from_env and host_from_env not in candidates:
        candidates.append(host_from_env)

    # Parse default gateway from /proc/net/route (WSL host often appears here)
    route_file = Path("/proc/net/route")
    if route_file.exists():
        for line in route_file.read_text(encoding="utf-8", errors="ignore").splitlines()[1:]:
            cols = line.split()
            if len(cols) < 3:
                continue
            destination, gateway_hex = cols[1], cols[2]
            if destination != "00000000":
                continue
            try:
                gw_bytes = bytes.fromhex(gateway_hex)
                gateway_ip = ".".join(str(b) for b in gw_bytes[::-1])
                if gateway_ip and gateway_ip not in candidates:
                    candidates.append(gateway_ip)
            except ValueError:
                pass

    resolv = Path("/etc/resolv.conf")
    if resolv.exists():
        for line in resolv.read_text(encoding="utf-8", errors="ignore").splitlines():
            line = line.strip()
            if line.startswith("nameserver "):
                ip = line.split(maxsplit=1)[1].strip()
                if ip and ip not in candidates:
                    candidates.append(ip)

    errors: List[str] = []
    for _ in range(6):
        for host in candidates:
            http_url = f"http://{host}:{debug_port}/json/version"
            try:
                with urllib.request.urlopen(http_url, timeout=1.5) as resp:
                    payload = resp.read().decode("utf-8", errors="ignore")
                data = json.loads(payload)
                ws_url = data.get("webSocketDebuggerUrl")
                if ws_url:
                    # If browser returns localhost/127.0.0.1, rewrite host to the host that worked.
                    return ws_url.replace("://127.0.0.1:", f"://{host}:").replace(
                        "://localhost:", f"://{host}:"
                    )
            except (urllib.error.URLError, urllib.error.HTTPError, TimeoutError, json.JSONDecodeError) as e:
                errors.append(f"{http_url} -> {e}")
                continue
        time.sleep(1)

    last_error = errors[-1] if errors else "no response"
    raise RuntimeError(
        "无法连接到浏览器 DevTools(CDP)。"
        f"已尝试主机: {', '.join(candidates)} 端口: {debug_port}。最后错误: {last_error}"
    )


def build_cookie_string(cookie_map: Dict[str, str]) -> str:
    required = ["csrftoken", "LEETCODE_SESSION"]
    missing = [k for k in required if k not in cookie_map]
    if missing:
        raise RuntimeError(f"缺少关键 Cookie: {', '.join(missing)}。请确认已登录 leetcode.com。")

    parts = [f"csrftoken={cookie_map['csrftoken']}", f"LEETCODE_SESSION={cookie_map['LEETCODE_SESSION']}"]
    for k in ("cf_clearance", "INGRESSCOOKIE"):
        if k in cookie_map:
            parts.append(f"{k}={cookie_map[k]}")
    return "; ".join(parts)


def update_github_secret(secret_name: str, secret_value: str, repo: Optional[str]) -> None:
    gh_candidates: List[str] = []
    for bin_name in ("gh", "gh.exe"):
        resolved = shutil.which(bin_name)
        if resolved and resolved not in gh_candidates:
            gh_candidates.append(resolved)

    if not gh_candidates:
        raise RuntimeError("未找到 GitHub CLI。请先在 WSL 安装 gh，或确保 gh.exe 可执行。")

    permission_errors: List[str] = []
    for gh_bin in gh_candidates:
        cmd = [gh_bin, "secret", "set", secret_name, "--body", secret_value]
        if repo:
            cmd.extend(["--repo", repo])
        try:
            subprocess.run(cmd, check=True)
            return
        except PermissionError as e:
            permission_errors.append(f"{gh_bin}: {e}")
            continue
        except subprocess.CalledProcessError as e:
            raise RuntimeError(
                f"gh 执行失败（{gh_bin}，exit={e.returncode}）。"
                "请先执行 `gh auth status` 确认登录状态。"
            ) from e

    raise RuntimeError(
        "检测到 gh 但不可执行。"
        f"候选: {', '.join(gh_candidates)}; 错误: {' | '.join(permission_errors)}"
    )


def main() -> int:
    load_project_env()

    parser = argparse.ArgumentParser(description="WSL cookie sync via Windows browser + CDP")
    parser.add_argument("--repo", default=os.getenv("GITHUB_REPO"), help="owner/repo")
    parser.add_argument("--secret-name", default="LEETCODE_COOKIE", help="GitHub secret name")
    parser.add_argument(
        "--browser",
        default="auto",
        choices=["auto", "chrome", "edge"],
        help="Windows browser (auto prefers chrome)",
    )
    parser.add_argument("--debug-port", type=int, default=9222, help="CDP port")
    parser.add_argument("--dry-run", action="store_true", help="Only validate, do not update secret")
    args = parser.parse_args()

    print("正在启动 Windows 浏览器并打开 LeetCode 登录页...")
    start_windows_browser(args.debug_port, args.browser, "https://leetcode.com/accounts/login/")
    print("请在打开的浏览器中完成登录，然后回到这里按回车继续。")
    input("完成登录后按回车: ")

    cookie_map = read_cookies_via_cdp(args.debug_port)
    cookie = build_cookie_string(cookie_map)

    valid, reason, username = validate_cookie(cookie)
    if not valid:
        print(f"Cookie 校验失败: {reason}", file=sys.stderr)
        return 1

    print(f"Cookie 有效，用户: {username}")
    if args.dry_run:
        print("dry-run 模式：未更新 GitHub Secret")
        return 0

    update_github_secret(args.secret_name, cookie, args.repo)
    print(f"已更新 GitHub Secret: {args.secret_name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
