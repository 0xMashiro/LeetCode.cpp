#include "leetcode/core.h"

namespace leetcode {
namespace problem_3660 {

using Func = std::function<vector<int>(vector<int>&)>;

class JumpGameIxSolution : public SolutionBase<Func> {
 public:
  vector<int> maxValue(vector<int>& nums);
  JumpGameIxSolution();
};

}  // namespace problem_3660
}  // namespace leetcode
