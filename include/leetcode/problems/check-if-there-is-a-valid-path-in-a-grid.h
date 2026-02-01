#include "leetcode/core.h"

namespace leetcode {
namespace problem_1391 {

using Func = std::function<bool(vector<vector<int>>&)>;

class CheckIfThereIsAValidPathInAGridSolution : public SolutionBase<Func> {
 public:
  //! 1391. Check if There is a Valid Path in a Grid
  //! https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/
  bool hasValidPath(vector<vector<int>>& grid);

  CheckIfThereIsAValidPathInAGridSolution();
};

}  // namespace problem_1391
}  // namespace leetcode
