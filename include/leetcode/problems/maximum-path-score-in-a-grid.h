#include "leetcode/core.h"

namespace leetcode {
namespace problem_3742 {

class Solution {
 public:
  int maxPathScore(vector<vector<int>>& grid, int k);
};

using Func = std::function<int(vector<vector<int>>&, int)>;

class MaximumPathScoreInAGridSolution : public SolutionBase<Func> {
 public:
  int maxPathScore(vector<vector<int>>& grid, int k);

  MaximumPathScoreInAGridSolution();
};

}  // namespace problem_3742
}  // namespace leetcode
