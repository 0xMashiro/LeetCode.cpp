#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 解题器主类
"""

import json
import os
import time
import traceback
from dataclasses import dataclass, field
from datetime import datetime
from pathlib import Path
from typing import Dict, Any, List, Optional

from openai import OpenAI
from openai._types import NOT_GIVEN
from dotenv import load_dotenv

import sys

from script.leetcode.api import ProblemRepository
from script.leetcode.ai.tools import ToolDefinition, ToolExecutor
from script.leetcode.ai.prompts import get_system_prompt, get_report_generation_prompt
from script.leetcode.config import AIConfig, AIProvider, ProjectPaths
from script.leetcode.exceptions import ProblemNotFoundError
from script.leetcode.utils import color_text, ColorCode


def log_with_time(message: str, color: Optional[ColorCode] = None):
    """打印带时间戳的日志（与 auto_solver 格式统一）"""
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    if color:
        message = color_text(message, color.value)
    print(f"[{timestamp}] {message}")


@dataclass
class Message:
    """模拟 API 响应的消息对象"""
    content: str = ""
    reasoning_content: Optional[str] = None
    tool_calls: Optional[List[Dict]] = field(default_factory=list)


@dataclass 
class ToolCall:
    """工具调用信息"""
    id: str
    type: str
    function_name: str
    function_arguments: str


class AISolver:
    """AI 自动解题器"""
    
    def __init__(
        self, 
        api_key: Optional[str] = None, 
        base_url: Optional[str] = None,
        repository: Optional[ProblemRepository] = None,
        enable_report: Optional[bool] = None,
        provider: Optional[AIProvider] = None
    ):
        self._load_env()
        
        # 选择 Provider（从参数、环境变量或默认）
        self.provider = provider or AIProvider.from_env()
        
        self.api_key = api_key or self._get_api_key()
        self.base_url = base_url or self.provider.base_url
        self.enable_report = enable_report if enable_report is not None else self._get_enable_report()
        
        # 创建 OpenAI 客户端
        self.client = OpenAI(api_key=self.api_key, base_url=self.base_url)
        
        self.repository = repository or ProblemRepository()
        self.tool_executor = ToolExecutor(self.repository)
        
        self.messages: List[Dict[str, Any]] = []
        self.use_reasoner = self.provider.use_reasoner
        
        # 报告收集
        self.reasoning_log: List[str] = []
        self.problem_id: Optional[int] = None
        self.problem_title: Optional[str] = None
        self.problem_slug: Optional[str] = None
        self.problem_difficulty: Optional[str] = None
        self.problem_tags: List[str] = []
        self.is_daily: bool = False
        self._current_reasoning: str = ""
        
        # 编译错误计数（防止在编译错误上无限循环）
        self._compile_fix_count: int = 0
        # LeetCode 验证失败修复计数
        self._leetcode_fix_count: int = 0
    
    def _load_env(self) -> None:
        """加载环境变量"""
        project_root = Path(__file__).parent.parent.parent.parent
        env_path = project_root / ".env"
        if env_path.exists():
            load_dotenv(dotenv_path=env_path)
        else:
            load_dotenv()
    
    def _get_api_key(self) -> str:
        """获取 API Key（根据 Provider 自动选择环境变量名）"""
        # 根据 Provider 名称选择对应的环境变量
        env_var_map = {
            "moonshot": "MOONSHOT_API_KEY",
        }
        
        env_var = env_var_map.get(self.provider.name, f"{self.provider.name.upper()}_API_KEY")
        api_key = os.getenv(env_var)
        
        if not api_key:
            # 如果没有找到特定 Provider 的 Key，尝试通用的 AI_API_KEY
            api_key = os.getenv("AI_API_KEY")
        
        if not api_key:
            raise ValueError(
                f"请设置 {env_var}：\n"
                f"  1. 创建 .env 文件并添加 {env_var}=your_key\n"
                f"  2. 或设置环境变量: export {env_var}=your_key\n"
                f"  3. 或使用通用的 AI_API_KEY"
            )
        return api_key
    
    def _get_enable_report(self) -> bool:
        """获取是否启用解题报告生成（默认关闭以节省 token）"""
        return os.getenv("AI_SOLVER_GENERATE_REPORT", "false").lower() == "true"
    
    @property
    def tools(self) -> List[Dict[str, Any]]:
        """获取工具定义列表"""
        return ToolDefinition.get_all()
    
    def solve_daily_challenge(self) -> None:
        """解决每日一题"""
        log_with_time("🚀 开始解决每日一题", ColorCode.CYAN)
        
        try:
            daily = self.repository.get_daily_challenge()
            question = daily["question"]
            problem_id = int(question["questionFrontendId"])
            
            self._solve(problem_id, question, is_daily=True)
        except Exception as e:
            log_with_time(f"❌ 错误: {e}", ColorCode.RED)
            traceback.print_exc()
            raise  # 重新抛出异常，让外层处理
    
    def solve_problem(self, problem_id: int) -> None:
        """解决指定题目"""
        log_with_time(f"🚀 开始解决题目: [{problem_id}]", ColorCode.CYAN)
        start_time = time.time()
        
        try:
            problem_data = self.repository.get_detail_by_id(problem_id, include_code=True)
            question = {
                "title": problem_data.title,
                "titleSlug": problem_data.slug,
                "difficulty": problem_data.difficulty
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
    
    def _solve(
        self, 
        problem_id: int, 
        question: Dict[str, Any], 
        is_daily: bool = False
    ) -> None:
        """解题主流程"""
        self.problem_id = problem_id
        self.problem_title = question['title']
        self.problem_slug = question['titleSlug']
        self.problem_difficulty = question.get('difficulty', 'Unknown')
        self.problem_tags = [tag['name'] for tag in question.get('topicTags', [])]
        self.is_daily = is_daily
        
        # 打印题目信息
        title_prefix = "📋 今日题目" if is_daily else "📋 题目"
        log_with_time(f"{title_prefix}: [{problem_id}] {question['title']}", ColorCode.BLUE)
        log_with_time(f"🔗 URL: https://leetcode.com/problems/{question['titleSlug']}/", ColorCode.BLUE)
        
        # 记录到报告
        self._log_problem_info(problem_id, question, is_daily)
        
        # 检查文件是否已存在
        if self._check_files_exist(problem_id):
            return
        
        self.reasoning_log.append("## 解题过程\n\n")
        
        # 初始化对话
        self._init_conversation(problem_id, is_daily)
        
        # 运行对话循环
        solve_start = time.time()
        success = self._run_conversation_loop()
        solve_elapsed = time.time() - solve_start
        
        # 如果达到最大迭代次数仍未完成，视为失败
        if not success:
            log_with_time(f"❌ 解题失败 ({solve_elapsed:.1f}s): 达到最大迭代次数", ColorCode.RED)
            raise RuntimeError(f"解题失败：达到最大迭代次数 ({AIConfig.MAX_ITERATIONS} 轮)，未能完成题目 {problem_id}")
        
        log_with_time(f"✅ 解题流程完成，总耗时 {solve_elapsed:.1f}s", ColorCode.GREEN)
    
    def _log_problem_info(
        self, 
        problem_id: int, 
        question: Dict[str, Any], 
        is_daily: bool
    ) -> None:
        """记录题目信息到报告"""
        # 记录解题过程的起始标记
        prefix = "每日一题" if is_daily else "题目"
        self.reasoning_log.append(f"## 开始解决 {prefix} [{problem_id}] {question['title']}\n\n")
    
    def _check_files_exist(self, problem_id: int) -> bool:
        """检查文件是否已存在"""
        from script.leetcode.services import FileGenerator
        
        problem_info = self.repository.get_by_id(problem_id)
        generator = FileGenerator(problem_info)
        
        if generator.files_exist():
            header_path, source_path, test_path = generator._get_file_paths()
            log_with_time("✅ 题目已解决，文件已存在", ColorCode.GREEN)
            log_with_time(f"   头文件: {header_path}", ColorCode.CYAN)
            log_with_time(f"   源文件: {source_path}", ColorCode.CYAN)
            log_with_time(f"   测试文件: {test_path}", ColorCode.CYAN)
            
            # 记录到报告
            self.reasoning_log.append("## 状态\n\n")
            self.reasoning_log.append("✅ **题目已解决**，文件已存在，跳过自动解题。\n\n")
            self.reasoning_log.append("**已存在的文件**:\n")
            self.reasoning_log.append(f"- 头文件: `{header_path}`\n")
            self.reasoning_log.append(f"- 源文件: `{source_path}`\n")
            self.reasoning_log.append(f"- 测试文件: `{test_path}`\n\n")
            
            self._generate_solution_report(is_skip=True)
            
            # 创建跳过 PR 标记文件
            skip_pr_file = Path("SKIP_PR")
            skip_pr_file.write_text(f"题目 {problem_id} 已解决，跳过 PR 创建。\n", encoding='utf-8')
            return True
        return False
    
    def _init_conversation(self, problem_id: int, is_daily: bool) -> None:
        """初始化对话"""
        # 获取题目基本信息
        problem_data = self.repository.get_detail_by_id(problem_id, include_code=True)
        
        user_message = f"""请帮我解决 LeetCode 题目：

