
#include "leetcode/problems/maximum-number-of-alloys.h"

namespace leetcode {
namespace problem_2861 {

/**
 * 二分搜索解法
 * 
 * 思路：对于每台机器，二分搜索能生产的最大合金数量
 * 
 * 判定函数：生产 x 个合金需要多少钱？
 * - 对于金属 j，需要 composition[i][j] * x 单位
 * - 如果库存 stock[j] >= 需要量，则不需要购买
 * - 否则需要购买 (need - stock[j]) 单位，花费 (need - stock[j]) * cost[j]
 * 
 * 时间复杂度：O(k * n * log(MAX))，其中 MAX 是二分上界（约 2e8）
 * 空间复杂度：O(1)
 */
static int solution1(int n, int k, int budget, vector<vector<int>>& composition, 
                     vector<int>& stock, vector<int>& cost) {
  long long ans = 0;
  
  // 对每台机器进行二分搜索
  for (int machine = 0; machine < k; ++machine) {
    // 二分搜索范围：[0, 2e8]
    // 上界估计：假设只用最便宜的金属，(budget + maxStock) / 1 + 1
    long long left = 0, right = 2e8;
    
    while (left <= right) {
      long long mid = left + (right - left) / 2;
      long long totalCost = 0;
      
      // 计算生产 mid 个合金需要的总花费
      for (int j = 0; j < n && totalCost <= budget; ++j) {
        long long need = (long long)composition[machine][j] * mid;  // 需要量
        if (need > stock[j]) {
          // 需要购买
          totalCost += (need - stock[j]) * cost[j];
        }
        // 如果库存足够，花费为 0
      }
      
      if (totalCost <= budget) {
        // 预算足够，尝试生产更多
        ans = max(ans, mid);
        left = mid + 1;
      } else {
        // 预算不足，减少生产量
        right = mid - 1;
      }
    }
  }
  
  return (int)ans;
}

MaximumNumberOfAlloysSolution::MaximumNumberOfAlloysSolution() {
  setMetaInfo({.id = 2861,
               .title = "Maximum Number of Alloys",
               .url = "https://leetcode.com/problems/maximum-number-of-alloys/"});
  registerStrategy("Binary Search", solution1);
}

int MaximumNumberOfAlloysSolution::maxNumberOfAlloys(int n, int k, int budget, 
                                                       vector<vector<int>>& composition, 
                                                       vector<int>& stock, 
                                                       vector<int>& cost) {
  return getSolution()(n, k, budget, composition, stock, cost);
}

}  // namespace problem_2861
}  // namespace leetcode
