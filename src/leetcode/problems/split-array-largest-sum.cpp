#include "leetcode/problems/split-array-largest-sum.h"

namespace leetcode {
namespace problem_410 {

// 辅助函数：判断是否可以在最大和限制为 maxSum 的情况下，将数组分成不超过 k 组
static bool canSplit(const vector<int>& nums, int k, long long maxSum) {
  int groups = 1;  // 当前分组数
  long long currentSum = 0;  // 当前组的和
  
  for (int num : nums) {
    // 如果单个元素就超过限制，无法分割
    if (num > maxSum) return false;
    
    if (currentSum + num <= maxSum) {
      // 当前元素可以放入当前组
      currentSum += num;
    } else {
      // 需要开启新的一组
      groups++;
      currentSum = num;
      if (groups > k) return false;
    }
  }
  return true;
}

// 二分查找解法
// 时间复杂度: O(n * log(sum)), 空间复杂度: O(1)
static int solution1(vector<int>& nums, int k) {
  long long left = 0;   // 最大元素
  long long right = 0;  // 数组总和
  
  for (int num : nums) {
    left = max(left, (long long)num);
    right += num;
  }
  
  // 二分查找最小化的最大和
  long long result = right;
  while (left <= right) {
    long long mid = left + (right - left) / 2;
    
    if (canSplit(nums, k, mid)) {
      // 可以分割，尝试更小的值
      result = mid;
      right = mid - 1;
    } else {
      // 无法分割，需要更大的值
      left = mid + 1;
    }
  }
  
  return (int)result;
}

SplitArrayLargestSumSolution::SplitArrayLargestSumSolution() {
  setMetaInfo({.id = 410,
               .title = "Split Array Largest Sum",
               .url = "https://leetcode.com/problems/split-array-largest-sum/"});
  registerStrategy("Binary Search", solution1);
}

int SplitArrayLargestSumSolution::splitArray(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_410
}  // namespace leetcode
