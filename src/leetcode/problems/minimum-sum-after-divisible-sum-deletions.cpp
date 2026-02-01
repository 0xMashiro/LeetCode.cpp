#include "leetcode/problems/minimum-sum-after-divisible-sum-deletions.h"

namespace leetcode {
namespace problem_3654 {

// 动态规划 + 前缀和
// dp[i] = 前 i 个元素的最小剩余和
// 对于位置 i：
// 1. 不删除：dp[i] = dp[i-1] + nums[i-1]
// 2. 删除子数组 [j, i-1]（如果和能被 k 整除）：dp[i] = dp[j]
// 使用前缀和：sum[j..i-1] = prefix[i] - prefix[j]
// 需要 (prefix[i] - prefix[j]) % k == 0，即 prefix[i] % k == prefix[j] % k
// 用哈希表记录每个 mod 对应的最小 dp 值
// 时间复杂度: O(n), 空间复杂度: O(k)
static long long solution(vector<int>& nums, int k) {
  const int n = nums.size();
  vector<long long> dp(n + 1, LLONG_MAX);
  dp[0] = 0;  // 前0个元素，剩余和为0
  
  // minDp[mod] = 前缀和模 k 等于 mod 时的最小 dp 值
  unordered_map<int, long long> minDp;
  minDp[0] = 0;  // prefix[0] = 0, dp[0] = 0
  
  long long prefix = 0;
  for (int i = 1; i <= n; ++i) {
    prefix += nums[i - 1];
    int mod = ((prefix % k) + k) % k;
    
    // 情况1：不删除以 i-1 结尾的子数组，保留 nums[i-1]
    dp[i] = dp[i - 1] + nums[i - 1];
    
    // 情况2：删除某个以 i-1 结尾且和能被 k 整除的子数组
    // 需要找到 j 满足 prefix[j] % k == prefix[i] % k
    if (minDp.find(mod) != minDp.end()) {
      dp[i] = min(dp[i], minDp[mod]);
    }
    
    // 更新 minDp[mod]：当前前缀和 mod 对应的最小 dp 值
    if (minDp.find(mod) == minDp.end()) {
      minDp[mod] = dp[i];
    } else {
      minDp[mod] = min(minDp[mod], dp[i]);
    }
  }
  
  return dp[n];
}

MinimumSumAfterDivisibleSumDeletionsSolution::MinimumSumAfterDivisibleSumDeletionsSolution() {
  setMetaInfo({.id = 3654,
               .title = "Minimum Sum After Divisible Sum Deletions",
               .url = "https://leetcode.com/problems/minimum-sum-after-divisible-sum-deletions/"});
  registerStrategy("DP + Prefix Sum", solution);
}

long long MinimumSumAfterDivisibleSumDeletionsSolution::minArraySum(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3654
}  // namespace leetcode
