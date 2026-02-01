#include "leetcode/problems/make-the-string-great.h"

namespace leetcode {
namespace problem_1544 {

/**
 * 栈模拟法：遍历字符串，使用栈维护结果
 * 对于每个字符，如果栈顶字符与当前字符构成"坏对"（一个大写一个小写，且是相同字母），
 * 则移除栈顶字符；否则当前字符入栈
 * 
 * 判断坏对的方法：abs(a - b) == 32（同一字母的大小写ASCII相差32）
 * 
 * 时间复杂度: O(n)，其中 n 为字符串长度
 * 空间复杂度: O(n)，栈空间
 */
static std::string solution1(std::string s) {
  std::string stack;
  
  for (char c : s) {
    if (!stack.empty() && std::abs(stack.back() - c) == 32) {
      // 栈顶字符与当前字符是"坏对"，移除栈顶
      stack.pop_back();
    } else {
      // 不是坏对，当前字符入栈
      stack.push_back(c);
    }
  }
  
  return stack;
}

MakeTheStringGreatSolution::MakeTheStringGreatSolution() {
  setMetaInfo({.id = 1544,
               .title = "Make The String Great",
               .url = "https://leetcode.com/problems/make-the-string-great/"});
  registerStrategy("Stack Simulation", solution1);
}

std::string MakeTheStringGreatSolution::makeGood(std::string s) {
  return getSolution()(s);
}

}  // namespace problem_1544
}  // namespace leetcode
