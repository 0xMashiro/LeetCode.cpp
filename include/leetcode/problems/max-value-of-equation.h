#include "leetcode/core.h"

namespace leetcode {
namespace problem_1499 {

using Func = std::function<int(vector<vector<int>>&, int)>;

class MaxValueOfEquationSolution : public SolutionBase<Func> {
 public:
  //! 1499. Max Value of Equation
  //! https://leetcode.com/problems/max-value-of-equation/
  int findMaxValueOfEquation(vector<vector<int>>& points, int k);

  MaxValueOfEquationSolution();
};

}  // namespace problem_1499
}  // namespace leetcode
