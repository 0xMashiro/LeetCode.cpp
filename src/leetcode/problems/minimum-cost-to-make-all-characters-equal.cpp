#include "leetcode/problems/minimum-cost-to-make-all-characters-equal.h"

namespace leetcode {
namespace problem_2712 {

// 核心观察：当 s[i] != s[i+1] 时，必须消除这个边界差异
// 有两种选择：
//   1. 翻转前缀 [0, i]，代价为 i + 1
//   2. 翻转后缀 [i+1, n-1]，代价为 n - i - 1
// 选择代价较小的那个
// 时间复杂度: O(n), 空间复杂度: O(1)
static long long solution1(string s) {
  const int n = s.size();
  long long cost = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (s[i] != s[i + 1]) {
      // 选择更便宜的操作来消除这个边界
      cost += min(i + 1, n - i - 1);
    }
  }
  return cost;
}

MinimumCostToMakeAllCharactersEqualSolution::MinimumCostToMakeAllCharactersEqualSolution() {
  setMetaInfo({.id = 2712,
               .title = "Minimum Cost to Make All Characters Equal",
               .url = "https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/"});
  registerStrategy("Greedy", solution1);
}

long long MinimumCostToMakeAllCharactersEqualSolution::minimumCost(string s) {
  return getSolution()(s);
}

}  // namespace problem_2712
}  // namespace leetcode
