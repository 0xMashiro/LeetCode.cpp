#include "leetcode/core.h"

namespace leetcode {
namespace problem_1782 {

using Func = std::function<vector<int>(int, vector<vector<int>>&, vector<int>&)>;

class CountPairsOfNodesSolution : public SolutionBase<Func> {
 public:
  //! 1782. Count Pairs Of Nodes
  //! https://leetcode.com/problems/count-pairs-of-nodes/
  vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries);

  CountPairsOfNodesSolution();
};

}  // namespace problem_1782
}  // namespace leetcode
