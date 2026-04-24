@echo off
setlocal
cd /d "%~dp0"
powershell -NoProfile -ExecutionPolicy Bypass -File ".\script\ci\cookie_update_windows.ps1" %*
echo.
if errorlevel 1 (
  echo Cookie update failed.
) else (
  echo Cookie update succeeded.
)
pause
