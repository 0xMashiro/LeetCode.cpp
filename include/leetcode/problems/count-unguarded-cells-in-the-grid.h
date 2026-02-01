#include "leetcode/core.h"

namespace leetcode {
namespace problem_2257 {

using Func = std::function<int(int, int, vector<vector<int>>&, vector<vector<int>>&)>;

class CountUnguardedCellsInTheGridSolution : public SolutionBase<Func> {
 public:
  //! 2257. Count Unguarded Cells in the Grid
  //! https://leetcode.com/problems/count-unguarded-cells-in-the-grid/
  int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls);

  CountUnguardedCellsInTheGridSolution();
};

}  // namespace problem_2257
}  // namespace leetcode
