#include "leetcode/core.h"

namespace leetcode {
namespace problem_1519 {

using Func = std::function<vector<int>(int, vector<vector<int>>&, string)>;

class NumberOfNodesInTheSubTreeWithTheSameLabelSolution : public SolutionBase<Func> {
 public:
  vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels);

  NumberOfNodesInTheSubTreeWithTheSameLabelSolution();
};

}  // namespace problem_1519
}  // namespace leetcode
