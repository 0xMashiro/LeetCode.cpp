#include "leetcode/problems/maximum-ascending-subarray-sum.h"

namespace leetcode {
namespace problem_1800 {

// 一次遍历，维护当前升序子数组的和
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  int max_sum = nums[0];
  int current_sum = nums[0];
  
  for (int i = 1; i < n; ++i) {
    if (nums[i] > nums[i - 1]) {
      // 递增继续，加入当前子数组
      current_sum += nums[i];
    } else {
      // 递增中断，从当前元素重新开始
      current_sum = nums[i];
    }
    max_sum = max(max_sum, current_sum);
  }
  
  return max_sum;
}

MaximumAscendingSubarraySumSolution::MaximumAscendingSubarraySumSolution() {
  setMetaInfo({.id = 1800,
               .title = "Maximum Ascending Subarray Sum",
               .url = "https://leetcode.com/problems/maximum-ascending-subarray-sum/"});
  registerStrategy("Linear Scan", solution1);
}

int MaximumAscendingSubarraySumSolution::maxAscendingSum(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1800
}  // namespace leetcode
