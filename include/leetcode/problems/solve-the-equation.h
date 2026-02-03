#include "leetcode/core.h"

namespace leetcode {
namespace problem_640 {

using Func = std::function<string(string)>;

class SolveTheEquationSolution : public SolutionBase<Func> {
 public:
  //! 640. Solve the Equation
  //! https://leetcode.com/problems/solve-the-equation/
  string solveEquation(string equation);

  SolveTheEquationSolution();
};

}  // namespace problem_640
}  // namespace leetcode
