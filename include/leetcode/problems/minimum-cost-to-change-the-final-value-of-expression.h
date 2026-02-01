
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1896 {

using Func = std::function<int(string)>;

class MinimumCostToChangeTheFinalValueOfExpressionSolution : public SolutionBase<Func> {
 public:
  //! 1896. Minimum Cost to Change the Final Value of Expression
  //! https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/
  int minOperationsToFlip(string expression);

  MinimumCostToChangeTheFinalValueOfExpressionSolution();
};

}  // namespace problem_1896
}  // namespace leetcode
