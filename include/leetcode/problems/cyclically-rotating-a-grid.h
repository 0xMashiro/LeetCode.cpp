#include "leetcode/core.h"

namespace leetcode {
namespace problem_1914 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&, int)>;

class CyclicallyRotatingAGridSolution : public SolutionBase<Func> {
 public:
  //! 1914. Cyclically Rotating a Grid
  //! https://leetcode.com/problems/cyclically-rotating-a-grid/
  vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k);

  CyclicallyRotatingAGridSolution();
};

}  // namespace problem_1914
}  // namespace leetcode
