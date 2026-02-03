#include "leetcode/problems/check-if-two-string-arrays-are-equivalent.h"

namespace leetcode {
namespace problem_1662 {

// 策略1：直接拼接字符串后比较
// 时间复杂度: O(n), 空间复杂度: O(n) - n为总字符数
static bool solution1(vector<string>& word1, vector<string>& word2) {
  string s1, s2;
  for (const auto& w : word1) {
    s1 += w;
  }
  for (const auto& w : word2) {
    s2 += w;
  }
  return s1 == s2;
}

// 策略2：使用stringstream拼接后比较
// 时间复杂度: O(n), 空间复杂度: O(n)
static bool solution2(vector<string>& word1, vector<string>& word2) {
  stringstream ss1, ss2;
  for (const auto& w : word1) {
    ss1 << w;
  }
  for (const auto& w : word2) {
    ss2 << w;
  }
  return ss1.str() == ss2.str();
}

CheckIfTwoStringArraysAreEquivalentSolution::CheckIfTwoStringArraysAreEquivalentSolution() {
  setMetaInfo({.id = 1662,
               .title = "Check If Two String Arrays are Equivalent",
               .url = "https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/"});
  registerStrategy("Concatenate", solution1);
  registerStrategy("StringStream", solution2);
}

bool CheckIfTwoStringArraysAreEquivalentSolution::arrayStringsAreEqual(
    vector<string>& word1, vector<string>& word2) {
  return getSolution()(word1, word2);
}

}  // namespace problem_1662
}  // namespace leetcode
