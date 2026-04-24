param(
  [string]$Repo = "0xMashiro/LeetCode.cpp",
  [switch]$Silent,
  [switch]$DryRun
)

# ============================================================================
# Windows 侧 LeetCode Cookie 同步
#
# 交互用:   .\cookie_update_windows.ps1
# 定时用:   .\cookie_update_windows.ps1 -Silent
#           在 Task Scheduler 里注册一个 Weekly 触发器,action 指向 powershell.exe,
#           args:  -NoProfile -ExecutionPolicy Bypass -File <this.ps1> -Silent
# 验证用:   .\cookie_update_windows.ps1 -DryRun
#           走到"会发 webhook"的分支时只打印 payload,不真的 POST
#
# 失败处理:
#   - 以 -Silent 运行时不打印正常流程日志
#   - 任何 throw 都会被捕获并(如 .env 里有 LEETCODE_COOKIE_ALERT_WEBHOOK_URL)
#     POST 到企微/飞书通用 text 消息 webhook
#   - 退出码永远 0(不打扰 Task Scheduler 历史列表)
# ============================================================================

$ErrorActionPreference = "Stop"

function Step($msg) {
  if (-not $Silent) { Write-Host "== $msg" -ForegroundColor Cyan }
}

function Resolve-PythonExe {
  if (Get-Command py -ErrorAction SilentlyContinue) { return "py" }
  if (Get-Command python -ErrorAction SilentlyContinue) { return "python" }
  if (Get-Command python3 -ErrorAction SilentlyContinue) { return "python3" }
  throw "Python not found on Windows PATH. Please install Python first."
}

function Invoke-Python([string[]]$ArgList) {
  $exe = Resolve-PythonExe
  if ($exe -eq "py") { & py -3 @ArgList } else { & $exe @ArgList }
}

function Get-WebhookUrl($projectRoot) {
  # 优先级:当前进程 env > 项目 .env 文件
  if ($env:LEETCODE_COOKIE_ALERT_WEBHOOK_URL) {
    return $env:LEETCODE_COOKIE_ALERT_WEBHOOK_URL
  }
  $envFile = Join-Path $projectRoot ".env"
  if (-not (Test-Path $envFile)) { return $null }

  $line = Get-Content $envFile | Where-Object { $_ -match '^\s*LEETCODE_COOKIE_ALERT_WEBHOOK_URL=' } | Select-Object -First 1
  if (-not $line) { return $null }
  $value = ($line -replace '^\s*LEETCODE_COOKIE_ALERT_WEBHOOK_URL=', '').Trim()
  $value = $value -replace "^['""]", "" -replace "['""]$", ""
  if ([string]::IsNullOrWhiteSpace($value)) { return $null }
  return $value
}

function Send-FailureWebhook($webhookUrl, $reason, $projectRoot) {
  $body = @{
    msgtype = "text"
    text = @{
      content = "【LeetCode Cookie 同步失败】`n主机: $env:COMPUTERNAME`n原因: $reason`n脚本: $PSCommandPath`n建议: 在浏览器重新登录 leetcode.com 后再试"
    }
  } | ConvertTo-Json -Depth 4 -Compress

  if ($DryRun) {
    Write-Host "--- DRY RUN: would POST to webhook ---"
    Write-Host "URL:  $webhookUrl"
    Write-Host "BODY: $body"
    return
  }

  try {
    Invoke-RestMethod -Uri $webhookUrl -Method Post -ContentType 'application/json' -Body $body -TimeoutSec 10 | Out-Null
  } catch {
    # 静默失败,避免二级异常污染 Task Scheduler
  }
}

$projectRoot = $null
try {
  $projectRoot = Resolve-Path "$PSScriptRoot\..\.."
  Set-Location $projectRoot

  Step "Project root: $projectRoot"

  if (-not (Test-Path ".\venv\Scripts\python.exe")) {
    Step "Create venv"
    Invoke-Python @("-m", "venv", "venv")
  }

  $python = ".\venv\Scripts\python.exe"

  Step "Install dependencies"
  if ($Silent) {
    & $python -m pip install --upgrade pip -q | Out-Null
    & $python -m pip install -r requirements.txt browser-cookie3 -q | Out-Null
  } else {
    & $python -m pip install --upgrade pip
    & $python -m pip install -r requirements.txt browser-cookie3
  }

  if (-not (Get-Command gh -ErrorAction SilentlyContinue)) {
    throw "GitHub CLI (gh) not found. Install it and run: gh auth login"
  }

  Step "Check gh auth"
  if ($Silent) { & gh auth status 2>&1 | Out-Null } else { & gh auth status }

  Step "Dry run (read browser cookie + validate)"
  if ($Silent) {
    & $python .\script\ci\sync_leetcode_cookie.py --repo $Repo --dry-run 2>&1 | Out-Null
  } else {
    & $python .\script\ci\sync_leetcode_cookie.py --repo $Repo --dry-run
  }
  if ($LASTEXITCODE -ne 0) {
    throw "Browser cookie read/validate failed. User likely not signed in on leetcode.com."
  }

  if ($DryRun) {
    Step "DryRun mode: skipping real secret update"
    if (-not $Silent) { Write-Host "Cookie update would succeed (dry-run)." -ForegroundColor Green }
    exit 0
  }

  Step "Update GitHub secret"
  if ($Silent) {
    & $python .\script\ci\sync_leetcode_cookie.py --repo $Repo 2>&1 | Out-Null
  } else {
    & $python .\script\ci\sync_leetcode_cookie.py --repo $Repo
  }
  if ($LASTEXITCODE -ne 0) {
    throw "GitHub secret update failed."
  }

  if (-not $Silent) {
    Write-Host ""
    Write-Host "Cookie update completed." -ForegroundColor Green
  }
  exit 0
}
catch {
  $reason = $_.Exception.Message
  if (-not $Silent) {
    Write-Host ""
    Write-Host "Failed: $reason" -ForegroundColor Red
  }
  if ($projectRoot) {
    $webhook = Get-WebhookUrl $projectRoot
    if ($webhook) {
      Send-FailureWebhook $webhook $reason $projectRoot
    }
  }
  # Silent 模式给 Task Scheduler 永远返回 0,避免在 Windows 事件日志里堆告警
  if ($Silent) { exit 0 } else { exit 1 }
}
