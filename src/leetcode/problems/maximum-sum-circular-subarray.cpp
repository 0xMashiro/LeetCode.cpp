#include "leetcode/problems/maximum-sum-circular-subarray.h"

namespace leetcode {
namespace problem_918 {

/**
 * Kadane算法实现
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 * 
 * 核心思想：
 * - 对于普通最大子数组和：dp[i] = max(nums[i], dp[i-1] + nums[i])
 * - 对于环形情况：最大环形和 = 总和 - 最小子数组和
 * - 特殊情况处理：如果全是负数，total - minSum = 0，这是不合法的
 *   所以当 maxSum < 0 时，直接返回 maxSum
 */
static int kadaneSolution(vector<int>& nums) {
  const int n = nums.size();
  
  // 用 Kadane 算法计算最大子数组和
  int maxSum = nums[0];
  int currentMax = nums[0];
  
  // 用 Kadane 算法计算最小子数组和（用于环形情况）
  int minSum = nums[0];
  int currentMin = nums[0];
  
  // 计算总和
  int total = nums[0];
  
  for (int i = 1; i < n; ++i) {
    // 计算以当前元素结尾的最大子数组和
    currentMax = max(nums[i], currentMax + nums[i]);
    maxSum = max(maxSum, currentMax);
    
    // 计算以当前元素结尾的最小子数组和
    currentMin = min(nums[i], currentMin + nums[i]);
    minSum = min(minSum, currentMin);
    
    total += nums[i];
  }
  
  // 如果所有数都是负数，maxSum < 0，直接返回 maxSum
  // 因为此时 total - minSum = 0（空子数组），但题目要求非空子数组
  if (maxSum < 0) {
    return maxSum;
  }
  
  // 返回两种情况的最大值
  // 1. maxSum: 普通情况（不跨越边界）
  // 2. total - minSum: 环形情况（跨越边界）
  return max(maxSum, total - minSum);
}

MaximumSumCircularSubarraySolution::MaximumSumCircularSubarraySolution() {
  setMetaInfo({
    .id = 918,
    .title = "Maximum Sum Circular Subarray",
    .url = "https://leetcode.com/problems/maximum-sum-circular-subarray/"
  });
  registerStrategy("Kadane Algorithm", kadaneSolution);
}

int MaximumSumCircularSubarraySolution::maxSubarraySumCircular(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_918
}  // namespace leetcode
