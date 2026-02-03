
#include "leetcode/problems/evaluate-reverse-polish-notation.h"

namespace leetcode {
namespace problem_150 {

// 栈解法：遍历 tokens，遇到数字入栈，遇到运算符弹出两个数计算
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<string>& tokens) {
  stack<long long> st;  // 使用 long long 防止中间结果溢出
  
  for (const string& token : tokens) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      // 是运算符，弹出两个操作数
      long long right = st.top(); st.pop();
      long long left = st.top(); st.pop();
      long long result = 0;
      
      if (token == "+") {
        result = left + right;
      } else if (token == "-") {
        result = left - right;
      } else if (token == "*") {
        result = left * right;
      } else if (token == "/") {
        result = left / right;  // C++ 整数除法向零取整，符合题目要求
      }
      
      st.push(result);
    } else {
      // 是数字，转换为整数入栈
      st.push(stoll(token));
    }
  }
  
  return static_cast<int>(st.top());
}

EvaluateReversePolishNotationSolution::EvaluateReversePolishNotationSolution() {
  setMetaInfo({.id = 150,
               .title = "Evaluate Reverse Polish Notation",
               .url = "https://leetcode.com/problems/evaluate-reverse-polish-notation/"});
  registerStrategy("Stack", solution1);
}

int EvaluateReversePolishNotationSolution::evalRPN(vector<string>& tokens) {
  return getSolution()(tokens);
}

}  // namespace problem_150
}  // namespace leetcode
