#!/usr/bin/env bash
# ============================================================================
# LeetCode Cookie 定时监控(WSL / Linux cron 用)
#
# 跑法:
#   正常:  在用户 crontab 里加一行,例如:
#          0 9 * * 1 /home/chai/workspace/LeetCode.cpp/script/ci/scheduled_cookie_watch.sh
#   验证:  加 --dry-run 参数,只打印 payload,不发 webhook
#          ./script/ci/scheduled_cookie_watch.sh --dry-run
#
# 行为:
#   1. 先用 check_leetcode_cookie.py ping GraphQL,确认当前 LEETCODE_COOKIE 状态
#   2. cookie 有效                                  → 完全静默,退出 0
#   3. cookie 失效 + LEETCODE_COOKIE_ALERT_WEBHOOK_URL 已设置 → POST 飞书/企微告警
#   4. 任何一步都不会把 stderr 泄漏到系统日志;退出码永远 0(cron 不要嚷嚷)
#
# 环境:
#   从项目 .env 自动加载 LEETCODE_COOKIE 和 LEETCODE_COOKIE_ALERT_WEBHOOK_URL
# ============================================================================

set -u

DRY_RUN=0
for arg in "$@"; do
    case "$arg" in
        --dry-run) DRY_RUN=1 ;;
    esac
done

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$PROJECT_ROOT" || exit 0

# venv 或系统 python 都接受
if [[ -x "$PROJECT_ROOT/venv/bin/python" ]]; then
    PYTHON="$PROJECT_ROOT/venv/bin/python"
else
    PYTHON="python3"
fi

# 载入 .env 里的变量到当前 shell(只要 KEY=VALUE 那几行)
if [[ -f "$PROJECT_ROOT/.env" ]]; then
    set -a
    # shellcheck disable=SC1090
    source <(grep -E '^[A-Z_]+=' "$PROJECT_ROOT/.env" | sed -E 's/^([A-Z_]+)=(["'\''])(.*)\2$/\1=\3/')
    set +a
fi

LOG_DIR="$PROJECT_ROOT/.cookie-watch"
mkdir -p "$LOG_DIR"
LOG_FILE="$LOG_DIR/last-run.log"
STATE_FILE="$LOG_DIR/last-state"

timestamp() { date '+%Y-%m-%d %H:%M:%S'; }

# 跑检测,结果放在临时文件里解析
CHECK_OUT="$(mktemp)"
trap 'rm -f "$CHECK_OUT"' EXIT

"$PYTHON" "$PROJECT_ROOT/script/ci/check_leetcode_cookie.py" >"$CHECK_OUT" 2>&1
STATUS_LINE="$(cat "$CHECK_OUT")"

# check 脚本的标准输出只有一行 "valid" 或 "invalid (reason)"
if grep -q "is valid" "$CHECK_OUT"; then
    STATE="valid"
else
    STATE="invalid"
fi

echo "[$(timestamp)] state=$STATE | $STATUS_LINE" >"$LOG_FILE"

if [[ "$STATE" == "valid" ]]; then
    echo "valid" >"$STATE_FILE"
    exit 0
fi

# 失效分支 —— 仅在状态从 valid→invalid 跨变时发告警,避免重复打扰
PREV_STATE="unknown"
[[ -f "$STATE_FILE" ]] && PREV_STATE="$(cat "$STATE_FILE")"
echo "invalid" >"$STATE_FILE"

if [[ "$PREV_STATE" == "invalid" ]]; then
    echo "[$(timestamp)] still-invalid (skipping webhook)" >>"$LOG_FILE"
    exit 0
fi

WEBHOOK="${LEETCODE_COOKIE_ALERT_WEBHOOK_URL:-}"
if [[ -z "$WEBHOOK" ]]; then
    echo "[$(timestamp)] webhook URL not set; skipping alert" >>"$LOG_FILE"
    exit 0
fi

# 构造企微/飞书通用的 text 消息
REASON="$(echo "$STATUS_LINE" | sed -E 's/.*\((.*)\).*/\1/')"
PAYLOAD=$(cat <<EOF
{"msgtype":"text","text":{"content":"【LeetCode Cookie 告警】\n主机: $(hostname)\n状态: 无效\n原因: $REASON\n建议: 在 Windows 浏览器里重新登录 leetcode.com, 然后运行 cookie-update 脚本"}}
EOF
)

if [[ "$DRY_RUN" -eq 1 ]]; then
    echo "[$(timestamp)] dry-run: would POST to webhook" >>"$LOG_FILE"
    echo "--- DRY RUN: webhook payload ---"
    echo "URL: $WEBHOOK"
    echo "BODY: $PAYLOAD"
    exit 0
fi

HTTP_CODE="$(curl -sS -o /dev/null -w '%{http_code}' -X POST "$WEBHOOK" \
    -H 'Content-Type: application/json' \
    -d "$PAYLOAD" 2>/dev/null || echo "network_error")"
echo "[$(timestamp)] webhook_post http=$HTTP_CODE" >>"$LOG_FILE"

exit 0
