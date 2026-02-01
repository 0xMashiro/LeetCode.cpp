
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1582 {

using Func = std::function<int(vector<vector<int>>&)>;

class SpecialPositionsInABinaryMatrixSolution : public SolutionBase<Func> {
 public:
  //! 1582. Special Positions in a Binary Matrix
  //! https://leetcode.com/problems/special-positions-in-a-binary-matrix/
  int numSpecial(vector<vector<int>>& mat);

  SpecialPositionsInABinaryMatrixSolution();
};

}  // namespace problem_1582
}  // namespace leetcode
