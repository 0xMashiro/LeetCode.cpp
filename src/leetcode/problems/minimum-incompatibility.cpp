
#include "leetcode/problems/minimum-incompatibility.h"

namespace leetcode {
namespace problem_1681 {

// 状态压缩动态规划
// 时间复杂度: O(2^n * C(n, m)), 空间复杂度: O(2^n)
// 其中 n = nums.size(), m = n / k
static int solution1(vector<int>& nums, int k) {
  int n = nums.size();
  int m = n / k;  // 每个子集的大小
  
  // 如果每个子集只有一个元素，不兼容性为0
  if (m == 1) return 0;
  
  // 统计每个数字的出现次数
  vector<int> freq(n + 1, 0);
  for (int num : nums) {
    freq[num]++;
    // 如果某个数字出现次数超过k，不可能分配
    if (freq[num] > k) return -1;
  }
  
  // 预处理所有合法的子集（大小为m且无重复元素）
  // value[mask] = 子集的不兼容性，如果不合法则为-1
  vector<int> value(1 << n, -1);
  
  for (int mask = 0; mask < (1 << n); ++mask) {
    // 只考虑大小为m的子集
    if (__builtin_popcount(mask) != m) continue;
    
    // 检查是否有重复元素
    vector<int> subset;
    bool valid = true;
    vector<bool> seen(n + 1, false);
    
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        if (seen[nums[i]]) {
          valid = false;
          break;
        }
        seen[nums[i]] = true;
        subset.push_back(nums[i]);
      }
    }
    
    if (!valid) continue;
    
    // 计算不兼容性
    int minVal = *min_element(subset.begin(), subset.end());
    int maxVal = *max_element(subset.begin(), subset.end());
    value[mask] = maxVal - minVal;
  }
  
  // 状态压缩DP
  // dp[mask] 表示已选择mask对应元素后的最小不兼容性之和
  const int INF = 1e9;
  vector<int> dp(1 << n, INF);
  dp[0] = 0;
  
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (dp[mask] == INF) continue;
    
    // 枚举所有合法的子集
    for (int sub = 0; sub < (1 << n); ++sub) {
      // 子集必须与mask无交集，且大小为m，且合法
      if ((mask & sub) != 0) continue;
      if (__builtin_popcount(sub) != m) continue;
      if (value[sub] == -1) continue;
      
      int newMask = mask | sub;
      dp[newMask] = min(dp[newMask], dp[mask] + value[sub]);
    }
  }
  
  return dp[(1 << n) - 1] == INF ? -1 : dp[(1 << n) - 1];
}

// 优化版本：只枚举未使用的元素的子集
static int solution2(vector<int>& nums, int k) {
  int n = nums.size();
  int m = n / k;
  
  if (m == 1) return 0;
  
  // 快速检查
  vector<int> freq(n + 1, 0);
  for (int num : nums) {
    if (++freq[num] > k) return -1;
  }
  
  // 预处理合法子集
  vector<int> value(1 << n, -1);
  
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (__builtin_popcount(mask) != m) continue;
    
    int minVal = n + 1, maxVal = 0;
    vector<bool> seen(n + 1, false);
    bool valid = true;
    
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        if (seen[nums[i]]) {
          valid = false;
          break;
        }
        seen[nums[i]] = true;
        minVal = min(minVal, nums[i]);
        maxVal = max(maxVal, nums[i]);
      }
    }
    
    if (valid) value[mask] = maxVal - minVal;
  }
  
  const int INF = 1e9;
  vector<int> dp(1 << n, INF);
  dp[0] = 0;
  
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (dp[mask] == INF) continue;
    
    // 只枚举未使用元素的子集
    int remaining = ((1 << n) - 1) ^ mask;
    
    // 枚举remaining的子集
    for (int sub = remaining; sub > 0; sub = (sub - 1) & remaining) {
      if (__builtin_popcount(sub) != m) continue;
      if (value[sub] == -1) continue;
      
      dp[mask | sub] = min(dp[mask | sub], dp[mask] + value[sub]);
    }
  }
  
  return dp[(1 << n) - 1] == INF ? -1 : dp[(1 << n) - 1];
}

MinimumIncompatibilitySolution::MinimumIncompatibilitySolution() {
  setMetaInfo({.id = 1681,
               .title = "Minimum Incompatibility",
               .url = "https://leetcode.com/problems/minimum-incompatibility/"});
  registerStrategy("DP Basic", solution1);
  registerStrategy("DP Optimized", solution2);
}

int MinimumIncompatibilitySolution::minimumIncompatibility(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_1681
}  // namespace leetcode
