#include "leetcode/core.h"

namespace leetcode {
namespace problem_1712 {

using Func = std::function<int(vector<int>&)>;

class WaysToSplitArrayIntoThreeSubarraysSolution : public SolutionBase<Func> {
 public:
  //! 1712. Ways to Split Array Into Three Subarrays
  //! https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/
  int waysToSplit(vector<int>& nums);

  WaysToSplitArrayIntoThreeSubarraysSolution();
};

}  // namespace problem_1712
}  // namespace leetcode
