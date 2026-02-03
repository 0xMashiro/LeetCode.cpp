#include "leetcode/core.h"

namespace leetcode {
namespace problem_2326 {

using Func = std::function<vector<vector<int>>(int, int, ListNode*)>;

class SpiralMatrixIvSolution : public SolutionBase<Func> {
 public:
  //! 2326. Spiral Matrix IV
  //! https://leetcode.com/problems/spiral-matrix-iv/
  vector<vector<int>> spiralMatrix(int m, int n, ListNode* head);

  SpiralMatrixIvSolution();
};

}  // namespace problem_2326
}  // namespace leetcode
