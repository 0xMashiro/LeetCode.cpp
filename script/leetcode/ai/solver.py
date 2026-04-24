#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""AI 解题器主类。"""

import os
import sys
import time
import traceback
from pathlib import Path
from typing import Any, Dict, List, Optional

from dotenv import load_dotenv

from script.leetcode.ai.api_client import AIApiClient
from script.leetcode.ai.guard import GuardState, should_abort
from script.leetcode.ai.journal import SolveJournal
from script.leetcode.ai.messages import Message, ToolCall
from script.leetcode.ai.prompts import SYSTEM_PROMPT
from script.leetcode.ai.report_generator import ReportGenerator
from script.leetcode.ai.scaffold import ScaffoldManager
from script.leetcode.ai.tool_round import ToolRoundProcessor, should_short_circuit
from script.leetcode.ai.tools import ToolDefinition, ToolExecutor
from script.leetcode.submit import feedback as leetcode_feedback
from script.leetcode.submit.classifier import SubmissionClassifier
from script.leetcode.api import ProblemRepository
from script.leetcode.config import AIConfig, AIProvider
from script.leetcode.exceptions import ProblemNotFoundError, StreamResponseError
from script.leetcode.utils import ColorCode, color_text, log_with_time


SKIP_PR_MARKER_PATH = Path("SKIP_PR")


