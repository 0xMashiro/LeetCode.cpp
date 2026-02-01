#include "leetcode/problems/valid-parentheses.h"

namespace leetcode {
namespace problem_20 {

// 栈方法：遍历字符串，用栈匹配括号
// 时间复杂度: O(n), 空间复杂度: O(n)
static bool solution1(std::string s) {
  std::stack<char> stk;
  
  for (char c : s) {
    if (c == '(' || c == '[' || c == '{') {
      // 左括号入栈
      stk.push(c);
    } else {
      // 右括号，检查是否匹配
      if (stk.empty()) return false;
      
      char top = stk.top();
      if ((c == ')' && top != '(') ||
          (c == ']' && top != '[') ||
          (c == '}' && top != '{')) {
        return false;
      }
      stk.pop();
    }
  }
  
  return stk.empty();
}

// 优化：使用哈希表存储匹配关系
// 时间复杂度: O(n), 空间复杂度: O(n)
static bool solution2(std::string s) {
  std::stack<char> stk;
  std::unordered_map<char, char> match = {
    {')', '('},
    {']', '['},
    {'}', '{'}
  };
  
  for (char c : s) {
    if (match.count(c)) {
      // 是右括号
      if (stk.empty() || stk.top() != match[c]) {
        return false;
      }
      stk.pop();
    } else {
      // 是左括号
      stk.push(c);
    }
  }
  
  return stk.empty();
}

ValidParenthesesSolution::ValidParenthesesSolution() {
  setMetaInfo({.id = 20,
               .title = "Valid Parentheses",
               .url = "https://leetcode.com/problems/valid-parentheses/"});
  registerStrategy("Stack", solution1);
  registerStrategy("Stack with HashMap", solution2);
}

bool ValidParenthesesSolution::isValid(std::string s) {
  return getSolution()(s);
}

}  // namespace problem_20
}  // namespace leetcode
