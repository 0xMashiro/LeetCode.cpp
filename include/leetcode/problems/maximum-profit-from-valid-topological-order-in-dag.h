#include "leetcode/core.h"

namespace leetcode {
namespace problem_3530 {

using Func = std::function<int(int, vector<vector<int>>&, vector<int>&)>;

class MaximumProfitFromValidTopologicalOrderInDagSolution : public SolutionBase<Func> {
 public:
  //! 3530. Maximum Profit from Valid Topological Order in DAG
  //! https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/
  int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score);

  MaximumProfitFromValidTopologicalOrderInDagSolution();
};

}  // namespace problem_3530
}  // namespace leetcode
