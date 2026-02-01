#include "leetcode/core.h"

namespace leetcode {
namespace problem_63 {

using Func = std::function<int(vector<vector<int>>&)>;

class UniquePathsIiSolution : public SolutionBase<Func> {
 public:
  //! 63. Unique Paths II
  //! https://leetcode.com/problems/unique-paths-ii/
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);

  UniquePathsIiSolution();
};

}  // namespace problem_63
}  // namespace leetcode
