#include "leetcode/core.h"

namespace leetcode {
namespace problem_918 {

using Func = std::function<int(vector<int>&)>;

/**
 * 918. Maximum Sum Circular Subarray
 * https://leetcode.com/problems/maximum-sum-circular-subarray/
 * 
 * 环形子数组的最大和
 * 
 * 思路：分两种情况处理
 * 1. 普通情况：最大子数组不跨越数组边界 → 使用 Kadane 算法
 * 2. 环形情况：最大子数组跨越数组边界 → 等价于 总和 - 最小子数组和
 * 
 * 特殊情况：如果所有数都是负数，直接返回最大子数组和
 */
class MaximumSumCircularSubarraySolution : public SolutionBase<Func> {
 public:
  int maxSubarraySumCircular(vector<int>& nums);
  
  MaximumSumCircularSubarraySolution();
};

}  // namespace problem_918
}  // namespace leetcode