class AISolver:
    def __init__(
        self,
        api_key: Optional[str] = None,
        base_url: Optional[str] = None,
        repository: Optional[ProblemRepository] = None,
        enable_report: Optional[bool] = None,
        provider: Optional[AIProvider] = None,
        scaffold_mode: bool = False,
        force_new_solution: Optional[bool] = None,
        require_leetcode: Optional[bool] = None,
        verify_all_strategies: Optional[bool] = None,
    ):
        self._load_env()

        self.provider = provider or AIProvider.from_env()
        self.api_key = api_key or self._require_api_key()
        self.base_url = base_url or self.provider.base_url

        self.enable_report = self._resolve_bool_flag(
            enable_report, "AI_SOLVER_GENERATE_REPORT", default=False
        )
        self.scaffold_mode = scaffold_mode
        self.force_new_solution = self._resolve_bool_flag(
            force_new_solution, "AI_SOLVER_FORCE_NEW_SOLUTION", default=False
        )
        # 默认 True：本地测试可能不全，LeetCode 判题才是可信信号
        self.require_leetcode = self._resolve_bool_flag(
            require_leetcode, "LEETCODE_SUBMIT_ENABLED", default=True
        )
        # 默认 False：多解验证把 LeetCode 提交次数 ×N，可能顶上限流。想验再开。
        self.verify_all_strategies = self._resolve_bool_flag(
            verify_all_strategies, "AI_SOLVER_VERIFY_ALL_STRATEGIES", default=False
        )

        self._api_client = AIApiClient(self.provider, self.api_key, self.base_url)
        self.repository = repository or ProblemRepository()
        self.tool_executor = ToolExecutor(self.repository)
        self.submission_classifier = SubmissionClassifier()
        self._report_generator = ReportGenerator(self._api_client.client, self.provider)
        self._journal = SolveJournal(self.provider)
        self._scaffold = ScaffoldManager(
            self.repository, self._api_client.client, self.provider
        )
        self._tool_round = ToolRoundProcessor(self.tool_executor)

        self.messages: List[Dict[str, Any]] = []
        self.use_reasoner = self.provider.use_reasoner

        self.reasoning_log: List[str] = []
        self.problem_id: Optional[int] = None
        self.problem_title: Optional[str] = None
        self.problem_slug: Optional[str] = None
        self.problem_difficulty: Optional[str] = None
        self.problem_tags: List[str] = []
        self.is_daily: bool = False

        self._leetcode_fix_count: int = 0
        self._guard = GuardState()

    @staticmethod
    def _resolve_bool_flag(
        explicit: Optional[bool], env_var: str, *, default: bool
    ) -> bool:
        """三级兜底：显式参数 → env → default。env 为空字符串按未设置处理。"""
        if explicit is not None:
            return explicit
        raw = os.getenv(env_var)
        if raw is None or raw == "":
            return default
        return raw.lower() == "true"

    def _should_skip_as_already_solved(self, problem_id: int) -> bool:
        if self.force_new_solution:
            return False
        return self._scaffold.has_solution(problem_id)

    def _load_env(self) -> None:
        project_root = Path(__file__).parent.parent.parent.parent
        env_path = project_root / ".env"
        if env_path.exists():
            load_dotenv(dotenv_path=env_path)
        else:
            load_dotenv()

    def _require_api_key(self) -> str:
        env_var = self.provider.api_key_env()
        api_key = os.getenv(env_var) or os.getenv("AI_API_KEY")
        if not api_key:
            raise ValueError(
                f"请设置 {env_var}：\n"
                f"  1. 创建 .env 文件并添加 {env_var}=your_key\n"
                f"  2. 或设置环境变量: export {env_var}=your_key\n"
                f"  3. 或使用通用的 AI_API_KEY"
            )
        return api_key

    @property
    def tools(self) -> List[Dict[str, Any]]:
        return ToolDefinition.get_all()


    def solve_daily_challenge(self) -> None:
        """解决每日一题"""
        log_with_time("🚀 开始解决每日一题", ColorCode.CYAN)
        
        try:
            daily = self.repository.get_daily_challenge()
            question = daily["question"]
            problem_id = int(question["questionFrontendId"])
            
            # 检查每日一题是否支持 C++
            slug = question.get("titleSlug")
            if slug:
                from script.leetcode.problem_pool import ProblemPool
                pool = ProblemPool()
                if not pool._has_cpp_support(slug):
                    log_with_time(f"⚠️ 今日每日一题 [{problem_id}] {question.get('title', '')} 不支持 C++，跳过", ColorCode.YELLOW)
                    self._write_skip_marker(problem_id, "每日一题不支持 C++")
                    return
            
            self._solve(problem_id, question, is_daily=True)
        except Exception as e:
            log_with_time(f"❌ 错误: {e}", ColorCode.RED)
            traceback.print_exc()
            raise

    def solve_problem(self, problem_id: int) -> None:
        log_with_time(f"🚀 开始解决题目: [{problem_id}]", ColorCode.CYAN)
        start_time = time.time()

        try:
            problem_data = self.repository.get_detail_by_id(problem_id, include_code=True)
            question = {
                "title": problem_data.title,
                "titleSlug": problem_data.slug,
                "difficulty": problem_data.difficulty,
                "topicTags": problem_data.topic_tags or [],
            }

            self._solve(problem_id, question, is_daily=False)
        except ProblemNotFoundError:
            print(color_text(f"❌ 题目 {problem_id} 不存在", ColorCode.RED.value))
            print()
            print(color_text("可能的原因:", ColorCode.YELLOW.value))
            print("  • 题目 ID 输入错误")
            print("  • 该题目是 LeetCode Premium 付费题目，无法通过 API 获取")
            print("  • 题目已被删除或下架")
            print()
            print(color_text("建议:", ColorCode.CYAN.value))
            print("  • 请确认题目 ID 正确")
            print("  • 如果是付费题目，请手动添加到项目中")
            sys.exit(1)
        except Exception as e:
            elapsed = time.time() - start_time
            log_with_time(f"❌ 错误 ({elapsed:.1f}s): {e}", ColorCode.RED)
            traceback.print_exc()
            raise
    
    def _solve(
        self,
        problem_id: int,
        question: Dict[str, Any],
        is_daily: bool = False,
    ) -> None:
        self.problem_id = problem_id
        self.problem_title = question['title']
        self.problem_slug = question['titleSlug']
        self.problem_difficulty = question.get('difficulty', 'Unknown')
        self.problem_tags = [tag['name'] for tag in question.get('topicTags', [])]
        self.is_daily = is_daily

        title_prefix = "📋 今日题目" if is_daily else "📋 题目"
        log_with_time(f"{title_prefix}: [{problem_id}] {question['title']}", ColorCode.BLUE)
        log_with_time(f"🔗 URL: https://leetcode.com/problems/{question['titleSlug']}/", ColorCode.BLUE)

        prefix = "每日一题" if is_daily else "题目"
        self.reasoning_log.append(f"## 开始解决 {prefix} [{problem_id}] {question['title']}\n\n")

        if self._should_skip_as_already_solved(problem_id):
            self._report_already_solved(problem_id)
            return
        if self._scaffold.has_solution(problem_id):
            log_with_time(
                "♻️ AI_SOLVER_FORCE_NEW_SOLUTION=true，删除旧文件后强制重新解题",
                ColorCode.CYAN,
            )
            self._scaffold.cleanup_files(problem_id)

        if self.scaffold_mode:
            self._scaffold.prepare(problem_id)

        self.reasoning_log.append("## 解题过程\n\n")

        self._init_conversation(problem_id, is_daily)

        solve_start = time.time()
        success = self._run_conversation_loop()
        solve_elapsed = time.time() - solve_start
        self._journal.set_solve_time(solve_elapsed)
        self._journal.set_success(success)

        if not success:
            reason = self._journal.failure_reason or "达到最大迭代次数"
            log_with_time(f"❌ 解题失败 ({solve_elapsed:.1f}s): {reason}", ColorCode.RED)
            self._journal.emit_summary()
            self._journal.persist_if_enabled(self.problem_id)
            self._scaffold.cleanup_files(problem_id)
            raise RuntimeError(f"解题失败（{reason}），未能完成题目 {problem_id}")

        log_with_time(f"✅ 解题流程完成，总耗时 {solve_elapsed:.1f}s", ColorCode.GREEN)
        self._journal.emit_summary()
        self._journal.persist_if_enabled(self.problem_id)
    
    def _report_already_solved(self, problem_id: int) -> None:
        from script.leetcode.services import FileGenerator
        problem_info = self.repository.get_by_id(problem_id)
        header_path, source_path, test_path = FileGenerator(problem_info)._get_file_paths()

        log_with_time("✅ 题目已解决，文件已存在", ColorCode.GREEN)
        log_with_time(f"   头文件: {header_path}", ColorCode.CYAN)
        log_with_time(f"   源文件: {source_path}", ColorCode.CYAN)
        log_with_time(f"   测试文件: {test_path}", ColorCode.CYAN)

        self.reasoning_log.append("## 状态\n\n")
        self.reasoning_log.append("✅ **题目已解决**，文件已存在，跳过自动解题。\n\n")
        self.reasoning_log.append("**已存在的文件**:\n")
        self.reasoning_log.append(f"- 头文件: `{header_path}`\n")
        self.reasoning_log.append(f"- 源文件: `{source_path}`\n")
        self.reasoning_log.append(f"- 测试文件: `{test_path}`\n\n")

        self._write_report(is_skip=True)
        SKIP_PR_MARKER_PATH.write_text(
            f"题目 {problem_id} 已解决，跳过 PR 创建。\n", encoding="utf-8"
        )

    def _init_conversation(self, problem_id: int, is_daily: bool) -> None:
        problem_data = self.repository.get_detail_by_id(problem_id, include_code=True)

        if self.scaffold_mode:
            user_message = self._scaffold.user_message_preamble(problem_id, problem_data)
        else:
            tags_line = (
                f"官方分类标签: {', '.join(self.problem_tags)}"
                if self.problem_tags else "官方分类标签: （未知）"
            )
            user_message = f"""请帮我解决 LeetCode 题目：

题目 ID: {problem_id}
标题: {problem_data.title}
难度: {problem_data.difficulty}
{tags_line}

请使用 `fetch_problem_metadata` 工具获取题目完整信息。
获取后按阶段 0（算法范式选型）+ 阶段 1（复述题意）要求输出，再开始写代码。"""

        self.messages = [
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": user_message}
        ]
        self._tool_round.reset()
        self._leetcode_fix_count = 0

    def _run_conversation_loop(self) -> bool:
        """主对话循环。返回 True 代表本地 + LeetCode 全过；False 代表守卫/API 失败或超轮。"""
        self._announce_model()

        for iteration in range(AIConfig.MAX_ITERATIONS):
            self._journal.set_round(iteration)
            self._announce_round(iteration)
            round_start = time.time()

            message = self._safe_api_call()
            if message is None:
                return False

            self.messages.append(self._assistant_message(message))

            if message.tool_calls:
                ok, tool_summary = self._process_tool_round(message.tool_calls)
                if not ok:
                    return False
                # compile_and_test 刚过 → 直接走完成路径，省下一轮"模型说完成"的空转
                if should_short_circuit(tool_summary):
                    log_with_time(
                        "⚡ compile_and_test 已通过，跳过下一轮 API 调用直接走完成流程",
                        ColorCode.CYAN,
                    )
                    outcome = self._handle_completion(iteration, round_start)
                    if outcome is True:
                        return True
                    if outcome is False:
                        return False
                continue

            if not (message.content or message.reasoning_content):
                self._journal.record_failure(
                    "empty_response_no_tool_calls",
                    message="❌ 模型返回空响应且无工具调用，视为失败",
                )
                return False

            outcome = self._handle_completion(iteration, round_start)
            if outcome is True:
                return True
            if outcome is False:
                return False

        log_with_time("⚠️ 达到最大迭代次数，停止处理", ColorCode.YELLOW)
        self._journal.set_failure_reason("max_iterations_exceeded")
        return False

    def _announce_model(self) -> None:
        think_label = "思考模式 ON" if self.use_reasoner else "思考模式 OFF"
        log_with_time(
            f"🤖 Provider: {self.provider.name} | 模型: {self.provider.model} | {think_label}",
            ColorCode.CYAN,
        )

    @staticmethod
    def _announce_round(iteration: int) -> None:
        print()
        log_with_time(f"🔄 第 {iteration + 1} 轮对话开始", ColorCode.YELLOW)

    def _safe_api_call(self) -> Optional[Message]:
        try:
            message = self._api_client.call(
                self.messages, self.tools,
                journal=self._journal,
                reasoning_log_collector=self,
            )
        except StreamResponseError as e:
            # 流超时 / 空响应：显式区分于"模型主动完成"，避免误判成功
            self._journal.increment_api_call()
            self._journal.record_failure(
                f"stream_error:{e.reason}",
                message=f"❌ 流响应异常: {e.reason}",
            )
            return None
        except Exception as e:
            self._journal.record_failure(
                f"api_error:{e}",
                exc=e,
                message=f"❌ API 调用错误: {e}",
            )
            return None

        self._journal.increment_api_call()
        return message

    def _process_tool_round(
        self, tool_calls: List[ToolCall]
    ) -> tuple[bool, Dict[str, Any]]:
        handle_start = time.time()
        tool_summary = self._tool_round.run(
            tool_calls,
            problem_id=self.problem_id or 0,
            messages=self.messages,
        )
        log_with_time(f"🛠️  工具执行完成 ({time.time() - handle_start:.1f}s)", ColorCode.CYAN)

        if should_abort(tool_summary, self._guard):
            self._journal.set_failure_reason("guard_terminated")
            return False, tool_summary
        return True, tool_summary

    def _handle_completion(self, iteration: int, round_start: float) -> Optional[bool]:
        """True=通过；False=放弃；None=可重试（fix 提示已写入 messages）。"""
        if self.scaffold_mode and self.problem_id and self._scaffold.still_dirty(self.problem_id):
            log_with_time(
                "⚠️ 模型声称完成但 scaffold 里官方 TEST_P 仍未填充，强制回炉",
                ColorCode.YELLOW,
            )
            self.messages.append({
                "role": "user",
                "content": (
                    "检测到你还没有调用 create_or_update_file 去填充 test 文件里的 "
                    "OfficialExampleN TEST_P（它们的 body 依然是注入 scaffold 时的 TODO 注释）。"
                    "不要只用文字讨论，也不要直接给结论：必须用 create_or_update_file 提交新的 test 文件，"
                    "把每个 OfficialExampleN 都填上用注释里 Input 构造的变量 + Output 作为 expected 的 "
                    "EXPECT_EQ / EXPECT_NEAR 断言。现在就提交。"
                ),
            })
            return None

        round_elapsed = time.time() - round_start
        log_with_time(f"✅ 第 {iteration + 1} 轮完成 ({round_elapsed:.1f}s)", ColorCode.GREEN)
        self._write_report()

        if not self.require_leetcode:
            log_with_time(
                "⏭️  require_leetcode=False，跳过 LeetCode 判题（本地测试通过即视为完成）",
                ColorCode.CYAN,
            )
            self._journal.set_leetcode_passed(None)
            self._journal.set_skip_reason("local_only")
            return True

        should_continue, accepted, feedback, skip_reason = self._submit_to_leetcode()
        self._journal.set_leetcode_passed(accepted)
        self._journal.set_skip_reason(skip_reason)

        if should_continue:
            return True

        self._leetcode_fix_count += 1
        if self._leetcode_fix_count >= AIConfig.MAX_LEETCODE_FIX_ATTEMPTS:
            log_with_time(
                f"⚠️ 达到 LeetCode 验证失败最大修复次数 ({AIConfig.MAX_LEETCODE_FIX_ATTEMPTS})，停止修复",
                ColorCode.YELLOW,
            )
            self._journal.set_failure_reason("leetcode_fix_exhausted")
            return False

        log_with_time(
            f"🔧 LeetCode 验证失败，开始第 {self._leetcode_fix_count}/{AIConfig.MAX_LEETCODE_FIX_ATTEMPTS} 次修复尝试...",
            ColorCode.YELLOW,
        )
        self.messages.append({"role": "user", "content": feedback})
        return None
    
    def record(self, reasoning: str, content: str) -> None:
        """AIApiClient 流结束时回写本轮思考 + 回复到 reasoning_log。"""
        if reasoning:
            self.reasoning_log.append(f"### 思考过程\n\n{reasoning}\n\n")
        if content:
            self.reasoning_log.append(f"### AI 回复\n\n{content}\n\n")

    def _assistant_message(self, message: Message) -> Dict[str, Any]:
        result: Dict[str, Any] = {
            "role": "assistant",
            "content": message.content or "",
        }
        if self.use_reasoner and message.reasoning_content:
            result["reasoning_content"] = message.reasoning_content
        if message.tool_calls:
            result["tool_calls"] = [
                {
                    "id": tc.id,
                    "type": tc.type,
                    "function": {"name": tc.function_name, "arguments": tc.function_arguments},
                }
                for tc in message.tool_calls
            ]
        return result

    def _write_skip_marker(self, problem_id: int, reason: str) -> None:
        SKIP_PR_MARKER_PATH.write_text(
            f"题目 {problem_id} - {reason}\n", encoding="utf-8"
        )
        log_with_time(f"📝 已创建跳过标记: {reason}", ColorCode.CYAN)

    def _write_report(self, is_skip: bool = False) -> None:
        if not self.problem_id or not self.enable_report:
            return
        self._report_generator.generate(
            problem_id=self.problem_id,
            problem_title=self.problem_title or "",
            problem_slug=self.problem_slug or "",
            problem_difficulty=self.problem_difficulty or "Unknown",
            problem_tags=self.problem_tags,
            reasoning_log=self.reasoning_log,
            is_skip=is_skip,
        )

    def _submit_to_leetcode(
        self,
    ) -> tuple[bool, Optional[bool], Optional[str], Optional[str]]:
        """返回 (should_continue, accepted, feedback, skip_reason)。"""
        if self.verify_all_strategies:
            outcome = self.submission_classifier.submit_all_and_classify(self.problem_id)
        else:
            outcome = self.submission_classifier.submit_and_classify(self.problem_id)
        if outcome.should_continue:
            return True, outcome.accepted, None, outcome.skip_reason
        if outcome.error_message:
            return False, outcome.accepted, outcome.error_message, outcome.skip_reason
        if outcome.result is not None:
            feedback = leetcode_feedback.build(
                outcome.result,
                self_authored_tests_locally_passed=self._has_self_authored_tests(),
            )
            return False, outcome.accepted, feedback, outcome.skip_reason
        return False, outcome.accepted, "LeetCode 提交失败", outcome.skip_reason

    def _has_self_authored_tests(self) -> bool:
        """test 文件里是否有 SelfAuthored 前缀的 TEST_P（走到这里本地已全绿）。"""
        if not self.problem_id:
            return False
        from script.leetcode.services import FileGenerator
        try:
            problem_info = self.repository.get_by_id(self.problem_id)
            _, _, test_path = FileGenerator(problem_info)._get_file_paths()
            return "SelfAuthored" in test_path.read_text(encoding="utf-8")
        except Exception:
            return False


if __name__ == "__main__":
    from script.leetcode.ai.cli import main

    main()
