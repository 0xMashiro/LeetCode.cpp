
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2087 {

using Func = std::function<int(vector<int>&, vector<int>&, vector<int>&, vector<int>&)>;

class MinimumCostHomecomingOfARobotInAGridSolution : public SolutionBase<Func> {
 public:
  //! 2087. Minimum Cost Homecoming of a Robot in a Grid
  //! https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/
  int minCost(vector<int>& startPos, vector<int>& homePos, 
              vector<int>& rowCosts, vector<int>& colCosts);

  MinimumCostHomecomingOfARobotInAGridSolution();
};

}  // namespace problem_2087
}  // namespace leetcode
