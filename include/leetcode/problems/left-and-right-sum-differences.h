#include "leetcode/core.h"

namespace leetcode {
namespace problem_2574 {

using Func = std::function<vector<int>(vector<int>&)>;

class LeftAndRightSumDifferencesSolution : public SolutionBase<Func> {
 public:
  //! 2574. Left and Right Sum Differences
  //! https://leetcode.com/problems/left-and-right-sum-differences/
  vector<int> leftRightDifference(vector<int>& nums);

  LeftAndRightSumDifferencesSolution();
};

}  // namespace problem_2574
}  // namespace leetcode
