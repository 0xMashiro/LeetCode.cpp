#include "leetcode/core.h"

namespace leetcode {
namespace problem_3559 {

using Func = std::function<vector<int>(vector<vector<int>>&, vector<vector<int>>&)>;

class NumberOfWaysToAssignEdgeWeightsIiSolution : public SolutionBase<Func> {
 public:
  //! 3559. Number of Ways to Assign Edge Weights II
  //! https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/
  vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries);

  NumberOfWaysToAssignEdgeWeightsIiSolution();
};

}  // namespace problem_3559
}  // namespace leetcode
