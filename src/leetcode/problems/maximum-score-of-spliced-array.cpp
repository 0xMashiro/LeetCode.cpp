#include "leetcode/problems/maximum-score-of-spliced-array.h"

namespace leetcode {
namespace problem_2321 {

/**
 * 计算最大子数组和（Kadane算法）
 * 时间复杂度：O(n)，空间复杂度：O(1)
 */
static long long maxSubarraySum(const vector<int>& diff) {
  long long maxSum = 0;  // 可以选择不交换，所以最小是0
  long long currentSum = 0;
  
  for (int val : diff) {
    currentSum = max((long long)val, currentSum + val);
    maxSum = max(maxSum, currentSum);
  }
  
  return maxSum;
}

/**
 * 解决方案
 * 1. 计算两个数组的总和
 * 2. 计算 diff = nums2 - nums1
 * 3. 求 diff 的最大子数组和，可使 nums1 最大
 * 4. 求 -diff 的最大子数组和，可使 nums2 最大
 * 5. 取两种情况的最大值
 */
static int solution(vector<int>& nums1, vector<int>& nums2) {
  const int n = nums1.size();
  
  long long sum1 = 0, sum2 = 0;
  vector<int> diff(n);
  
  for (int i = 0; i < n; ++i) {
    sum1 += nums1[i];
    sum2 += nums2[i];
    diff[i] = nums2[i] - nums1[i];
  }
  
  // 计算 diff 的最大子数组和（让 nums1 变大）
  long long maxGain1 = maxSubarraySum(diff);
  
  // 计算 -diff 的最大子数组和（让 nums2 变大）
  vector<int> negDiff(n);
  for (int i = 0; i < n; ++i) {
    negDiff[i] = -diff[i];
  }
  long long maxGain2 = maxSubarraySum(negDiff);
  
  // 返回最大分数
  return (int)max(sum1 + maxGain1, sum2 + maxGain2);
}

MaximumScoreOfSplicedArraySolution::MaximumScoreOfSplicedArraySolution() {
  setMetaInfo({.id = 2321,
               .title = "Maximum Score Of Spliced Array",
               .url = "https://leetcode.com/problems/maximum-score-of-spliced-array/"});
  registerStrategy("Kadane Algorithm", solution);
}

int MaximumScoreOfSplicedArraySolution::maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
  return getSolution()(nums1, nums2);
}

}  // namespace problem_2321
}  // namespace leetcode
