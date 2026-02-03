#include "leetcode/core.h"

namespace leetcode {
namespace problem_695 {

using Func = std::function<int(vector<vector<int>>&)>;

class MaxAreaOfIslandSolution : public SolutionBase<Func> {
 public:
  int maxAreaOfIsland(vector<vector<int>>& grid);
  MaxAreaOfIslandSolution();
};

}  // namespace problem_695
}  // namespace leetcode
