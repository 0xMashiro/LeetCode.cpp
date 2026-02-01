#include "leetcode/problems/maximum-strength-of-k-disjoint-subarrays.h"

namespace leetcode {
namespace problem_3077 {

// 动态规划解法
// dp[j][0]：已经选了 j 个子数组，当前不在任何子数组中的最大强度
// dp[j][1]：已经选了 j 个子数组，当前正处于第 j 个子数组中的最大强度
// 由于当前子数组的系数只与 j 有关，我们用 sign 来标记正负（j为奇数时正，偶数时负）
// 但实际上系数应该是：第1个子数组系数为+k，第2个为-(k-1)，第3个为+(k-2)...
// 所以第 j 个子数组的系数是 (k-j+1) * (-1)^(j+1) 的符号，即 j为奇数时正，偶数时负
// 具体值：第j个 = (k-j+1) 如果j是奇数，否则 -(k-j+1)
static long long solution1(vector<int>& nums, int k) {
  const int n = nums.size();
  const long long INF = (long long)4e18;
  
  // dp[j][0/1] 表示已经选了 j 个子数组，0=不在子数组中，1=在子数组中
  // 初始化：除了 dp[0][0] = 0，其他都是 -INF
  vector<vector<long long>> dp(k + 1, vector<long long>(2, -INF));
  dp[0][0] = 0;
  
  for (int i = 0; i < n; ++i) {
    // 倒序遍历 j，避免重复计算
    for (int j = min(i + 1, k); j >= 1; --j) {
      // 第 j 个子数组的系数
      long long coeff = (j % 2 == 1) ? (k - j + 1) : -(k - j + 1);
      
      // 状态1：当前在子数组中
      // 可以从"之前就在子数组中"延续，或"开始新子数组"
      long long startNew = dp[j - 1][0] + coeff * nums[i];  // 开始第j个子数组
      long long continueSub = (dp[j][1] == -INF) ? -INF : dp[j][1] + coeff * nums[i];  // 延续
      dp[j][1] = max(startNew, continueSub);
      
      // 状态0：当前不在子数组中
      // 可以从"之前就不在"或"之前在某个子数组中（结束它）"转移
      dp[j][0] = max(dp[j][0], dp[j][1]);  // 结束当前子数组
    }
    // j=0 的情况：始终不在子数组中
    dp[0][0] = 0;  // 保持不变
  }
  
  // 答案可以是选了 k 个子数组且不在子数组中，或在子数组中但最终结束
  return max(dp[k][0], dp[k][1]);
}

MaximumStrengthOfKDisjointSubarraysSolution::MaximumStrengthOfKDisjointSubarraysSolution() {
  setMetaInfo({
    .id = 3077,
    .title = "Maximum Strength of K Disjoint Subarrays",
    .url = "https://leetcode.com/problems/maximum-strength-of-k-disjoint-subarrays/"
  });
  registerStrategy("DP", solution1);
}

long long MaximumStrengthOfKDisjointSubarraysSolution::maximumStrength(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3077
}  // namespace leetcode