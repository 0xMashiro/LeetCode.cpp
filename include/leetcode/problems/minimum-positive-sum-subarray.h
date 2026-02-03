#include "leetcode/core.h"

namespace leetcode {
namespace problem_3364 {

using Func = std::function<int(vector<int>&, int, int)>;

class MinimumPositiveSumSubarraySolution : public SolutionBase<Func> {
 public:
  //! 3364. Minimum Positive Sum Subarray
  //! https://leetcode.com/problems/minimum-positive-sum-subarray/
  int minimumSumSubarray(vector<int>& nums, int l, int r);

  MinimumPositiveSumSubarraySolution();
};

}  // namespace problem_3364
}  // namespace leetcode