题目 ID: {problem_id}
标题: {problem_data.title}
难度: {problem_data.difficulty}

请使用 `fetch_problem_metadata` 工具获取题目完整信息。
获取后，请先用中文用自己的话描述题目要求（确保你真正理解了题意），然后开始解题。"""
        
        self.messages = [
            {"role": "system", "content": self._get_system_prompt()},
            {"role": "user", "content": user_message}
        ]
        self._current_reasoning = ""
        self._compile_fix_count = 0  # 重置编译错误计数
        self._leetcode_fix_count = 0  # 重置 LeetCode 修复计数
    
    def _run_conversation_loop(self) -> bool:
        """运行对话循环
        
        Returns:
            bool: 是否成功完成解题（包括本地测试通过和 LeetCode 验证通过）
        """
        model_name = self.provider.model
        self._print_model_info(model_name)
        
        for iteration in range(AIConfig.MAX_ITERATIONS):
            round_start = time.time()
            print()  # 空行分隔，提高可读性
            log_with_time(f"🔄 第 {iteration + 1} 轮对话开始", ColorCode.YELLOW)
            
            try:
                message = self._call_api(model_name)
            except Exception as e:
                log_with_time(f"❌ API 调用错误: {e}", ColorCode.RED)
                traceback.print_exc()
                return False
            
            # 保存消息
            self.messages.append(self._build_message_to_save(message))
            
            # 处理工具调用
            if message.tool_calls:
                handle_start = time.time()
                self._handle_tool_calls(message.tool_calls)
                handle_elapsed = time.time() - handle_start
                log_with_time(f"🛠️  工具执行完成 ({handle_elapsed:.1f}s)", ColorCode.CYAN)
            else:
                # 没有工具调用，表示 AI 认为解题完成
                round_elapsed = time.time() - round_start
                log_with_time(f"✅ 第 {iteration + 1} 轮完成 ({round_elapsed:.1f}s)", ColorCode.GREEN)
                self._print_completion(message)
                self._generate_solution_report()
                
                # 自动提交到 LeetCode 验证
                leetcode_success, feedback = self._submit_to_leetcode()
                
                if leetcode_success:
                    # 验证通过，解题成功
                    return True
                
                # LeetCode 验证失败，需要继续修复
                self._leetcode_fix_count += 1
                max_leetcode_fix = getattr(AIConfig, 'MAX_LEETCODE_FIX_ATTEMPTS', 3)
                
                if self._leetcode_fix_count >= max_leetcode_fix:
                    log_with_time(f"⚠️ 达到 LeetCode 验证失败最大修复次数 ({max_leetcode_fix})，停止修复", ColorCode.YELLOW)
                    return False
                
                log_with_time(f"🔧 LeetCode 验证失败，开始第 {self._leetcode_fix_count}/{max_leetcode_fix} 次修复尝试...", ColorCode.YELLOW)
                
                # 将错误反馈添加到对话，让 AI 继续修复
                self.messages.append({"role": "user", "content": feedback})
                
                # 继续下一轮对话进行修复
                continue
        
        # 达到最大迭代次数
        log_with_time("⚠️ 达到最大迭代次数，停止处理", ColorCode.YELLOW)
        return False
    
    def _call_api(self, model_name: str) -> Message:
        """调用 API 并处理流式响应"""
        start_time = time.time()
        log_with_time("⏳ 开始调用 AI API...", ColorCode.CYAN)
        
        params = {
            "model": model_name,
            "messages": self.messages,
            "tools": self.tools,
            "stream": True
        }
        
        # 非 reasoner 模型需要额外设置
        if self.use_reasoner and not self.provider.use_reasoner:
            params["extra_body"] = {"thinking": {"type": "enabled"}}
        
        stream = self.client.chat.completions.create(**params)
        
        full_reasoning = ""
        full_content = ""
        tool_calls = []
        
        first_chunk_received = False
        chunk_count = 0
        max_chunks = 100000  # 防止无限循环的安全上限
        last_chunk_time = time.time()
        stream_timeout = 60  # 60秒没有新数据则认为超时
        
        try:
            for chunk in stream:
                chunk_count += 1
                if chunk_count > max_chunks:
                    print(color_text("\n⚠️ 达到最大 chunk 数限制，强制结束流", ColorCode.YELLOW.value))
                    break
                
                current_time = time.time()
                if current_time - last_chunk_time > stream_timeout:
                    print(color_text(f"\n⚠️ 流响应超时({stream_timeout}秒无数据)，强制结束", ColorCode.YELLOW.value))
                    break
                
                if not chunk.choices:
                    continue
                
                delta = chunk.choices[0].delta
                last_chunk_time = current_time  # 更新最后收到数据的时间
                
                # 标记已收到第一个 chunk，清除等待提示
                if not first_chunk_received:
                    print("\r" + " " * 30 + "\r", end="", flush=True)
                    first_chunk_received = True
                    if self.use_reasoner:
                        print(color_text("🧠 思考过程: ", ColorCode.CYAN.value), end="", flush=True)
                
                # 处理思考内容
                if hasattr(delta, 'reasoning_content') and delta.reasoning_content:
                    full_reasoning += delta.reasoning_content
                    self._current_reasoning += delta.reasoning_content
                    print(delta.reasoning_content, end="", flush=True)
                
                # 处理内容
                if hasattr(delta, 'content') and delta.content:
                    if not full_content and self.use_reasoner and full_reasoning:
                        print()  # 思考结束换行
                    
                    if not full_content:
                        print(color_text("\n💬 回复:", ColorCode.BLUE.value), end="", flush=True)
                    
                    full_content += delta.content
                    print(delta.content, end="", flush=True)
                
                # 收集工具调用
                if hasattr(delta, 'tool_calls') and delta.tool_calls:
                    tool_calls = self._merge_tool_calls(delta.tool_calls, tool_calls)
                
                if chunk.choices[0].finish_reason:
                    break
        finally:
            # 确保 stream 被正确关闭
            try:
                stream.close()
            except Exception:
                pass
        
        if not first_chunk_received:
            print(color_text("\n⚠️ 未收到任何响应数据", ColorCode.YELLOW.value))
        
        print()
        
        # API 调用完成，记录耗时
        elapsed = time.time() - start_time
        log_with_time(f"✅ API 调用完成，耗时 {elapsed:.2f}s", ColorCode.GREEN)
        
        # 保存到日志
        if self._current_reasoning:
            self.reasoning_log.append(f"### 思考过程\n\n{self._current_reasoning}\n\n")
            self._current_reasoning = ""
        
        if full_content:
            self.reasoning_log.append(f"### AI 回复\n\n{full_content}\n\n")
        
        # 构建 ToolCall 对象列表
        converted_tool_calls = None
        if tool_calls:
            converted_tool_calls = [
                ToolCall(
                    id=tc.get("id", ""),
                    type=tc.get("type", "function"),
                    function_name=tc.get("function", {}).get("name", ""),
                    function_arguments=tc.get("function", {}).get("arguments", "")
                )
                for tc in tool_calls if tc.get("id")
            ]
        
        return Message(
            content=full_content,
            reasoning_content=full_reasoning if self.use_reasoner else None,
            tool_calls=converted_tool_calls
        )
    
    def _merge_tool_calls(
        self, 
        deltas: List[Any], 
        existing: List[Dict]
    ) -> List[Dict]:
        """合并工具调用增量"""
        result = existing.copy() if existing else []
        
        for delta in deltas:
            index = delta.index
            while len(result) <= index:
                result.append({
                    "id": "",
                    "type": "function",
                    "function": {"name": "", "arguments": ""}
                })
            
            if delta.id:
                result[index]["id"] = delta.id
            if delta.type:
                result[index]["type"] = delta.type
            if hasattr(delta, 'function'):
                if delta.function.name:
                    result[index]["function"]["name"] = delta.function.name
                if delta.function.arguments:
                    result[index]["function"]["arguments"] += delta.function.arguments
        
        return result
    
    def _build_message_to_save(self, message: Message) -> Dict[str, Any]:
        """构建要保存的消息"""
        result = {
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
                    "function": {
                        "name": tc.function_name,
                        "arguments": tc.function_arguments
                    }
                }
                for tc in message.tool_calls
            ]
        
        return result
    
    def _handle_tool_calls(self, tool_calls: List[ToolCall]) -> None:
        """处理工具调用"""
        for tc in tool_calls:
            log_with_time(f"🔧 调用工具: {tc.function_name}", ColorCode.MAGENTA)
            
            # 显示参数预览
            preview = tc.function_arguments[:100] + "..." if len(tc.function_arguments) > 100 else tc.function_arguments
            print(f"   参数: {preview}")
            
            try:
                # 解析参数
                args = json.loads(tc.function_arguments)
                
                # 执行工具（对于 compile_project 和 compile_and_test，自动传入当前 problem_id）
                if tc.function_name in ("compile_project", "compile_and_test") and self.problem_id:
                    args["problem_id"] = self.problem_id
                result = self.tool_executor.execute(tc.function_name, args)
                
                # 检测编译错误并计数
                if tc.function_name in ("compile_project", "compile_and_test"):
                    if not result.get("is_successful"):
                        self._compile_fix_count += 1
                        if self._compile_fix_count >= AIConfig.MAX_COMPILE_FIX_ATTEMPTS:
                            # 添加警告消息
                            warning_msg = f"⚠️ 警告：已连续 {self._compile_fix_count} 次编译失败。建议：\n1. 仔细检查代码结构和语法\n2. 使用 retrieve_file_content 查看完整代码\n3. 考虑简化实现或检查头文件包含"
                            print(color_text(warning_msg, ColorCode.YELLOW.value))
                    else:
                        # 编译成功，重置计数
                        self._compile_fix_count = 0
                
                # 显示结果
                self._print_tool_result(result)
                
                # 添加结果到消息
                self.messages.append({
                    "role": "tool",
                    "tool_call_id": tc.id,
                    "content": json.dumps(result, ensure_ascii=False)
                })
            except Exception as e:
                error_msg = f"工具调用异常: {str(e)}"
                print(color_text(f"   ✗ {error_msg}", ColorCode.RED.value))
                self.messages.append({
                    "role": "tool",
                    "tool_call_id": tc.id,
                    "content": json.dumps({"is_successful": False, "error_message": error_msg}, ensure_ascii=False)
                })
    
    def _print_tool_result(self, result: Dict[str, Any]) -> None:
        """打印工具调用结果"""
        if result.get("is_successful"):
            msg = result.get('status_message', '成功')
            print(color_text(f"   ✓ {msg}", ColorCode.GREEN.value))
            if "generated_files" in result:
                for file_info in result["generated_files"]:
                    print(f"      {file_info['file_category']}: {file_info['file_path']}")
        else:
            error = result.get("error_message", "未知错误")
            preview = error[:500] + "..." if len(error) > 500 else error
            print(color_text(f"   ✗ 失败: {preview}", ColorCode.RED.value))
    
    def _print_completion(self, message: Message) -> None:
        """打印完成信息（内容已在流式响应中打印，这里只打印标记）"""
        # 解题成功，无需额外输出（文件生成和测试通过的信息已在前面显示）
        pass
    
    def _generate_solution_report(self, is_skip: bool = False) -> None:
        """生成专业解题报告（统一格式：固定部分 + AI生成内容）"""
        if not self.problem_id:
            return
        
        # 检查是否启用报告生成（默认关闭以节省 token）
        if not self.enable_report:
            return
        
        print()
        print(color_text("📝 正在生成专业解题报告...", ColorCode.CYAN.value))
        
        # 生成固定的报告头部
        header = self._build_report_header()
        
        # 生成中间内容（AI博客 或 跳过提示）
        if is_skip:
            content = "## 状态\n\n✅ **题目已解决**，文件已存在，跳过自动解题。\n"
        else:
            content = self._generate_blog_content()
        
        # 生成固定的报告尾部（文件变更表格）
        footer = self._build_report_footer()
        
        # 组合完整报告
        report_content = f"{header}\n{content}\n{footer}"
        
        report_path = Path(f"SOLUTION_REPORT_{self.problem_id}.md")
        report_path.write_text(report_content, encoding='utf-8')
        
        print(color_text(f"✅ 解题报告已保存: {report_path}", ColorCode.GREEN.value))
    
    def _build_report_header(self) -> str:
        """构建报告头部（固定格式）"""
        difficulty = self.problem_difficulty or "Unknown"
        tags_str = ", ".join(self.problem_tags) if self.problem_tags else "暂无"
        
        header_path = f"include/leetcode/problems/{self.problem_slug}.h"
        source_path = f"src/leetcode/problems/{self.problem_slug}.cpp"
        test_path = f"test/leetcode/problems/{self.problem_slug}.cpp"
        
        return f"""# LeetCode {self.problem_id}. {self.problem_title}

