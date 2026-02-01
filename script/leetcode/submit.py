#!/usr/bin/env python3
"""
LeetCode 代码提交工具
使用 AI 将本地代码转换为 LeetCode 格式并提交验证
"""

import argparse
import os
import sys
import time
import json
import urllib.request
from pathlib import Path
from typing import Optional, Dict, Any
from dataclasses import dataclass

from script.leetcode.api.repository import ProblemRepository
from script.leetcode.models import ProblemData
from script.leetcode.utils import color_text, ColorCode
from script.leetcode.config import AIProvider
from openai import OpenAI
from dotenv import load_dotenv


@dataclass
class SubmissionResult:
    """提交结果"""
    status: str  # "Accepted", "Wrong Answer", "Runtime Error", etc.
    status_code: int
    total_test_cases: int = 0
    passed_test_cases: int = 0
    failed_test_case: Optional[Dict] = None
    runtime_ms: Optional[float] = None
    memory_mb: Optional[float] = None
    error_message: Optional[str] = None


class LeetCodeSubmitter:
    """LeetCode 代码提交器"""
    
    def __init__(self):
        # 加载 .env 文件
        load_dotenv()
        
        self.repo = ProblemRepository()
        self.cookie = os.getenv("LEETCODE_COOKIE")
        self.csrf_token = self._extract_csrf_token() if self.cookie else None
        
        # 初始化 AI 客户端
        self._init_ai_client()
        
        if not self.cookie:
            print(color_text("⚠️  未设置 LEETCODE_COOKIE 环境变量", ColorCode.YELLOW.value))
            print("提交功能需要 Cookie，但转换功能可用\n")
            self.cookie_valid = False
        else:
            # 验证 Cookie 有效性（验证失败不阻止提交，让提交来验证）
            self.cookie_valid = self._validate_cookie()
            if not self.cookie_valid:
                print(color_text("⚠️  Cookie 验证失败，但仍将尝试提交", ColorCode.YELLOW.value))
                print("如果提交失败，请检查网络连接或重新登录 LeetCode\n")
                # 验证失败不阻止提交，设置为 True 允许尝试
                self.cookie_valid = True
    
    def _validate_cookie(self) -> bool:
        """验证 Cookie 是否有效
        
        使用 LeetCode GraphQL API 查询 userStatus，检查 isSignedIn 字段
        带重试机制，最多重试 3 次
        """
        print("🔍 正在验证 LEETCODE_COOKIE...", end=" ", flush=True)
        
        max_retries = 3
        timeout = 15  # 增加超时时间到 15 秒
        
        for attempt in range(max_retries):
            if attempt > 0:
                print(f"\n   重试 {attempt}/{max_retries}...", end=" ", flush=True)
            
            try:
                # 使用 GraphQL API 查询用户状态
                url = "https://leetcode.com/graphql"
                
                graphql_query = {
                    "query": """
                        query globalData {
                            userStatus {
                                isSignedIn
                                username
                                userId
                            }
                        }
                    """,
                    "variables": {}
                }
                
                body = json.dumps(graphql_query).encode('utf-8')
                
                headers = {
                    'Cookie': self.cookie,
                    'Content-Type': 'application/json',
                    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
                    'Referer': 'https://leetcode.com/',
                    'x-csrftoken': self.csrf_token or ''
                }
                
                req = urllib.request.Request(url, data=body, headers=headers, method='POST')
                
                with urllib.request.urlopen(req, timeout=timeout) as response:
                    data = json.loads(response.read().decode('utf-8'))
                    
                    # 检查 GraphQL 响应
                    if 'errors' in data:
                        error_msg = data['errors'][0].get('message', 'Unknown error')
                        print(color_text(f"❌ Cookie 无效 ({error_msg})", ColorCode.RED.value))
                        return False
                    
                    user_status = data.get('data', {}).get('userStatus', {})
                    is_signed_in = user_status.get('isSignedIn', False)
                    username = user_status.get('username', '')
                    
                    if is_signed_in and username:
                        print(color_text(f"✅ Cookie 有效 (用户: {username})", ColorCode.GREEN.value))
                        return True
                    else:
                        print(color_text("❌ Cookie 无效 (未登录)", ColorCode.RED.value))
                        return False
                    
            except urllib.error.HTTPError as e:
                if e.code == 401 or e.code == 403:
                    print(color_text(f"❌ Cookie 无效 (HTTP {e.code})", ColorCode.RED.value))
                    return False
                # 其他 HTTP 错误，如果是最后一次尝试则返回失败
                if attempt == max_retries - 1:
                    print(color_text(f"⚠️  HTTP {e.code}", ColorCode.YELLOW.value))
                    return False
                # 否则继续重试
                
            except urllib.error.URLError as e:
                if attempt == max_retries - 1:
                    print(color_text(f"⚠️  网络错误: {e.reason}", ColorCode.YELLOW.value))
                    return False
                # 否则继续重试
                    
            except Exception as e:
                if attempt == max_retries - 1:
                    print(color_text(f"⚠️  验证出错: {e}", ColorCode.YELLOW.value))
                    return False
                # 否则继续重试
        
        return False
    
    def _init_ai_client(self):
        """初始化 AI 客户端"""
        load_dotenv()
        
        provider = AIProvider.from_env()
        api_key = os.getenv("MOONSHOT_API_KEY") or os.getenv("AI_API_KEY")
        
        if not api_key:
            raise ValueError("请设置 MOONSHOT_API_KEY 或 AI_API_KEY")
        
        self.ai_client = OpenAI(
            api_key=api_key,
            base_url=provider.base_url
        )
        self.ai_model = provider.model
    
    def _extract_csrf_token(self) -> Optional[str]:
        """从 Cookie 中提取 CSRF Token"""
        import re
        match = re.search(r'csrftoken=([^;]+)', self.cookie)
        return match.group(1) if match else None
    
    def submit_problem(self, problem_id: int, solution_num: int = 1) -> bool:
        """提交指定题目到 LeetCode"""
        self.current_problem_id = problem_id
        
        # 1. 获取题目信息
        try:
            problem_data = self.repo.get_detail_by_id(problem_id, include_code=True)
            self.current_problem_slug = problem_data.slug
            print(f"📋 题目: [{problem_id}] {problem_data.title}")
            print(f"🔗 https://leetcode.com/problems/{problem_data.slug}/")
            print()
        except Exception as e:
            print(color_text(f"❌ 获取题目信息失败: {e}", ColorCode.RED.value))
            return False
        
        # 2. 读取本地代码
        header_code, source_code = self._read_local_code(problem_data.slug)
        if not source_code:
            return False
        
        # 3. 使用 AI 转换为 LeetCode 格式
        print("🤖 AI 转换中...")
        leetcode_code = self._convert_with_ai(problem_data, header_code, source_code, solution_num)
        if not leetcode_code:
            return False
        
        # 保存转换后的代码
        submit_dir = Path(".leetcode-cache/submit")
        submit_dir.mkdir(parents=True, exist_ok=True)
        submit_file = submit_dir / f"{problem_data.slug}_leetcode.cpp"
        submit_file.write_text(leetcode_code, encoding='utf-8')
        print(f"💾 转换后的代码已保存: {submit_file}")
        print()
        
        # 4. 提交到 LeetCode（如果配置了 Cookie）
        if not self.cookie or not getattr(self, 'cookie_valid', False):
            if not self.cookie:
                print(color_text("💡 提示: 设置 LEETCODE_COOKIE 后可自动提交到 LeetCode", ColorCode.CYAN.value))
                print("   export LEETCODE_COOKIE='csrftoken=xxx; LEETCODE_SESSION=xxx'")
            else:
                print(color_text("❌ LEETCODE_COOKIE 无效或已过期", ColorCode.RED.value))
                print("   请重新登录 LeetCode 并从浏览器复制新的 Cookie")
            return True
        
        return self._submit_to_leetcode(problem_data, leetcode_code)
    
    def submit_problem_with_result(self, problem_id: int, solution_num: int = 1) -> SubmissionResult:
        """提交题目并返回详细结果（用于 AI 自动修复）"""
        self.current_problem_id = problem_id
        
        try:
            problem_data = self.repo.get_detail_by_id(problem_id, include_code=True)
            self.current_problem_slug = problem_data.slug
        except Exception as e:
            return SubmissionResult(
                status="Error",
                status_code=-1,
                error_message=str(e)
            )
        
        # 读取并转换代码
        header_code, source_code = self._read_local_code(problem_data.slug)
        if not source_code:
            return SubmissionResult(
                status="Error",
                status_code=-1,
                error_message="无法读取源代码"
            )
        
        leetcode_code = self._convert_with_ai(problem_data, header_code, source_code, solution_num)
        if not leetcode_code:
            return SubmissionResult(
                status="Error",
                status_code=-1,
                error_message="AI 转换失败"
            )
        
        # 保存转换后的代码
        submit_dir = Path(".leetcode-cache/submit")
        submit_dir.mkdir(parents=True, exist_ok=True)
        submit_file = submit_dir / f"{problem_data.slug}_leetcode.cpp"
        submit_file.write_text(leetcode_code, encoding='utf-8')
        print(f"💾 转换后的代码已保存: {submit_file}")
        
        # 提交到 LeetCode
        if not self.cookie or not getattr(self, 'cookie_valid', False):
            if not self.cookie:
                return SubmissionResult(
                    status="Error",
                    status_code=-1,
                    error_message="未设置 LEETCODE_COOKIE"
                )
            else:
                return SubmissionResult(
                    status="Error",
                    status_code=-1,
                    error_message="LEETCODE_COOKIE 无效或已过期"
                )
        
        return self._submit_to_leetcode_with_result(problem_data, leetcode_code)
    
    def _submit_to_leetcode_with_result(self, problem_data: ProblemData, code: str) -> SubmissionResult:
        """提交到 LeetCode 并返回详细结果"""
        print("🌐 正在提交到 LeetCode...")
        
        # 1. 获取题目内部 ID
        question_id = self._get_question_id(problem_data.id)
        if not question_id:
            return SubmissionResult(
                status="Error",
                status_code=-1,
                error_message="无法获取题目内部 ID"
            )
        
        # 2. 提交代码
        submit_url = f"https://leetcode.com/problems/{problem_data.slug}/submit/"
        headers = {
            'Content-Type': 'application/json',
            'Cookie': self.cookie,
            'X-CSRFToken': self.csrf_token or '',
            'Referer': f'https://leetcode.com/problems/{problem_data.slug}/',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        }
        
        payload = {
            'lang': 'cpp',
            'question_id': question_id,
            'typed_code': code
        }
        
        try:
            req = urllib.request.Request(
                submit_url,
                data=json.dumps(payload).encode('utf-8'),
                headers=headers,
                method='POST'
            )
            
            with urllib.request.urlopen(req, timeout=30) as response:
                result = json.loads(response.read().decode('utf-8'))
                submission_id = result.get('submission_id')
                
                if not submission_id:
                    return SubmissionResult(
                        status="Error",
                        status_code=-1,
                        error_message=f"提交失败: {result}"
                    )
                
                print(f"✅ 提交成功，ID: {submission_id}")
                print("⏳ 等待判题结果...")
                
                # 3. 轮询结果
                return self._wait_for_result_with_details(submission_id)
                
        except Exception as e:
            return SubmissionResult(
                status="Error",
                status_code=-1,
                error_message=str(e)
            )
    
    def _wait_for_result_with_details(self, submission_id: str, max_wait: int = 60) -> SubmissionResult:
        """等待判题结果并返回详细信息"""
        check_url = f"https://leetcode.com/submissions/detail/{submission_id}/check/"
        headers = {
            'Cookie': self.cookie,
            'Referer': 'https://leetcode.com/',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        }
        
        start_time = time.time()
        dots = 0
        while time.time() - start_time < max_wait:
            try:
                req = urllib.request.Request(check_url, headers=headers)
                with urllib.request.urlopen(req, timeout=10) as response:
                    result = json.loads(response.read().decode('utf-8'))
                    
                    state = result.get('state')
                    if state == 'SUCCESS':
                        print()  # 换行
                        return self._parse_result(result)
                    
                    # 显示等待动画
                    dots = (dots + 1) % 4
                    print(f"\r⏳ 判题中{'.' * dots}{' ' * (3-dots)}", end='', flush=True)
                    time.sleep(1)
                    
            except Exception as e:
                time.sleep(1)
                continue
        
        return SubmissionResult(
            status="Timeout",
            status_code=-1,
            error_message="等待结果超时"
        )
    
    def _parse_result(self, result: Dict) -> SubmissionResult:
        """解析 LeetCode 返回的结果"""
        status_code = result.get('status_code', 0)
        status_msg = result.get('status_msg', 'Unknown')
        
        # 构建失败的测试用例信息
        failed_test_case = None
        if status_code == 11:  # Wrong Answer
            failed_test_case = {
                'input': result.get('input', 'N/A'),
                'actual': result.get('code_output', 'N/A'),
                'expected': result.get('expected_output', 'N/A')
            }
        
        return SubmissionResult(
            status=status_msg,
            status_code=status_code,
            total_test_cases=result.get('total_testcases', 0),
            passed_test_cases=result.get('total_correct', 0),
            failed_test_case=failed_test_case,
            runtime_ms=result.get('status_runtime', 'N/A'),
            memory_mb=result.get('status_memory', 'N/A'),
            error_message=result.get('full_runtime_error') or result.get('compile_error')
        )
    
    def _read_local_code(self, slug: str) -> tuple[Optional[str], Optional[str]]:
        """读取本地头文件和源代码"""
        header_path = Path(f"include/leetcode/problems/{slug}.h")
        source_path = Path(f"src/leetcode/problems/{slug}.cpp")
        
        header_code = None
        if header_path.exists():
            header_code = header_path.read_text(encoding='utf-8')
        
        if not source_path.exists():
            print(color_text(f"❌ 源文件不存在: {source_path}", ColorCode.RED.value))
            return None, None
        
        source_code = source_path.read_text(encoding='utf-8')
        return header_code, source_code
    
    def _convert_with_ai(self, problem_data: ProblemData,
                        header_code: Optional[str],
                        source_code: str,
                        solution_num: int) -> Optional[str]:
        """使用 AI 将项目代码转换为 LeetCode 格式"""
        
        print("🤖 正在使用 AI 转换代码格式...", end=" ", flush=True)
        
        # 构建提示词
        prompt = f"""请将以下 LeetCode C++ 项目代码转换为标准 LeetCode 提交格式。

题目：{problem_data.title}
题目描述：
{problem_data.content[:1500]}...

【原始头文件】
{header_code or "(无头文件)"}

【原始源文件】
{source_code}

【使用策略】使用 solution{solution_num} 函数（默认是第一个解法，可通过 --solution N 指定其他）

【转换要求】
1. 转换为标准 LeetCode class Solution 格式
2. 只包含 public 区域的解题函数，不要多策略注册代码
3. 移除项目特定的命名空间 (leetcode::problem_XXX)
4. 保留所有必要的辅助函数和类定义，但把它们放到 Solution 类内部或改为私有
5. 确保代码可以直接在 LeetCode 上编译运行
6. 只输出最终代码，不要有其他说明文字

【LeetCode 格式示例】
```cpp
class Solution {{
public:
    vector<int> twoSum(vector<int>& nums, int target) {{
        // 实现
    }}
}};
```

请输出转换后的代码："""

        try:
            # 根据 provider 决定是否设置 temperature
            # Moonshot 推理模型只支持 temperature=1
            extra_params = {}
            if "moonshot" not in self.ai_model.lower() and "kimi" not in self.ai_model.lower():
                extra_params["temperature"] = 0.2
            
            response = self.ai_client.chat.completions.create(
                model=self.ai_model,
                messages=[
                    {"role": "system", "content": "你是 C++ 代码转换专家，擅长将项目代码转换为 LeetCode 格式。只输出代码，不要有其他说明。"},
                    {"role": "user", "content": prompt}
                ],
                max_tokens=4000,
                **extra_params
            )
            
            code = response.choices[0].message.content
            
            # 提取代码块
            import re
            if "```cpp" in code:
                match = re.search(r'```cpp\s*(.*?)\s*```', code, re.DOTALL)
                if match:
                    code = match.group(1)
            elif "```" in code:
                match = re.search(r'```\s*(.*?)\s*```', code, re.DOTALL)
                if match:
                    code = match.group(1)
            
            print(color_text("✅ 完成", ColorCode.GREEN.value))
            return code.strip()
            
        except Exception as e:
            print(color_text(f"❌ AI 转换失败: {e}", ColorCode.RED.value))
            return None
    
    def _submit_to_leetcode(self, problem_data: ProblemData, code: str) -> bool:
        """提交到 LeetCode"""
        print("🌐 正在提交到 LeetCode...")
        
        # 1. 获取题目 ID（内部 ID）
        question_id = self._get_question_id(problem_data.id)
        if not question_id:
            print(color_text("❌ 无法获取题目内部 ID", ColorCode.RED.value))
            return False
        
        # 2. 提交代码
        submit_url = f"https://leetcode.com/problems/{problem_data.slug}/submit/"
        headers = {
            'Content-Type': 'application/json',
            'Cookie': self.cookie,
            'X-CSRFToken': self.csrf_token or '',
            'Referer': f'https://leetcode.com/problems/{problem_data.slug}/',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        }
        
        payload = {
            'lang': 'cpp',
            'question_id': question_id,
            'typed_code': code
        }
        
        try:
            req = urllib.request.Request(
                submit_url,
                data=json.dumps(payload).encode('utf-8'),
                headers=headers,
                method='POST'
            )
            
            with urllib.request.urlopen(req, timeout=30) as response:
                result = json.loads(response.read().decode('utf-8'))
                submission_id = result.get('submission_id')
                
                if not submission_id:
                    print(color_text(f"❌ 提交失败: {result}", ColorCode.RED.value))
                    return False
                
                print(f"✅ 提交成功，ID: {submission_id}")
                print("⏳ 等待判题结果...")
                
                # 3. 轮询结果
                return self._wait_for_result(submission_id)
                
        except Exception as e:
            print(color_text(f"❌ 提交异常: {e}", ColorCode.RED.value))
            return False
    
    def _get_question_id(self, problem_id: int) -> Optional[str]:
        """获取题目的内部 ID"""
        try:
            # 需要使用 get_detail_by_id 获取 question_id
            problem_data = self.repo.get_detail_by_id(problem_id)
            return str(problem_data.question_id)
        except:
            return None
    
    def _wait_for_result(self, submission_id: str, max_wait: int = 60) -> bool:
        """等待判题结果"""
        check_url = f"https://leetcode.com/submissions/detail/{submission_id}/check/"
        headers = {
            'Cookie': self.cookie,
            'Referer': 'https://leetcode.com/',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        }
        
        start_time = time.time()
        while time.time() - start_time < max_wait:
            try:
                req = urllib.request.Request(check_url, headers=headers)
                with urllib.request.urlopen(req, timeout=10) as response:
                    result = json.loads(response.read().decode('utf-8'))
                    
                    state = result.get('state')
                    if state == 'SUCCESS':
                        return self._display_result(result)
                    
                    time.sleep(1)
                    
            except Exception as e:
                time.sleep(1)
                continue
        
        print(color_text("⏱️  等待超时", ColorCode.YELLOW.value))
        return False
    
    def _display_result(self, result: Dict) -> bool:
        """显示判题结果"""
        status_code = result.get('status_code', 0)
        status_msg = result.get('status_msg', 'Unknown')
        
        print()
        if status_code == 10:  # Accepted
            print(color_text("✅ Accepted!", ColorCode.GREEN.value))
            print(f"   执行用时: {result.get('status_runtime', 'N/A')}")
            print(f"   内存消耗: {result.get('status_memory', 'N/A')}")
            return True
        
        elif status_code == 11:  # Wrong Answer
            print(color_text("❌ Wrong Answer", ColorCode.RED.value))
            print(f"\n输入:")
            print(result.get('input', 'N/A'))
            print(f"\n输出:")
            print(result.get('code_output', 'N/A'))
            print(f"\n期望:")
            print(result.get('expected_output', 'N/A'))
            return False
        
        elif status_code == 14:  # Time Limit Exceeded
            print(color_text("⏱️  Time Limit Exceeded", ColorCode.YELLOW.value))
            return False
        
        elif status_code == 15:  # Runtime Error
            print(color_text("💥 Runtime Error", ColorCode.RED.value))
            print(f"错误信息: {result.get('full_runtime_error', 'N/A')}")
            return False
        
        else:
            print(color_text(f"❌ {status_msg}", ColorCode.RED.value))
            print(f"详情: {result}")
            return False


def main():
    parser = argparse.ArgumentParser(
        description="将本地代码转换为 LeetCode 格式并提交验证",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 转换并提交题目 1
  python -m script.leetcode.submit 1
  
  # 使用第2个解法
  python -m script.leetcode.submit 1 --solution 2
  
  # 仅转换不提交（没有 Cookie 时）
  python -m script.leetcode.submit 1
        """
    )
    parser.add_argument("id", type=int, help="题目 ID")
    parser.add_argument("--solution", "-n", type=int, default=1, help="使用第 n 个解法（默认 1）")
    
    args = parser.parse_args()
    
    try:
        submitter = LeetCodeSubmitter()
        success = submitter.submit_problem(args.id, args.solution)
        sys.exit(0 if success else 1)
    except Exception as e:
        print(color_text(f"❌ 错误: {e}", ColorCode.RED.value))
        sys.exit(1)


if __name__ == "__main__":
    main()
