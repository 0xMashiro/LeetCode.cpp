#include "leetcode/core.h"

namespace leetcode {
namespace problem_1572 {

using Func = std::function<int(vector<vector<int>>&)>;

class MatrixDiagonalSumSolution : public SolutionBase<Func> {
 public:
  //! 1572. Matrix Diagonal Sum
  //! https://leetcode.com/problems/matrix-diagonal-sum/
  int diagonalSum(vector<vector<int>>& mat);

  MatrixDiagonalSumSolution();
};

}  // namespace problem_1572
}  // namespace leetcode
