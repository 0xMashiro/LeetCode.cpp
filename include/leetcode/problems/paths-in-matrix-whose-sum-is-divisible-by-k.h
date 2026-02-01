#include "leetcode/core.h"

namespace leetcode {
namespace problem_2435 {

using Func = std::function<int(vector<vector<int>>&, int)>;

class PathsInMatrixWhoseSumIsDivisibleByKSolution : public SolutionBase<Func> {
 public:
  int numberOfPaths(vector<vector<int>>& grid, int k);

  PathsInMatrixWhoseSumIsDivisibleByKSolution();
};

}  // namespace problem_2435
}  // namespace leetcode