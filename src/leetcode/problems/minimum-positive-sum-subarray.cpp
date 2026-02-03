#include "leetcode/problems/minimum-positive-sum-subarray.h"

namespace leetcode {
namespace problem_3364 {

// 暴力枚举：枚举所有长度在 [l, r] 范围内的子数组
// 时间复杂度: O(n² × (r-l)), 空间复杂度: O(1)
static int solution1(vector<int>& nums, int l, int r) {
  const int n = nums.size();
  int minSum = INT_MAX;
  
  // 枚举子数组的起始位置
  for (int i = 0; i < n; ++i) {
    // 枚举子数组的长度，从 l 到 r
    for (int len = l; len <= r && i + len <= n; ++len) {
      int sum = 0;
      // 计算子数组 [i, i+len-1] 的和
      for (int k = i; k < i + len; ++k) {
        sum += nums[k];
      }
      // 如果和大于 0，更新最小正和
      if (sum > 0 && sum < minSum) {
        minSum = sum;
      }
    }
  }
  
  return (minSum == INT_MAX) ? -1 : minSum;
}

// 优化版本：使用前缀和加速子数组和的计算
// 时间复杂度: O(n × (r-l)), 空间复杂度: O(n)
static int solution2(vector<int>& nums, int l, int r) {
  const int n = nums.size();
  
  // 计算前缀和：prefix[i] 表示 nums[0..i-1] 的和
  vector<int> prefix(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + nums[i];
  }
  
  int minSum = INT_MAX;
  
  // 枚举子数组的起始位置
  for (int i = 0; i < n; ++i) {
    // 枚举子数组的长度，从 l 到 r
    for (int len = l; len <= r && i + len <= n; ++len) {
      // 使用前缀和快速计算子数组 [i, i+len-1] 的和
      int sum = prefix[i + len] - prefix[i];
      // 如果和大于 0，更新最小正和
      if (sum > 0 && sum < minSum) {
        minSum = sum;
      }
    }
  }
  
  return (minSum == INT_MAX) ? -1 : minSum;
}

MinimumPositiveSumSubarraySolution::MinimumPositiveSumSubarraySolution() {
  setMetaInfo({.id = 3364,
               .title = "Minimum Positive Sum Subarray",
               .url = "https://leetcode.com/problems/minimum-positive-sum-subarray/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Prefix Sum Optimized", solution2);
}

int MinimumPositiveSumSubarraySolution::minimumSumSubarray(vector<int>& nums, int l, int r) {
  return getSolution()(nums, l, r);
}

}  // namespace problem_3364
}  // namespace leetcode
