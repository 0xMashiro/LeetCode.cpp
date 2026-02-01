#include "leetcode/core.h"

namespace leetcode {
namespace problem_396 {

using Func = std::function<int(vector<int>&)>;

class RotateFunctionSolution : public SolutionBase<Func> {
 public:
  //! 396. Rotate Function
  //! https://leetcode.com/problems/rotate-function/
  int maxRotateFunction(vector<int>& nums);

  RotateFunctionSolution();
};

}  // namespace problem_396
}  // namespace leetcode
