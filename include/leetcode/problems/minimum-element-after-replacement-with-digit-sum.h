#include "leetcode/core.h"

namespace leetcode {
namespace problem_3300 {

using Func = std::function<int(vector<int>&)>;

class MinimumElementAfterReplacementWithDigitSumSolution : public SolutionBase<Func> {
 public:
  //! 3300. Minimum Element After Replacement With Digit Sum
  //! https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/
  int minElement(vector<int>& nums);

  MinimumElementAfterReplacementWithDigitSumSolution();
};

}  // namespace problem_3300
}  // namespace leetcode
