#include "leetcode/problems/resulting-string-after-adjacent-removals.h"

namespace leetcode {
namespace problem_3561 {

// 判断两个字符在字母表中是否连续（考虑循环）
static bool isConsecutive(char a, char b) {
  int diff = abs(a - b);
  return diff == 1 || diff == 25;  // 25 = 'z' - 'a'
}

// 栈解法：遍历字符串，维护一个结果栈
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution1(string s) {
  string stack;
  for (char c : s) {
    if (!stack.empty() && isConsecutive(stack.back(), c)) {
      // 栈顶字符与当前字符连续，移除栈顶（相当于移除这对）
      stack.pop_back();
    } else {
      // 不连续，压入当前字符
      stack.push_back(c);
    }
  }
  return stack;
}

ResultingStringAfterAdjacentRemovalsSolution::ResultingStringAfterAdjacentRemovalsSolution() {
  setMetaInfo({.id = 3561,
               .title = "Resulting String After Adjacent Removals",
               .url = "https://leetcode.com/problems/resulting-string-after-adjacent-removals/"});
  registerStrategy("Stack", solution1);
}

string ResultingStringAfterAdjacentRemovalsSolution::resultingString(string s) {
  return getSolution()(s);
}

}  // namespace problem_3561
}  // namespace leetcode
