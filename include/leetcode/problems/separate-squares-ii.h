#include "leetcode/core.h"

namespace leetcode {
namespace problem_3454 {

using Func = std::function<double(vector<vector<int>>&)>;

class SeparateSquaresIiSolution : public SolutionBase<Func> {
 public:
  double separateSquares(vector<vector<int>>& squares);

  SeparateSquaresIiSolution();
};

}  // namespace problem_3454
}  // namespace leetcode