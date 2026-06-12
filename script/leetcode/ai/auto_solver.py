#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 自动解题循环模式
持续运行 AI Solve 直到完善所有题解

用法:
    python -m script.leetcode.ai.auto_solver
    python -m script.leetcode.ai.auto_solver --report  # 生成解题报告
    python -m script.leetcode.ai.auto_solver --max-retries 5  # 最大重试次数
"""

import argparse
import os
import re
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import Optional, Set

from script.leetcode.utils import ColorCode, color_text


class AutoSolver:
    """自动解题循环器"""
    
    def __init__(
        self,
        report: bool = False,
        max_retries: int = 3,
        retry_delay: int = 60,
        fail_streak_limit: int = 3,
        fail_streak_pause: int = 60,
        api_key: Optional[str] = None,
        base_url: Optional[str] = None,
        require_leetcode: Optional[bool] = None,
    ):
        self.report = report
        self.max_retries = max_retries
        self.retry_delay = retry_delay
        self.fail_streak_limit = fail_streak_limit
        self.fail_streak_pause = fail_streak_pause
        self.api_key = api_key
        self.base_url = base_url
        # None=随子进程默认(env + 默认 True); True/False 都透传为显式 CLI flag
        self.require_leetcode = require_leetcode
        
        # 统计信息
        self.start_time = datetime.now()
        self.total_attempts = 0
        self.success_count = 0
        self.fail_streak = 0
        self.success_streak = 0
        self.failed_problem_ids: Set[int] = set()
    
    @staticmethod
    def _log(message: str, level: str = "INFO"):
        """打印带时间戳的日志"""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        level_colors = {
            "INFO": ColorCode.CYAN.value,
            "SUCCESS": ColorCode.GREEN.value,
            "WARNING": ColorCode.YELLOW.value,
            "ERROR": ColorCode.RED.value,
        }
        color = level_colors.get(level, ColorCode.RESET.value)
        level_tag = color_text(f"[{level}]", color)
        print(f"[{timestamp}] {level_tag} {message}")
    
    @staticmethod
    def _get_solved_count() -> int:
        """获取已解决的题目数量"""
        try:
            source_dir = Path("src/leetcode/problems")
            if not source_dir.exists():
                return 0
            return len(list(source_dir.glob("*.cpp")))
        except Exception:
            return 0
    
    def _analyze_failure(self, output: str) -> str:
        """分析失败原因（按优先级顺序匹配）"""
        patterns = [
            ("no_problem", r"No unsolved problems found|没有未解决的题目"),
            ("leetcode_failed", r"LeetCode 验证未通过|Wrong Answer|Runtime Error|Time Limit Exceeded"),
            ("compile_ambiguous", r"ambiguous|call of overloaded"),
            ("compile_error", r"编译失败|error:"),
            ("test_fail", r"测试失败|FAILED"),
            ("api_error", r"API 调用错误|Authentication"),
            ("timeout", r"timeout|超时"),
            ("max_iteration", r"达到最大迭代次数"),
        ]
        
        for fail_type, pattern in patterns:
            if re.search(pattern, output, re.I):
                return fail_type
        return "unknown"
    
    def _build_solve_cmd(self, problem_id: int) -> list:
        """构建解题命令"""
        # 直接使用 Python 调用，避免 just 的缓冲问题
        import sys
        python_exe = sys.executable
        cmd = [python_exe, "-m", "script.leetcode.ai.solver", str(problem_id)]
        if self.report:
            cmd.append("--report")
        if self.require_leetcode is True:
            cmd.append("--require-leetcode")
        elif self.require_leetcode is False:
            cmd.append("--no-leetcode")
        return cmd

    def _pick_problem(self) -> Optional[int]:
        """选择一个本轮尚未失败过的未解决题目。"""
        from script.leetcode.problem_pool import ProblemPool

        return ProblemPool().get_random(exclude_ids=self.failed_problem_ids)

    def _mark_problem_failed(
        self, problem_id: int, error_type: str
    ) -> tuple[bool, str]:
        self.failed_problem_ids.add(problem_id)
        self._log(
            f"⏭️ 题目 {problem_id} 本轮失败（{error_type}），后续跳过并继续下一题",
            "WARNING",
        )
        return False, error_type
    
    def run_once(self) -> tuple[bool, Optional[str]]:
        """
        运行一次 AI Solve
        
        Returns:
            (success, error_type): 是否成功，错误类型（None表示成功）
        """
        problem_id = self._pick_problem()
        if problem_id is None:
            if self.failed_problem_ids:
                self._log(
                    f"本轮剩余未解决题目都已失败并跳过（{len(self.failed_problem_ids)} 题）",
                    "WARNING",
                )
            else:
                self._log("没有未解决的题目", "SUCCESS")
            return True, "ALL_SOLVED"

        cmd = self._build_solve_cmd(problem_id)
        start_count = self._get_solved_count()
        
        for attempt in range(self.max_retries):
            self._log(
                f"开始执行题目 {problem_id}: {' '.join(cmd)} "
                f"(尝试 {attempt + 1}/{self.max_retries})"
            )
            print("-" * 60)
            self._log("⏳ 正在启动 AI 解题流程，首次启动可能需要 10-20 秒...")
            self._log("💡 提示: AI 解题平均需要 1-3 分钟，请耐心等待，不要中断")
            
            try:
                # 使用 Popen 实时输出，避免"卡住"的感觉
                # 设置 PYTHONUNBUFFERED=1 确保子进程无缓冲输出
                env = os.environ.copy()
                env['PYTHONUNBUFFERED'] = '1'
                
                process = subprocess.Popen(
                    cmd,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    text=True,
                    bufsize=1,  # 行缓冲
                    universal_newlines=True,
                    env=env
                )
                
                # 实时输出 stdout
                stdout_lines = []
                for line in process.stdout:
                    print(line, end='')
                    stdout_lines.append(line)
                
                # 获取 stderr
                stderr_output = process.stderr.read()
                if stderr_output:
                    print(stderr_output, file=sys.stderr)
                
                # 等待进程结束
                process.wait(timeout=600)
                
                print("-" * 60)
                
                # 合并输出用于分析
                stdout_output = ''.join(stdout_lines)
                
                end_count = self._get_solved_count()
                
                # 判断是否成功（通过题目数量变化 + LeetCode 验证通过）
                leetcode_passed = "LeetCode 验证通过！" in stdout_output or "LeetCode 验证通过" in stdout_output
                # 检查是否因为 LeetCode 修复次数耗尽而失败
                leetcode_fix_exhausted = "达到 LeetCode 验证失败最大修复次数" in stdout_output
                
                if end_count > start_count and leetcode_passed:
                    self._log("✅ 解题完成，新增题目", "SUCCESS")
                    return True, None
                elif end_count > start_count and leetcode_fix_exhausted:
                    # 文件创建了但 LeetCode 验证最终未能通过（已尝试修复但次数耗尽）
                    self._log("⚠️ 本地文件已生成，但 LeetCode 验证最终未能通过（已尝试多次修复）", "WARNING")
                    return self._mark_problem_failed(
                        problem_id, "leetcode_verification_failed_after_retries"
                    )
                elif end_count > start_count and not leetcode_passed:
                    # 文件创建了但 LeetCode 验证失败（可能是没有 Cookie 跳过验证）
                    self._log("⚠️ 本地文件已生成，LeetCode 验证未进行或失败", "WARNING")
                    return True, None  # 本地测试通过也算成功，LeetCode 验证是额外的
                
                # 分析失败原因
                output = stdout_output + stderr_output
                fail_type = self._analyze_failure(output)
                
                if fail_type == "no_problem":
                    self._log("🎉 所有题目都已解决！", "SUCCESS")
                    return True, "ALL_SOLVED"
                
                self._log(f"❌ 解题失败（类型: {fail_type}，返回码: {process.returncode}）", "WARNING")
                
                if attempt < self.max_retries - 1:
                    self._log(f"等待 {self.retry_delay} 秒后重试...", "INFO")
                    time.sleep(self.retry_delay)
                else:
                    return self._mark_problem_failed(problem_id, fail_type)
                    
            except subprocess.TimeoutExpired:
                process.kill()
                self._log("⏱️ 执行超时（10分钟）", "ERROR")
                if attempt < self.max_retries - 1:
                    time.sleep(self.retry_delay)
            except Exception as e:
                self._log(f"💥 异常: {e}", "ERROR")
                if attempt < self.max_retries - 1:
                    time.sleep(self.retry_delay)

        return self._mark_problem_failed(problem_id, "max_retries_exceeded")
    
    def run(self):
        """主循环"""
        solved_count_start = self._get_solved_count()
        
        self._log("=" * 60)
        self._log("🚀 启动 AI Solve 自动模式")
        self._log(f"📊 当前已解决题目: {solved_count_start}")
        self._log(f"📝 生成报告: {'是' if self.report else '否'}")
        self._log(f"🔄 最大重试: {self.max_retries} 次")
        self._log("🔁 失败策略: 单题失败后本轮跳过，继续下一题")
        self._log(f"⏸️  连续失败{self.fail_streak_limit}次后暂停: {self.fail_streak_pause} 秒")
        self._log("=" * 60)
        self._log("按 Ctrl+C 停止")
        print()
        
        try:
            while True:
                self.total_attempts += 1
                
                # 运行一次解题
                success, error = self.run_once()
                
                if error == "ALL_SOLVED":
                    break
                
                if success:
                    self.success_count += 1
                    self.success_streak += 1
                    self.fail_streak = 0
                    current_solved = self._get_solved_count()
                    self._log(f"✅ 成功！已解决题目: {current_solved}", "SUCCESS")
                else:
                    self.fail_streak += 1
                    self.success_streak = 0
                    self._log(f"❌ 失败: {error}", "ERROR")
                    
                    # 连续失败检测
                    if self.fail_streak >= self.fail_streak_limit:
                        self._log(f"连续失败 {self.fail_streak_limit} 次，暂停 {self.fail_streak_pause} 秒...", "WARNING")
                        time.sleep(self.fail_streak_pause)
                        self.fail_streak = 0
                
                # 统计信息
                elapsed = datetime.now() - self.start_time
                self._log(f"📈 统计: 尝试 {self.total_attempts} 次, 成功 {self.success_count} 次, 运行时间 {elapsed}")
                print()
                
                # 短暂休息，避免 API 限流
                time.sleep(2)
                
        except KeyboardInterrupt:
            print()
            self._log("👋 用户中断", "WARNING")
        
        # 最终统计
        self._print_final_stats(solved_count_start)
    
    def _print_final_stats(self, solved_count_start: int):
        """打印最终统计"""
        elapsed = datetime.now() - self.start_time
        final_solved = self._get_solved_count()
        
        self._log("=" * 60)
        self._log("📊 最终统计")
        self._log("=" * 60)
        self._log(f"⏱  运行时间: {elapsed}")
        self._log(f"🎯 尝试次数: {self.total_attempts}")
        self._log(f"✅ 成功次数: {self.success_count}")
        self._log(f"❌ 失败次数: {self.total_attempts - self.success_count}")
        self._log(f"⏭️  本轮跳过失败题目: {len(self.failed_problem_ids)}")
        self._log(f"📚 新增题目: {final_solved - solved_count_start}")
        self._log(f"📦 总题目数: {final_solved}")
        self._log("=" * 60)


def main():
    """主函数"""
    parser = argparse.ArgumentParser(
        description="AI 自动解题循环模式",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 基础用法（不生成报告，节省 token）
  python -m script.leetcode.ai.auto_solver
  
  # 生成解题报告（消耗更多 token）
  python -m script.leetcode.ai.auto_solver --report
  
  # 自定义重试次数和间隔
  python -m script.leetcode.ai.auto_solver --max-retries 5 --retry-delay 30
  
  # 自定义连续失败限制
  python -m script.leetcode.ai.auto_solver --fail-streak-limit 5 --fail-streak-pause 120
        """
    )
    parser.add_argument(
        "--report",
        action="store_true",
        help="生成解题报告（默认关闭以节省 token）"
    )
    parser.add_argument(
        "--max-retries",
        type=int,
        default=3,
        help="每次执行的最大重试次数（默认: 3）"
    )
    parser.add_argument(
        "--retry-delay",
        type=int,
        default=60,
        help="重试间隔秒数（默认: 60）"
    )
    parser.add_argument(
        "--fail-streak-limit",
        type=int,
        default=3,
        help="连续失败多少次后暂停（默认: 3）"
    )
    parser.add_argument(
        "--fail-streak-pause",
        type=int,
        default=60,
        help="连续失败后的暂停秒数（默认: 60）"
    )
    parser.add_argument(
        "--api-key",
        help="API Key"
    )
    parser.add_argument(
        "--base-url",
        help="API 基础 URL"
    )
    
    args = parser.parse_args()
    
    solver = AutoSolver(
        report=args.report,
        max_retries=args.max_retries,
        retry_delay=args.retry_delay,
        fail_streak_limit=args.fail_streak_limit,
        fail_streak_pause=args.fail_streak_pause,
        api_key=args.api_key,
        base_url=args.base_url,
    )
    
    try:
        solver.run()
    except KeyboardInterrupt:
        print()
        sys.exit(130)


if __name__ == "__main__":
    main()
