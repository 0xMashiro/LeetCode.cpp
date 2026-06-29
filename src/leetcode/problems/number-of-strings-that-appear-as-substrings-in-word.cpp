#include "leetcode/problems/number-of-strings-that-appear-as-substrings-in-word.h"

namespace leetcode {
namespace problem_1967 {

// 直接使用 string::find 判断每个 pattern 是否为 word 的子串
// 时间复杂度: O(n * m * k), n = patterns.size(), m = word.size(), k = 平均 pattern 长度
// 空间复杂度: O(1)
static int solution1(std::vector<std::string>& patterns, std::string word) {
  int count = 0;
  for (const auto& pattern : patterns) {
    if (word.find(pattern) != std::string::npos) {
      ++count;
    }
  }
  return count;
}

NumberOfStringsThatAppearAsSubstringsInWordSolution::
    NumberOfStringsThatAppearAsSubstringsInWordSolution() {
  setMetaInfo({.id = 1967,
               .title = "Number of Strings That Appear as Substrings in Word",
               .url = "https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/"});
  registerStrategy({.name = "String Find",
                    .expected = "Accepted",
                    .time_complexity = "O(n * m * k)",
                    .space_complexity = "O(1)",
                    .tags = {"Array", "String"}},
                   solution1);
}

int NumberOfStringsThatAppearAsSubstringsInWordSolution::numOfStrings(
    std::vector<std::string>& patterns, std::string word) {
  return getSolution()(patterns, word);
}

}  // namespace problem_1967
}  // namespace leetcode
