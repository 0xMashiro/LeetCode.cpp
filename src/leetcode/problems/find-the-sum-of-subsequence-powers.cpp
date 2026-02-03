#include "leetcode/problems/find-the-sum-of-subsequence-powers.h"

namespace leetcode {
namespace problem_3098 {

static const int MOD = 1e9 + 7;

// 计算最小差 >= d 的长度为 k 的子序列数量
static long long calc(const vector<int>& nums, int k, int d) {
  int n = nums.size();
  // dp[i][j]: 以第 i 个元素结尾，选了 j+1 个元素，相邻差都 >= d 的方案数
  vector<vector<long long>> dp(n, vector<long long>(k, 0));
  
  // 初始化：只选一个元素
  for (int i = 0; i < n; i++) {
    dp[i][0] = 1;
  }
  
  // 枚举子序列长度
  for (int j = 1; j < k; j++) {
    // 计算前缀和，用于快速查询
    vector<long long> prefix(n);
    prefix[0] = dp[0][j - 1];
    for (int i = 1; i < n; i++) {
      prefix[i] = (prefix[i - 1] + dp[i][j - 1]) % MOD;
    }
    
    // 计算 dp[i][j]
    for (int i = 0; i < n; i++) {
      // 找最大的 t < i 使得 nums[i] - nums[t] >= d，即 nums[t] <= nums[i] - d
      int target = nums[i] - d;
      // upper_bound 找第一个 > target 的位置
      auto it = upper_bound(nums.begin(), nums.begin() + i, target);
      if (it != nums.begin()) {
        int idx = static_cast<int>(it - nums.begin()) - 1;
        dp[i][j] = prefix[idx];
      }
    }
  }
  
  // 累加以每个元素结尾的方案数
  long long res = 0;
  for (int i = 0; i < n; i++) {
    res = (res + dp[i][k - 1]) % MOD;
  }
  return res;
}

// 主解法
static int solution(vector<int>& nums, int k) {
  int n = nums.size();
  sort(nums.begin(), nums.end());
  
  // 收集所有正差值
  vector<int> diffs;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (nums[j] - nums[i] > 0) {
        diffs.push_back(nums[j] - nums[i]);
      }
    }
  }
  
  // 如果没有正差值，说明所有元素相同，答案为 0
  if (diffs.empty()) {
    return 0;
  }
  
  // 排序并去重
  sort(diffs.begin(), diffs.end());
  diffs.erase(unique(diffs.begin(), diffs.end()), diffs.end());
  
  // 计算答案
  // ans = sum_{i} (diffs[i] - diffs[i-1]) * f(diffs[i])
  // 其中 diffs[-1] = 0，f(d) 表示最小差 >= d 的子序列数量
  long long ans = 0;
  int prev_d = 0;
  
  for (int d : diffs) {
    long long f = calc(nums, k, d);
    ans = (ans + static_cast<long long>(d - prev_d) * f) % MOD;
    prev_d = d;
  }
  
  return static_cast<int>(ans);
}

FindTheSumOfSubsequencePowersSolution::FindTheSumOfSubsequencePowersSolution() {
  setMetaInfo({.id = 3098,
               .title = "Find the Sum of Subsequence Powers",
               .url = "https://leetcode.com/problems/find-the-sum-of-subsequence-powers/"});
  registerStrategy("DP + Enumeration", solution);
}

int FindTheSumOfSubsequencePowersSolution::sumOfPowers(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3098
}  // namespace leetcode
