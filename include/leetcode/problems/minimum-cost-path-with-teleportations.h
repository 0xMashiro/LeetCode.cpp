#include "leetcode/core.h"

namespace leetcode {
namespace problem_3651 {

using Func = std::function<int(vector<vector<int>>&, int)>;

class MinimumCostPathWithTeleportationsSolution : public SolutionBase<Func> {
 public:
  int minCost(vector<vector<int>>& grid, int k);
  MinimumCostPathWithTeleportationsSolution();
};

}  // namespace problem_3651
}  // namespace leetcode
