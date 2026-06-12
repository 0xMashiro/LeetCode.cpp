#include "leetcode/problems/rotate-string.h"

namespace leetcode {
namespace problem_796 {

// 暴力模拟：枚举所有可能的循环移位
// 时间复杂度 O(n²)，空间复杂度 O(1)
// 思路：对于每个偏移量 i，检查 s[i:] + s[:i] 是否等于 goal
static bool solution1(string s, string goal) {
  int n = s.length();
  if (n != (int)goal.length()) return false;
  if (n == 0) return true;
  for (int i = 0; i < n; ++i) {
    bool match = true;
    for (int j = 0; j < n; ++j) {
      if (s[(i + j) % n] != goal[j]) {
        match = false;
        break;
      }
    }
    if (match) return true;
  }
  return false;
}

// 字符串拼接：利用 s+s 包含所有循环移位的性质
// 时间复杂度 O(n)，空间复杂度 O(n)
// 思路：s 的所有循环移位都作为子串出现在 s+s 中，只需检查 goal 是否为子串
static bool solution2(string s, string goal) {
  if (s.length() != goal.length()) return false;
  if (s.empty()) return true;
  return (s + s).find(goal) != string::npos;
}

RotateStringSolution::RotateStringSolution() {
  setMetaInfo({.id = 796,
               .title = "Rotate String",
               .url = "https://leetcode.com/problems/rotate-string/"});
  registerStrategy({.name = "Brute Force"}, solution1);
  registerStrategy({.name = "Concatenation Check"}, solution2);
}

bool RotateStringSolution::rotateString(string s, string goal) {
  return getSolution()(s, goal);
}

}  // namespace problem_796
}  // namespace leetcode
