#include "leetcode/core.h"

namespace leetcode {
namespace problem_1411 {

using Func = std::function<int(int)>;

class NumberOfWaysToPaintN3GridSolution : public SolutionBase<Func> {
 public:
  //! 1411. Number of Ways to Paint N × 3 Grid
  //! https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/
  int numOfWays(int n);

  NumberOfWaysToPaintN3GridSolution();
};

}  // namespace problem_1411
}  // namespace leetcode