
#include "leetcode/problems/collecting-chocolates.h"

namespace leetcode {
namespace problem_2735 {

static long long solution1(vector<int>& nums, int x) {
  const int n = nums.size();
  
  // minCost[i][k] 表示类型 i 在 k 次旋转内的最小成本
  // 实际上可以优化为一维，但 n <= 1000，二维也可以接受
  vector<vector<long long>> minCost(n, vector<long long>(n));
  
  // 初始化：0 次旋转，每个类型只能选自己的位置
  for (int i = 0; i < n; ++i) {
    minCost[i][0] = nums[i];
  }
  
  // 预处理：对于每个类型，计算旋转 1 到 n-1 次的最小成本
  for (int k = 1; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      // 旋转 k 次后，原来位置 (i - k + n) % n 的巧克力变成了类型 i
      int originalPos = (i - k + n) % n;
      minCost[i][k] = min(minCost[i][k - 1], (long long)nums[originalPos]);
    }
  }
  
  long long result = LLONG_MAX;
  
  // 枚举总旋转次数 k (0 到 n-1)
  for (int k = 0; k < n; ++k) {
    long long totalCost = (long long)k * x;  // 操作成本
    for (int i = 0; i < n; ++i) {
      totalCost += minCost[i][k];  // 每种类型在 k 次旋转内的最小成本
    }
    result = min(result, totalCost);
  }
  
  return result;
}

CollectingChocolatesSolution::CollectingChocolatesSolution() {
  setMetaInfo({.id = 2735,
               .title = "Collecting Chocolates",
               .url = "https://leetcode.com/problems/collecting-chocolates/"});
  registerStrategy("Precompute Min Cost", solution1);
}

long long CollectingChocolatesSolution::minCost(vector<int>& nums, int x) {
  return getSolution()(nums, x);
}

}  // namespace problem_2735
}  // namespace leetcode
