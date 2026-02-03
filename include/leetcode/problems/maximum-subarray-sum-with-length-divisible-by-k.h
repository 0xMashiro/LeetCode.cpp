#include "leetcode/core.h"

namespace leetcode {
namespace problem_3381 {

using Func = std::function<long long(vector<int>&, int)>;

class MaximumSubarraySumWithLengthDivisibleByKSolution : public SolutionBase<Func> {
 public:
  //! 3381. Maximum Subarray Sum With Length Divisible by K
  //! https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/
  long long maxSubarraySum(vector<int>& nums, int k);

  MaximumSubarraySumWithLengthDivisibleByKSolution();
};

}  // namespace problem_3381
}  // namespace leetcode
