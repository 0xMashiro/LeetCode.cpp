#include "leetcode/core.h"

namespace leetcode {
namespace problem_1800 {

using Func = std::function<int(vector<int>&)>;

class MaximumAscendingSubarraySumSolution : public SolutionBase<Func> {
 public:
  //! 1800. Maximum Ascending Subarray Sum
  //! https://leetcode.com/problems/maximum-ascending-subarray-sum/
  int maxAscendingSum(vector<int>& nums);

  MaximumAscendingSubarraySumSolution();
};

}  // namespace problem_1800
}  // namespace leetcode
