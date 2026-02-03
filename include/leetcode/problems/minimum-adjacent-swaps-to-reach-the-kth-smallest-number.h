#include "leetcode/core.h"

namespace leetcode {
namespace problem_1850 {

using Func = std::function<int(string, int)>;

class MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution : public SolutionBase<Func> {
 public:
  //! 1850. Minimum Adjacent Swaps to Reach the Kth Smallest Number
  //! https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/
  int getMinSwaps(string num, int k);

  MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution();
};

}  // namespace problem_1850
}  // namespace leetcode
