#include "leetcode/core.h"

namespace leetcode {
namespace problem_3650 {

using Func = std::function<int(int, vector<vector<int>>&)>;

class MinimumCostPathWithEdgeReversalsSolution : public SolutionBase<Func> {
 public:
  //! 3650. Minimum Cost Path with Edge Reversals
  //! https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/
  int minCost(int n, vector<vector<int>>& edges);

  MinimumCostPathWithEdgeReversalsSolution();
};

}  // namespace problem_3650
}  // namespace leetcode