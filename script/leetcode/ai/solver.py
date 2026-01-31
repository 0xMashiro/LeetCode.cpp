#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
AI 解题器主类
"""

import json
import os
import traceback
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Any, List, Optional

from openai import OpenAI
from dotenv import load_dotenv

import sys

from script.leetcode.api import ProblemRepository
from script.leetcode.ai.tools import ToolDefinition, ToolExecutor
from script.leetcode.ai.prompts import get_system_prompt, get_report_generation_prompt
from script.leetcode.config import AIConfig, ProjectPaths
from script.leetcode.exceptions import ProblemNotFoundError
from script.leetcode.utils import color_text, ColorCode


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
        repository: Optional[ProblemRepository] = None
    ):
        self._load_env()
        self.api_key = api_key or self._get_api_key()
        self.base_url = base_url or self._get_base_url()
        
        self.client = OpenAI(api_key=self.api_key, base_url=self.base_url)
        self.repository = repository or ProblemRepository()
        self.tool_executor = ToolExecutor(self.repository)
        
        self.messages: List[Dict[str, Any]] = []
        self.use_reasoner = self._get_use_reasoner()
        
        # 报告收集
        self.reasoning_log: List[str] = []
        self.problem_id: Optional[int] = None
        self.problem_title: Optional[str] = None
        self.problem_slug: Optional[str] = None
        self.problem_difficulty: Optional[str] = None
        self.problem_tags: List[str] = []
        self.is_daily: bool = False
        self._current_reasoning: str = ""
    
    def _load_env(self) -> None:
        """加载环境变量"""
        project_root = Path(__file__).parent.parent.parent.parent
        env_path = project_root / ".env"
        if env_path.exists():
            load_dotenv(dotenv_path=env_path)
        else:
            load_dotenv()
    
    def _get_api_key(self) -> str:
        """获取 API Key"""
        api_key = os.getenv("MOONSHOT_API_KEY")
        if not api_key:
            raise ValueError(
                "请设置 MOONSHOT_API_KEY：\n"
                "  1. 创建 .env 文件并添加 MOONSHOT_API_KEY=your_key\n"
                "  2. 或设置环境变量: export MOONSHOT_API_KEY=your_key"
            )
        return api_key
    
    def _get_base_url(self) -> str:
        """获取 base URL"""
        return os.getenv("MOONSHOT_BASE_URL", AIConfig.DEFAULT_BASE_URL)
    
    def _get_use_reasoner(self) -> bool:
        """获取是否启用深度思考模式"""
        model = os.getenv("MOONSHOT_MODEL", AIConfig.DEFAULT_MODEL)
        if "kimi-k2.5" in model or "thinking" in model:
            return True
        return os.getenv("MOONSHOT_ENABLE_THINKING", "false").lower() == "true"
    
    @property
    def tools(self) -> List[Dict[str, Any]]:
        """获取工具定义列表"""
        return ToolDefinition.get_all()
    
    def solve_daily_challenge(self) -> None:
        """解决每日一题"""
        print(color_text("🚀 开始解决每日一题", ColorCode.CYAN.value))
        print()
        
        try:
            daily = self.repository.get_daily_challenge()
            question = daily["question"]
            problem_id = int(question["questionFrontendId"])
            
            self._solve(problem_id, question, is_daily=True)
        except Exception as e:
            print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
            traceback.print_exc()
    
    def solve_problem(self, problem_id: int) -> None:
        """解决指定题目"""
        print(color_text(f"🚀 开始解决题目: [{problem_id}]", ColorCode.CYAN.value))
        print()
        
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
            print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
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
        print(color_text(f"{title_prefix}: [{problem_id}] {question['title']}", ColorCode.BLUE.value))
        print(color_text(f"🔗 URL: https://leetcode.com/problems/{question['titleSlug']}/", ColorCode.BLUE.value))
        print()
        
        # 记录到报告
        self._log_problem_info(problem_id, question, is_daily)
        
        # 检查文件是否已存在
        if self._check_files_exist(problem_id):
            return
        
        self.reasoning_log.append("## 解题过程\n\n")
        
        # 初始化对话
        self._init_conversation(problem_id, is_daily)
        
        # 运行对话循环
        self._run_conversation_loop()
    
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
            print(color_text("✅ 题目已解决，文件已存在", ColorCode.GREEN.value))
            print(color_text(f"   头文件: {header_path}", ColorCode.CYAN.value))
            print(color_text(f"   源文件: {source_path}", ColorCode.CYAN.value))
            print(color_text(f"   测试文件: {test_path}", ColorCode.CYAN.value))
            print()
            
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
        user_message = (
            f"请帮我解决 LeetCode 每日一题：题目 ID {problem_id}" 
            if is_daily else 
            f"请帮我解决 LeetCode 题目：题目 ID {problem_id}"
        )
        
        self.messages = [
            {"role": "system", "content": self._get_system_prompt()},
            {"role": "user", "content": user_message}
        ]
        self._current_reasoning = ""
    
    def _run_conversation_loop(self) -> None:
        """运行对话循环"""
        model_name = os.getenv("MOONSHOT_MODEL", AIConfig.DEFAULT_MODEL)
        self._print_model_info(model_name)
        
        for iteration in range(AIConfig.MAX_ITERATIONS):
            print(color_text(f"💭 AI 思考中... (第 {iteration + 1} 轮)", ColorCode.YELLOW.value))
            
            try:
                message = self._call_api(model_name)
            except Exception as e:
                print(color_text(f"❌ API 调用错误: {e}", ColorCode.RED.value))
                traceback.print_exc()
                break
            
            # 保存消息
            self.messages.append(self._build_message_to_save(message))
            
            # 处理工具调用
            if message.tool_calls:
                self._handle_tool_calls(message.tool_calls)
            else:
                # 没有工具调用，解题完成
                self._print_completion(message)
                self._generate_solution_report()
                break
        else:
            print(color_text("⚠️ 达到最大迭代次数，停止处理", ColorCode.YELLOW.value))
    
    def _call_api(self, model_name: str) -> Message:
        """调用 API 并处理流式响应"""
        params = {
            "model": model_name,
            "messages": self.messages,
            "tools": self.tools,
            "stream": True
        }
        
        # 非 k2.5 模型需要额外设置
        if self.use_reasoner and "kimi-k2.5" not in model_name:
            params["extra_body"] = {"thinking": {"type": "enabled"}}
        
        stream = self.client.chat.completions.create(**params)
        
        full_reasoning = ""
        full_content = ""
        tool_calls = []
        
        if self.use_reasoner:
            print(color_text("🧠 思考过程:", ColorCode.CYAN.value), end="", flush=True)
        
        for chunk in stream:
            if not chunk.choices:
                continue
            
            delta = chunk.choices[0].delta
            
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
        
        print()
        
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
            print(color_text(f"🔧 调用工具: {tc.function_name}", ColorCode.MAGENTA.value))
            
            # 显示参数预览
            preview = tc.function_arguments[:100] + "..." if len(tc.function_arguments) > 100 else tc.function_arguments
            print(f"   参数: {preview}")
            
            try:
                # 解析参数
                args = json.loads(tc.function_arguments)
                
                # 执行工具
                result = self.tool_executor.execute(tc.function_name, args)
                
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
        print()
        print(color_text("✅ AI 完成", ColorCode.GREEN.value))
    
    def _generate_solution_report(self, is_skip: bool = False) -> None:
        """生成专业解题报告（统一格式：固定部分 + AI生成内容）"""
        if not self.problem_id:
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
                model=os.getenv("MOONSHOT_MODEL", AIConfig.DEFAULT_MODEL),
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
            print(color_text(f"🧠 使用 {model_name} 模型（思考模式）", ColorCode.CYAN.value))
        else:
            print(color_text(f"💬 使用 {model_name} 模型", ColorCode.CYAN.value))
        print()
    
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
  # 解决每日一题
  python -m script.leetcode.ai.solver
  
  # 解决指定题目
  python -m script.leetcode.ai.solver 1
  
  # 随机挑选未解决的题目（用于测试增量编译）
  python -m script.leetcode.ai.solver --random
  python -m script.leetcode.ai.solver --random --difficulty Easy
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
    
    args = parser.parse_args()
    
    try:
        solver = AISolver(
            api_key=args.api_key,
            base_url=args.base_url
        )
        
        if args.id:
            solver.solve_problem(args.id)
        elif args.random:
            # 随机模式
            from script.leetcode.problem_pool import ProblemPool
            pool = ProblemPool()
            problem_id = pool.get_random(args.difficulty)
            if problem_id:
                print(color_text(f"🎲 Randomly selected problem: {problem_id}", ColorCode.CYAN.value))
                print()
                solver.solve_problem(problem_id)
            else:
                print(color_text("No unsolved problems found", ColorCode.YELLOW.value))
        else:
            solver.solve_daily_challenge()
    except KeyboardInterrupt:
        print()
        print(color_text("操作已中断", ColorCode.YELLOW.value))
    except Exception as e:
        print(color_text(f"错误: {e}", ColorCode.RED.value))
        traceback.print_exc()


if __name__ == "__main__":
    main()
