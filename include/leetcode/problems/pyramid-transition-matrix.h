#include "leetcode/core.h"

namespace leetcode {
namespace problem_756 {

using Func = std::function<bool(string, vector<string>&)>;

class PyramidTransitionMatrixSolution : public SolutionBase<Func> {
 public:
  //! 756. Pyramid Transition Matrix
  //! https://leetcode.com/problems/pyramid-transition-matrix/
  bool pyramidTransition(string bottom, vector<string>& allowed);

  PyramidTransitionMatrixSolution();
};

}  // namespace problem_756
}  // namespace leetcode