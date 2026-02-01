#include "leetcode/core.h"

namespace leetcode {
namespace problem_3654 {

using Func = std::function<long long(vector<int>&, int)>;

class MinimumSumAfterDivisibleSumDeletionsSolution : public SolutionBase<Func> {
 public:
  //! 3654. Minimum Sum After Divisible Sum Deletions
  //! https://leetcode.com/problems/minimum-sum-after-divisible-sum-deletions/
  long long minArraySum(vector<int>& nums, int k);

  MinimumSumAfterDivisibleSumDeletionsSolution();
};

}  // namespace problem_3654
}  // namespace leetcode
