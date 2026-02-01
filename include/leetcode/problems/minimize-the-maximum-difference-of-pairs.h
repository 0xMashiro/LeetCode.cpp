
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2616 {

using Func = std::function<int(vector<int>&, int)>;

class MinimizeTheMaximumDifferenceOfPairsSolution : public SolutionBase<Func> {
 public:
  //! 2616. Minimize the Maximum Difference of Pairs
  //! https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/
  int minimizeMax(vector<int>& nums, int p);

  MinimizeTheMaximumDifferenceOfPairsSolution();
};

}  // namespace problem_2616
}  // namespace leetcode
