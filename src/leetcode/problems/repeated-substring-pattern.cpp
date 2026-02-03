#include "leetcode/problems/repeated-substring-pattern.h"

namespace leetcode {
namespace problem_459 {

// 数学技巧法：如果 s 可由子串重复构成，则 (s+s) 去掉首尾后必包含 s
// 时间复杂度: O(n), 空间复杂度: O(n)
static bool solution1(string s) {
  string doubled = s + s;
  // 去掉首尾字符
  string sub = doubled.substr(1, doubled.size() - 2);
  return sub.find(s) != string::npos;
}

// 暴力枚举法：枚举所有可能的子串长度
// 时间复杂度: O(n^2), 空间复杂度: O(n)
static bool solution2(string s) {
  int n = s.size();
  // 枚举子串长度，子串长度必须是 n 的约数且小于 n
  for (int len = 1; len <= n / 2; ++len) {
    if (n % len != 0) continue;
    string pattern = s.substr(0, len);
    bool valid = true;
    for (int i = len; i < n; i += len) {
      if (s.substr(i, len) != pattern) {
        valid = false;
        break;
      }
    }
    if (valid) return true;
  }
  return false;
}

RepeatedSubstringPatternSolution::RepeatedSubstringPatternSolution() {
  setMetaInfo({.id = 459,
               .title = "Repeated Substring Pattern",
               .url = "https://leetcode.com/problems/repeated-substring-pattern/"});
  registerStrategy("Mathematical Trick", solution1);
  registerStrategy("Brute Force", solution2);
}

bool RepeatedSubstringPatternSolution::repeatedSubstringPattern(string s) {
  return getSolution()(s);
}

}  // namespace problem_459
}  // namespace leetcode
