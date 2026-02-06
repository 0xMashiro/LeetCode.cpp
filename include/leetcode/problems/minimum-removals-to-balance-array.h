#include "leetcode/core.h"

namespace leetcode {
namespace problem_3634 {

using Func = std::function<int(vector<int>&, int)>;

class MinimumRemovalsToBalanceArraySolution : public SolutionBase<Func> {
 public:
  //! 3634. Minimum Removals to Balance Array
  //! https://leetcode.com/problems/minimum-removals-to-balance-array/
  int minRemoval(vector<int>& nums, int k);

  MinimumRemovalsToBalanceArraySolution();
};

}  // namespace problem_3634
}  // namespace leetcode