## 题目信息

| 属性 | 内容 |
|------|------|
| **题目链接** | https://leetcode.com/problems/{self.problem_slug}/ |
| **难度** | {difficulty} |
| **标签** | {tags_str} |

## 文件位置

- 头文件：`{header_path}`
- 源文件：`{source_path}`
- 测试文件：`{test_path}`

---

"""
    
    def _generate_blog_content(self) -> str:
        """使用 AI 生成技术博客内容（Karpathy 风格）"""
        history = "\n".join(self.reasoning_log)
        
        # User Prompt 只提供原材料，所有风格/结构指令在 System Prompt 中
        user_prompt = f"""这是这道题的完整解题历史记录（包含题目描述、代码片段和思考过程）：

{history}

请基于上述材料，按照 System Prompt 中的要求，写出那篇技术博客。直接开始写正文，不要有任何开场白。"""
        
        try:
            response = self.client.chat.completions.create(
                model=self.provider.model,
                messages=[
                    {"role": "system", "content": get_report_generation_prompt()},
                    {"role": "user", "content": user_prompt}
                ],
                stream=False
            )
            
            return response.choices[0].message.content
            
        except Exception as e:
            print(color_text(f"⚠️ AI 博客生成失败: {e}，使用基础描述", ColorCode.YELLOW.value))
            return "## 解题思路\n\n（详细的解题思路请参考源代码和测试用例中的注释）\n"
    
    def _build_report_footer(self) -> str:
        """构建报告尾部"""
        return """---

