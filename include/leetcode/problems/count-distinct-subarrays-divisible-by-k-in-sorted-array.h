#include "leetcode/core.h"

namespace leetcode {
namespace problem_3729 {

using Func = std::function<long long(vector<int>&, int)>;

class CountDistinctSubarraysDivisibleByKInSortedArraySolution : public SolutionBase<Func> {
 public:
  long long numGoodSubarrays(vector<int>& nums, int k);

  CountDistinctSubarraysDivisibleByKInSortedArraySolution();
};

}  // namespace problem_3729
}  // namespace leetcode
