
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1514 {

using Func = std::function<double(int, vector<vector<int>>&, vector<double>&, int, int)>;

class PathWithMaximumProbabilitySolution : public SolutionBase<Func> {
 public:
  //! 1514. Path with Maximum Probability
  //! https://leetcode.com/problems/path-with-maximum-probability/
  double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node);

  PathWithMaximumProbabilitySolution();
};

}  // namespace problem_1514
}  // namespace leetcode