*本报告由 AI 自动生成。*
"""
    
    def _print_model_info(self, model_name: str) -> None:
        """打印模型信息"""
        if self.use_reasoner:
            log_with_time(f"🧠 使用 {model_name} 模型（思考模式）", ColorCode.CYAN)
        else:
            log_with_time(f"💬 使用 {model_name} 模型", ColorCode.CYAN)
    
    def _submit_to_leetcode(self) -> tuple[bool, Optional[str]]:
        """本地测试通过后，提交到 LeetCode 验证
        
        Returns:
            tuple[bool, Optional[str]]: (是否通过验证, 错误反馈信息用于AI修复)
            - 通过验证: (True, None)
            - 未通过验证: (False, 错误反馈信息)
            - 无 Cookie 跳过验证: (True, None)
        """
        if not self.problem_id:
            return False, "无法获取题目 ID"
        
        # 检查是否有 LEETCODE_COOKIE
        if not os.getenv("LEETCODE_COOKIE"):
            print()
            print(color_text("💡 提示: 设置 LEETCODE_COOKIE 后可自动提交到 LeetCode 验证", ColorCode.CYAN.value))
            return True, None  # 返回 True 表示本地已通过
        
        print()
        log_with_time("🌐 正在提交到 LeetCode 验证...", ColorCode.CYAN)
        
        try:
            # 导入提交模块
            from script.leetcode.submit import LeetCodeSubmitter
            
            submitter = LeetCodeSubmitter()
            # 提交并获取详细结果
            result = submitter.submit_problem_with_result(self.problem_id, solution_num=1)
            
            if result.status == "Accepted":
                log_with_time("✅ LeetCode 验证通过！", ColorCode.GREEN)
                return True, None
            
            # 构建错误反馈信息用于 AI 修复
            feedback = self._build_leetcode_error_feedback(result)
            return False, feedback
                
        except Exception as e:
            error_msg = f"提交到 LeetCode 时出错: {e}"
            log_with_time(f"⚠️  {error_msg}", ColorCode.YELLOW)
            return False, error_msg
    
    def _build_leetcode_error_feedback(self, result) -> str:
        """根据 LeetCode 返回结果构建 AI 修复提示"""
        from script.leetcode.submit import SubmissionResult
        
        lines = ["LeetCode 提交失败，需要修复。", ""]
        
        if result.status == "Wrong Answer":
            lines.append(f"❌ Wrong Answer (通过了 {result.passed_test_cases}/{result.total_test_cases} 个测试用例)")
            lines.append("")
            if result.failed_test_case:
                failed = result.failed_test_case
                lines.append("失败的测试用例:")
                lines.append(f"- 输入: {failed.get('input', 'N/A')}")
                lines.append(f"- 输出: {failed.get('actual', 'N/A')}")
                lines.append(f"- 期望: {failed.get('expected', 'N/A')}")
                lines.append("")
                lines.append("请按以下步骤修复：")
                lines.append("")
                lines.append("**步骤 1: 添加失败的测试用例到本地**")
                lines.append("使用 `append_test_case` 工具将此测试用例添加到本地测试文件。")
                lines.append("test_name 建议使用描述性名称如 'WrongAnswerCase1' 或 'EdgeCaseEmptyArray'")
                lines.append("test_code 格式示例（注意缩进为2个空格）：")
                lines.append("```")
                lines.append("  // 输入: nums = [1,2,3], target = 4")
                lines.append("  // 期望: [0,1]")
                lines.append("  vector<int> nums = {{1, 2, 3}};")
                lines.append("  int target = 4;")
                lines.append("  vector<int> expected = {{0, 1}};")
                lines.append("  vector<int> result = solution.twoSum(nums, target);")
                lines.append("  EXPECT_EQ(expected, result);")
                lines.append("```")
                lines.append("")
                lines.append("**步骤 2: 分析并修复代码**")
                lines.append("使用 `retrieve_file_content` 查看当前代码，分析失败原因，")
                lines.append("然后使用 `create_or_update_file` 修复源文件中的问题。")
                lines.append("")
                lines.append("**步骤 3: 验证修复**")
                lines.append("调用 `compile_and_test` 确保修复后的代码通过所有测试。")
                
        elif result.status == "Runtime Error":
            lines.append(f"💥 Runtime Error")
            if result.error_message:
                lines.append(f"错误信息: {result.error_message}")
            lines.append("")
            lines.append("请分析错误原因（数组越界？空指针？除以零？），然后：")
            lines.append("1. 使用 `retrieve_file_content` 查看代码")
            lines.append("2. 修复问题并使用 `create_or_update_file` 更新代码")
            lines.append("3. 调用 `compile_and_test` 验证修复")
            
        elif result.status == "Time Limit Exceeded":
            lines.append("⏱️ Time Limit Exceeded")
            lines.append("")
            lines.append("算法时间复杂度过高，请考虑：")
            lines.append("1. 优化算法（例如使用更高效的数据结构）")
            lines.append("2. 减少冗余计算")
            lines.append("3. 使用 `retrieve_file_content` 查看当前实现并改进")
            
        elif result.status == "Compile Error":
            lines.append("❌ Compile Error")
            if result.error_message:
                lines.append(f"编译错误信息: {result.error_message}")
            lines.append("")
            lines.append("请检查代码语法并修复编译错误。")
            
        else:
            lines.append(f"❌ {result.status}")
            if result.error_message:
                lines.append(f"错误信息: {result.error_message}")
        
        lines.append("")
        lines.append("请开始修复。")
        
        return "\n".join(lines)
    
    @staticmethod
    def _get_system_prompt() -> str:
        """获取系统提示词"""
        return get_system_prompt()


def main():
    """主函数"""
    import argparse
    
    parser = argparse.ArgumentParser(
        description="AI 自动解决 LeetCode 题目",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 解决每日一题（默认 moonshot，不生成报告）
  python -m script.leetcode.ai.solver
  
  # 解决指定题目
  python -m script.leetcode.ai.solver 1
  
  # 生成解题报告（CI 使用）
  python -m script.leetcode.ai.solver --report
  python -m script.leetcode.ai.solver 1 --report
  
  # 随机挑选未解决的题目（用于测试增量编译）
  python -m script.leetcode.ai.solver --random
  python -m script.leetcode.ai.solver --random --difficulty Easy
  
  # 自动循环模式（持续解决未完成的题目）
  python -m script.leetcode.ai.solver --auto
  python -m script.leetcode.ai.solver --auto --report
        """
    )
    parser.add_argument(
        "id",
        nargs="?",
        type=int,
        help="指定要解决的题目 ID"
    )
    parser.add_argument(
        "--random",
        action="store_true",
        help="随机挑选未解决的题目"
    )
    parser.add_argument(
        "--auto",
        action="store_true",
        help="自动循环模式：持续解决未完成的题目，直到全部完成"
    )
    parser.add_argument(
        "--difficulty",
        choices=["Easy", "Medium", "Hard"],
        help="配合 --random 使用，指定难度"
    )
    parser.add_argument(
        "--api-key",
        help="Moonshot API Key"
    )
    parser.add_argument(
        "--base-url",
        help="API 基础 URL"
    )
    parser.add_argument(
        "--report",
        action="store_true",
        help="生成解题报告（默认关闭以节省 token，CI 可开启）"
    )
    parser.add_argument(
        "--max-retries",
        type=int,
        default=3,
        help="自动模式下每次执行的最大重试次数（默认: 3）"
    )
    parser.add_argument(
        "--retry-delay",
        type=int,
        default=60,
        help="自动模式下重试间隔秒数（默认: 60）"
    )
    parser.add_argument(
        "--fail-streak-limit",
        type=int,
        default=3,
        help="自动模式下连续失败多少次后暂停（默认: 3）"
    )
    parser.add_argument(
        "--fail-streak-pause",
        type=int,
        default=60,
        help="自动模式下连续失败后的暂停秒数（默认: 60）"
    )
    args = parser.parse_args()
    
    # 自动模式
    if args.auto:
        from script.leetcode.ai.auto_solver import AutoSolver
        auto_solver = AutoSolver(
            report=args.report,
            max_retries=args.max_retries,
            retry_delay=args.retry_delay,
            fail_streak_limit=args.fail_streak_limit,
            fail_streak_pause=args.fail_streak_pause,
            api_key=args.api_key,
            base_url=args.base_url,
        )
        try:
            auto_solver.run()
        except KeyboardInterrupt:
            print()
            print(color_text("操作已中断", ColorCode.YELLOW.value))
            sys.exit(130)
        return
    
    try:
        solver = AISolver(
            api_key=args.api_key,
            base_url=args.base_url,
            enable_report=args.report
        )
        
        if args.id:
            solver.solve_problem(args.id)
        elif args.random:
            # 随机模式
            from script.leetcode.problem_pool import ProblemPool
            pool = ProblemPool()
            problem_id = pool.get_random(args.difficulty)
            if problem_id:
                log_with_time(f"🎲 Randomly selected problem: {problem_id}", ColorCode.CYAN)
                solver.solve_problem(problem_id)
            else:
                log_with_time("No unsolved problems found", ColorCode.YELLOW)
        else:
            solver.solve_daily_challenge()
    except KeyboardInterrupt:
        print()
        log_with_time("操作已中断", ColorCode.YELLOW)
        sys.exit(130)  # 130 是 Ctrl+C 的标准退出码
    except Exception as e:
        print(color_text(f"错误: {e}", ColorCode.RED.value))
        traceback.print_exc()
        sys.exit(1)


if __name__ == "__main__":
    main()
