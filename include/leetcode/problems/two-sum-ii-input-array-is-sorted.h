
#include "leetcode/core.h"

namespace leetcode {
namespace problem_167 {

using Func = std::function<vector<int>(vector<int>&, int)>;

/**
 * 167. Two Sum II - Input Array Is Sorted
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * 给定一个已按非递减顺序排序的数组，找出和为目标值的两个数。
 * 返回的索引需要加 1（1-indexed）。
 *
 * 解法：
 * 1. 双指针：利用数组已排序的特性，左右指针向中间移动
 *    时间复杂度 O(n)，空间复杂度 O(1)
 */
class TwoSumIiInputArrayIsSortedSolution : public SolutionBase<Func> {
 public:
  vector<int> twoSum(vector<int>& numbers, int target);

  TwoSumIiInputArrayIsSortedSolution();
};

}  // namespace problem_167
}  // namespace leetcode
