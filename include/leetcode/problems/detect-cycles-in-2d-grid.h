
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1559 {

using Func = std::function<bool(vector<vector<char>>&)>;

class DetectCyclesIn2dGridSolution : public SolutionBase<Func> {
 public:
  //! 1559. Detect Cycles in 2D Grid
  //! https://leetcode.com/problems/detect-cycles-in-2d-grid/
  bool containsCycle(vector<vector<char>>& grid);

  DetectCyclesIn2dGridSolution();
};

}  // namespace problem_1559
}  // namespace leetcode
