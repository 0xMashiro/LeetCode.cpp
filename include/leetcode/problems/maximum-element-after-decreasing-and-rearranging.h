#include "leetcode/core.h"

namespace leetcode {
namespace problem_1846 {

using Func = std::function<int(std::vector<int>&)>;

class MaximumElementAfterDecreasingAndRearrangingSolution : public SolutionBase<Func> {
 public:
  //! 1846. Maximum Element After Decreasing and Rearranging
  //! https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/
  int maximumElementAfterDecrementingAndRearranging(std::vector<int>& arr);

  MaximumElementAfterDecreasingAndRearrangingSolution();
};

}  // namespace problem_1846
}  // namespace leetcode
