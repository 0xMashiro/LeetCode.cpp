#include "leetcode/core.h"

namespace leetcode {
namespace problem_1340 {

using Func = std::function<int(vector<int>&, int)>;

class JumpGameVSolution : public SolutionBase<Func> {
 public:
  //! 1340. Jump Game V
  //! https://leetcode.com/problems/jump-game-v/
  int maxJumps(vector<int>& arr, int d);

  JumpGameVSolution();
};

}  // namespace problem_1340
}  // namespace leetcode
