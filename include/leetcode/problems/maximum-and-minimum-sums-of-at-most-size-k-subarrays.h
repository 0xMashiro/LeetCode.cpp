
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3430 {

using Func = std::function<long long(vector<int>&, int)>;

class MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution : public SolutionBase<Func> {
 public:
  //! 3430. Maximum and Minimum Sums of at Most Size K Subarrays
  //! https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/
  long long minMaxSubarraySum(vector<int>& nums, int k);

  MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution();
};

}  // namespace problem_3430
}  // namespace leetcode
