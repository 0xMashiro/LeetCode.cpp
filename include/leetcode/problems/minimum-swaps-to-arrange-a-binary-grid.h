#include "leetcode/core.h"

namespace leetcode {
namespace problem_1536 {

using Func = std::function<int(vector<vector<int>> &)>;

class MinimumSwapsToArrangeABinaryGridSolution : public SolutionBase<Func> {
 public:
  //! 1536. Minimum Swaps to Arrange a Binary Grid
  //! https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/
  int minSwaps(vector<vector<int>> &grid);

  MinimumSwapsToArrangeABinaryGridSolution();
};

}  // namespace problem_1536
}  // namespace leetcode