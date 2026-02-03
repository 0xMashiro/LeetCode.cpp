#include "leetcode/problems/minimum-cost-to-acquire-required-items.h"

namespace leetcode {
namespace problem_3789 {

// O(1) 数学优化：检查关键点的成本
// 成本函数 f(z) = z*costBoth + max(0, need1-z)*cost1 + max(0, need2-z)*cost2
// 这是分段线性函数，最小值必定出现在区间端点
static long long solution1(int cost1, int cost2, int costBoth, int need1, int need2) {
  // 辅助函数：计算给定 z 的总成本
  auto calc = [&](long long z) -> long long {
    long long remain1 = std::max(0LL, (long long)need1 - z);
    long long remain2 = std::max(0LL, (long long)need2 - z);
    return z * costBoth + remain1 * cost1 + remain2 * cost2;
  };
  
  long long ans = LLONG_MAX;
  
  // 关键点：z = 0, z = need1, z = need2, z = min(need1, need2)
  // 注意：min(need1, need2) 可能是 need1 或 need2 之一
  std::vector<long long> candidates = {0, need1, need2};
  
  for (long long z : candidates) {
    ans = std::min(ans, calc(z));
  }
  
  return ans;
}

MinimumCostToAcquireRequiredItemsSolution::MinimumCostToAcquireRequiredItemsSolution() {
  setMetaInfo({.id = 3789,
               .title = "Minimum Cost to Acquire Required Items",
               .url = "https://leetcode.com/problems/minimum-cost-to-acquire-required-items/"});
  registerStrategy("Optimized", solution1);
}

long long MinimumCostToAcquireRequiredItemsSolution::minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
  return getSolution()(cost1, cost2, costBoth, need1, need2);
}

}  // namespace problem_3789
}  // namespace leetcode
