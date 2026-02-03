
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1654 {

using Func = std::function<int(vector<int>&, int, int, int)>;

class MinimumJumpsToReachHomeSolution : public SolutionBase<Func> {
 public:
  //! 1654. Minimum Jumps to Reach Home
  //! https://leetcode.com/problems/minimum-jumps-to-reach-home/
  int minimumJumps(vector<int>& forbidden, int a, int b, int x);

  MinimumJumpsToReachHomeSolution();
};

}  // namespace problem_1654
}  // namespace leetcode
