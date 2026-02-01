#include "leetcode/problems/minimum-sum-of-values-by-dividing-array.h"

namespace leetcode {
namespace problem_3117 {

// 基于 AND 单调性的 DP 优化版本
static int solve(vector<int>& nums, vector<int>& andValues) {
  int n = nums.size();
  int m = andValues.size();
  
  if (m > n) return -1;
  
  const int INF = 1e9;
  // dp[i][j] = 将 nums[0..i-1] 分成 j 个子数组的最小值和
  // i 的范围是 [0..n]，j 的范围是 [0..m]
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
  dp[0][0] = 0;
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= min(i, m); j++) {
      int target = andValues[j - 1];
      int curAnd = nums[i - 1];
      
      // 枚举第 j 个子数组的起点 k（0-indexed）
      // 子数组为 nums[k..i-1]，最后一个元素是 nums[i-1]
      for (int k = i - 1; k >= j - 1; k--) {
        if (k < i - 1) {
          curAnd &= nums[k];
        }
        
        // AND 值只会递减，如果已经小于 target，后面的都不用看了
        if (curAnd < target) break;
        
        if (curAnd == target && dp[k][j - 1] != INF) {
          dp[i][j] = min(dp[i][j], dp[k][j - 1] + nums[i - 1]);
        }
        
        // 优化：如果 curAnd 已经等于 0，再 AND 任何数都是 0
        // 但如果 target != 0，上面已经 break 了
        // 如果 target == 0，我们需要找到所有能形成 0 的位置
        // 但 dp[k][j-1] 可能不同，所以不能简单 break
      }
    }
  }
  
  return dp[n][m] == INF ? -1 : dp[n][m];
}

// 进一步优化：利用 AND 值的有限性
// 对于固定的 i，从右往左扫，不同的 AND 值最多只有 O(log(max)) 个
static int solveOptimized(vector<int>& nums, vector<int>& andValues) {
  int n = nums.size();
  int m = andValues.size();
  
  if (m > n) return -1;
  
  const int INF = 1e9;
  // dp[j] 表示当前位置之前，分成 j 个子数组的最小值和
  // 但我们需要按 i 的顺序处理，所以还是需要二维 DP
  
  // dp[i][j] = 以位置 i-1 结尾，分成 j 个子数组的最小值和
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
  dp[0][0] = 0;
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= min(i, m); j++) {
      int target = andValues[j - 1];
      
      // 使用 map 来记录 (AND值 -> 该AND值对应的最小dp[k][j-1])
      // 但对于固定的 i 和 j，我们只需要找特定的 target
      
      int curAnd = nums[i - 1];
      
      // 枚举子数组起点 k
      for (int k = i - 1; k >= j - 1; k--) {
        if (k < i - 1) {
          curAnd &= nums[k];
        }
        
        if (curAnd < target) break;
        
        if (curAnd == target && dp[k][j - 1] != INF) {
          dp[i][j] = min(dp[i][j], dp[k][j - 1] + nums[i - 1]);
        }
      }
    }
  }
  
  return dp[n][m] == INF ? -1 : dp[n][m];
}

MinimumSumOfValuesByDividingArraySolution::MinimumSumOfValuesByDividingArraySolution() {
  setMetaInfo({.id = 3117,
               .title = "Minimum Sum of Values by Dividing Array",
               .url = "https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/"});
  registerStrategy("DP", solve);
  registerStrategy("DP Optimized", solveOptimized);
}

int MinimumSumOfValuesByDividingArraySolution::minimumValueSum(vector<int>& nums, vector<int>& andValues) {
  return getSolution()(nums, andValues);
}

}  // namespace problem_3117
}  // namespace leetcode
