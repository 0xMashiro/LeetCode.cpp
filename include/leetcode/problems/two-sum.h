
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1 {

using Func = std::function<vector<int>(vector<int>&, int)>;

class TwoSumSolution : public SolutionBase<Func> {
 public:
  //! 1. Two Sum
  //! https://leetcode.com/problems/two-sum/
  vector<int> twoSum(vector<int>& nums, int target);

  TwoSumSolution();
};

}  // namespace problem_1
}  // namespace leetcode
