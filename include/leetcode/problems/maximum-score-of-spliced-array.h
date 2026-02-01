#include "leetcode/core.h"

namespace leetcode {
namespace problem_2321 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

/**
 * 2321. Maximum Score Of Spliced Array
 * https://leetcode.com/problems/maximum-score-of-spliced-array/
 *
 * 思路：最大子数组和（Kadane算法）
 * 定义 diff[i] = nums2[i] - nums1[i]
 * - 交换子数组使 nums1 最大：sum(nums1) + max_subarray_sum(diff)
 * - 交换子数组使 nums2 最大：sum(nums2) + max_subarray_sum(-diff)
 * 时间复杂度：O(n)，空间复杂度：O(1)
 */
class MaximumScoreOfSplicedArraySolution : public SolutionBase<Func> {
 public:
  int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2);

  MaximumScoreOfSplicedArraySolution();
};

}  // namespace problem_2321
}  // namespace leetcode
