#include "leetcode/core.h"

namespace leetcode {
namespace problem_1053 {

using Func = std::function<vector<int>(vector<int>&)>;

/**
 * 1053. Previous Permutation With One Swap
 * https://leetcode.com/problems/previous-permutation-with-one-swap/
 * 
 * 给定一个正整数数组 arr（元素可能不唯一），返回字典序最大的、比 arr 小的排列，
 * 且只能通过一次交换得到。如果无法实现，则返回原数组。
 */
class PreviousPermutationWithOneSwapSolution : public SolutionBase<Func> {
 public:
  vector<int> prevPermOpt1(vector<int>& arr);

  PreviousPermutationWithOneSwapSolution();
};

}  // namespace problem_1053
}  // namespace leetcode