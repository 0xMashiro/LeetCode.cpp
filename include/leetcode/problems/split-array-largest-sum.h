#include "leetcode/core.h"

namespace leetcode {
namespace problem_410 {

using Func = std::function<int(vector<int>&, int)>;

class SplitArrayLargestSumSolution : public SolutionBase<Func> {
 public:
  //! 410. Split Array Largest Sum
  //! https://leetcode.com/problems/split-array-largest-sum/
  int splitArray(vector<int>& nums, int k);

  SplitArrayLargestSumSolution();
};

}  // namespace problem_410
}  // namespace leetcode
