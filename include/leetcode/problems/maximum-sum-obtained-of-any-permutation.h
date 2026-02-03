
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1589 {

using Func = std::function<int(vector<int>&, vector<vector<int>>&)>;

class MaximumSumObtainedOfAnyPermutationSolution : public SolutionBase<Func> {
 public:
  //! 1589. Maximum Sum Obtained of Any Permutation
  //! https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/
  int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests);

  MaximumSumObtainedOfAnyPermutationSolution();
};

}  // namespace problem_1589
}  // namespace leetcode
