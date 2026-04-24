#include "leetcode/core.h"

namespace leetcode {
namespace problem_1293 {

using Func = std::function<int(vector<vector<int>>&, int)>;

class ShortestPathInAGridWithObstaclesEliminationSolution : public SolutionBase<Func> {
 public:
  //! 1293. Shortest Path in a Grid with Obstacles Elimination
  //! https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
  int shortestPath(vector<vector<int>>& grid, int k);

  ShortestPathInAGridWithObstaclesEliminationSolution();
};

}  // namespace problem_1293
}  // namespace leetcode
