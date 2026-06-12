#include "leetcode/problems/minimum-cost-of-buying-candies-with-discount.h"

namespace leetcode {
namespace problem_2144 {

// 本题结构唯一合理解为 O(n log n) 贪心+排序，无明显多解
// 贪心策略：降序排序，每 3 个一组买前两个，第三个免费
// 时间复杂度: O(n log n), 空间复杂度: O(1)（视排序而定）
static int solution1(vector<int>& cost) {
  sort(cost.begin(), cost.end(), greater<int>());
  int total = 0;
  const int n = cost.size();
  for (int i = 0; i < n; ++i) {
    // 每 3 个一组，索引 % 3 == 2 的是免费糖果
    if (i % 3 != 2) {
      total += cost[i];
    }
  }
  return total;
}

MinimumCostOfBuyingCandiesWithDiscountSolution::MinimumCostOfBuyingCandiesWithDiscountSolution() {
  setMetaInfo({.id = 2144,
               .title = "Minimum Cost of Buying Candies With Discount",
               .url = "https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/"});
  registerStrategy({.name = "Greedy + Sort"}, solution1);
}

int MinimumCostOfBuyingCandiesWithDiscountSolution::minimumCost(vector<int>& cost) {
  return getSolution()(cost);
}

}  // namespace problem_2144
}  // namespace leetcode
