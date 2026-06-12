#include "leetcode/problems/count-the-number-of-special-characters-i.h"

namespace leetcode {
namespace problem_3120 {

// 暴力枚举：对每个字母 a-z，分别查找小写和大写
// 时间复杂度: O(n * 26) = O(n), 空间复杂度: O(1)
// 注：n <= 50，但作为教学用展示最朴素思路
static int solution1(string word) {
  int count = 0;
  for (char c = 'a'; c <= 'z'; ++c) {
    bool hasLower = false, hasUpper = false;
    for (char ch : word) {
      if (ch == c) hasLower = true;
      if (ch == toupper(c)) hasUpper = true;
    }
    if (hasLower && hasUpper) ++count;
  }
  return count;
}

// 哈希集合：用两个 bool 数组记录小写和大写出现情况
// 时间复杂度: O(n + 26) = O(n), 空间复杂度: O(26) = O(1)
static int solution2(string word) {
  bool lower[26] = {false};
  bool upper[26] = {false};
  for (char ch : word) {
    if (ch >= 'a' && ch <= 'z') {
      lower[ch - 'a'] = true;
    } else {
      upper[ch - 'A'] = true;
    }
  }
  int count = 0;
  for (int i = 0; i < 26; ++i) {
    if (lower[i] && upper[i]) ++count;
  }
  return count;
}

// 位掩码：用两个 int 的 26 个 bit 分别记录小写和大写出现情况
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution3(string word) {
  int lowerMask = 0, upperMask = 0;
  for (char ch : word) {
    if (ch >= 'a' && ch <= 'z') {
      lowerMask |= 1 << (ch - 'a');
    } else {
      upperMask |= 1 << (ch - 'A');
    }
  }
  // 按位与后统计 1 的个数
  return __builtin_popcount(lowerMask & upperMask);
}

CountTheNumberOfSpecialCharactersISolution::CountTheNumberOfSpecialCharactersISolution() {
  setMetaInfo({.id = 3120,
               .title = "Count the Number of Special Characters I",
               .url = "https://leetcode.com/problems/count-the-number-of-special-characters-i/"});
  registerStrategy({.name = "Brute Force"}, solution1);  // O(n*26) 暴力搜索
  registerStrategy({.name = "Bool Array"}, solution2);   // O(n) 哈希数组
  registerStrategy({.name = "Bitmask"}, solution3);      // O(n) 位运算最优
}

int CountTheNumberOfSpecialCharactersISolution::numberOfSpecialChars(string word) {
  return getSolution()(word);
}

}  // namespace problem_3120
}  // namespace leetcode
