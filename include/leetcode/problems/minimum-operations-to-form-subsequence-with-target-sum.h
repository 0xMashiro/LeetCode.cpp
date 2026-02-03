#include "leetcode/core.h"

namespace leetcode {
namespace problem_2835 {

using Func = std::function<int(vector<int>&, int)>;

class MinimumOperationsToFormSubsequenceWithTargetSumSolution : public SolutionBase<Func> {
 public:
  int minOperations(vector<int>& nums, int target);
  MinimumOperationsToFormSubsequenceWithTargetSumSolution();
};

}  // namespace problem_2835
}  // namespace leetcode
