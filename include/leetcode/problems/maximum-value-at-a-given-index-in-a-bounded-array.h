
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1802 {

using Func = std::function<int(int, int, int)>;

class MaximumValueAtAGivenIndexInABoundedArraySolution : public SolutionBase<Func> {
 public:
  //! 1802. Maximum Value at a Given Index in a Bounded Array
  //! https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/
  int maxValue(int n, int index, int maxSum);

  MaximumValueAtAGivenIndexInABoundedArraySolution();
};

}  // namespace problem_1802
}  // namespace leetcode
