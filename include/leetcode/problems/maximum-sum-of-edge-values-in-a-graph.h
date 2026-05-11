#include "leetcode/core.h"

namespace leetcode {
namespace problem_3547 {

using Func = std::function<long long(int, vector<vector<int>>&)>;

class MaximumSumOfEdgeValuesInAGraphSolution : public SolutionBase<Func> {
 public:
  //! 3547. Maximum Sum of Edge Values in a Graph
  //! https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/
  long long maxScore(int n, vector<vector<int>>& edges);

  MaximumSumOfEdgeValuesInAGraphSolution();
};

}  // namespace problem_3547
}  // namespace leetcode
