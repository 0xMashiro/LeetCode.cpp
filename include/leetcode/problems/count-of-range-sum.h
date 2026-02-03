#include "leetcode/core.h"

namespace leetcode {
namespace problem_327 {

using Func = std::function<int(vector<int>&, int, int)>;

class CountOfRangeSumSolution : public SolutionBase<Func> {
 public:
  //! 327. Count of Range Sum
  //! https://leetcode.com/problems/count-of-range-sum/
  int countRangeSum(vector<int>& nums, int lower, int upper);

  CountOfRangeSumSolution();
};

}  // namespace problem_327
}  // namespace leetcode
