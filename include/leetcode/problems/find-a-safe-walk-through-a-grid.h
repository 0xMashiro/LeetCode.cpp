#include "leetcode/core.h"

namespace leetcode {
namespace problem_3286 {

using Func = std::function<bool(vector<vector<int>>&, int)>;

class FindASafeWalkThroughAGridSolution : public SolutionBase<Func> {
 public:
  //! 3286. Find a Safe Walk Through a Grid
  //! https://leetcode.com/problems/find-a-safe-walk-through-a-grid/
  bool findSafeWalk(vector<vector<int>>& grid, int health);

  FindASafeWalkThroughAGridSolution();
};

}  // namespace problem_3286
}  // namespace leetcode
