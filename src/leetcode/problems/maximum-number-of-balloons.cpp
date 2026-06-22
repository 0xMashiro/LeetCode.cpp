#include "leetcode/problems/maximum-number-of-balloons.h"

#include <algorithm>
#include <string>

namespace leetcode {
namespace problem_1189 {

// 计数法：统计 text 中每个字符的频率，然后计算能组成 "balloon" 的最大实例数
// 时间复杂度: O(n)，空间复杂度: O(1)
static int solutionCounting(std::string text) {
  int count[26] = {0};
  for (char c : text) {
    count[c - 'a']++;
  }

  // "balloon": b=1, a=1, l=2, o=2, n=1
  int ans = count['b' - 'a'];
  ans = std::min(ans, count['a' - 'a']);
  ans = std::min(ans, count['l' - 'a'] / 2);
  ans = std::min(ans, count['o' - 'a'] / 2);
  ans = std::min(ans, count['n' - 'a']);

  return ans;
}

MaximumNumberOfBalloonsSolution::MaximumNumberOfBalloonsSolution() {
  setMetaInfo({.id = 1189,
               .title = "Maximum Number of Balloons",
               .url = "https://leetcode.com/problems/maximum-number-of-balloons/"});
  registerStrategy({.name = "Counting",
                    .time_complexity = "O(n)",
                    .space_complexity = "O(1)",
                    .tags = {"Hash Table", "String", "Counting"}},
                   solutionCounting);
}

int MaximumNumberOfBalloonsSolution::maxNumberOfBalloons(std::string text) {
  return getSolution()(text);
}

}  // namespace problem_1189
}  // namespace leetcode
