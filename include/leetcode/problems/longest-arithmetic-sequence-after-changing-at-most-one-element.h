#include "leetcode/core.h"

namespace leetcode {
namespace problem_3872 {

using Func = std::function<int(vector<int>&)>;

class LongestArithmeticSequenceAfterChangingAtMostOneElementSolution : public SolutionBase<Func> {
 public:
  //! 3872. Longest Arithmetic Sequence After Changing At Most One Element
  //! https://leetcode.com/problems/longest-arithmetic-sequence-after-changing-at-most-one-element/
  int longestArithmetic(vector<int>& nums);

  LongestArithmeticSequenceAfterChangingAtMostOneElementSolution();
};

}  // namespace problem_3872
}  // namespace leetcode
