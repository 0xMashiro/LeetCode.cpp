#include "leetcode/problems/smallest-subsequence-of-distinct-characters.h"

namespace leetcode {
namespace problem_1081 {

// 单调栈：维护字典序最小的子序列
// 1. 统计每个字符最后出现的位置
// 2. 遍历字符串，如果当前字符已在栈中则跳过
// 3. 如果当前字符 < 栈顶字符，且栈顶字符后面还会出现，则弹出栈顶
// 4. 当前字符入栈
// 时间复杂度: O(n), 空间复杂度: O(1)
static string solution1(string s) {
  int n = s.size();
  // 记录每个字符最后出现的位置
  vector<int> last(26, -1);
  for (int i = 0; i < n; ++i) {
    last[s[i] - 'a'] = i;
  }
  
  string stack;  // 用 string 模拟栈
  vector<bool> inStack(26, false);  // 记录字符是否在栈中
  
  for (int i = 0; i < n; ++i) {
    char c = s[i];
    // 如果当前字符已经在栈中，跳过
    if (inStack[c - 'a']) {
      continue;
    }
    
    // 如果当前字符 < 栈顶字符，且栈顶字符后面还会出现，则弹出
    while (!stack.empty() && c < stack.back() && last[stack.back() - 'a'] > i) {
      inStack[stack.back() - 'a'] = false;
      stack.pop_back();
    }
    
    // 当前字符入栈
    stack.push_back(c);
    inStack[c - 'a'] = true;
  }
  
  return stack;
}

SmallestSubsequenceOfDistinctCharactersSolution::SmallestSubsequenceOfDistinctCharactersSolution() {
  setMetaInfo({.id = 1081,
               .title = "Smallest Subsequence of Distinct Characters",
               .url = "https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/"});
  registerStrategy("Monotonic Stack", solution1);
}

string SmallestSubsequenceOfDistinctCharactersSolution::smallestSubsequence(string s) {
  return getSolution()(s);
}

}  // namespace problem_1081
}  // namespace leetcode
