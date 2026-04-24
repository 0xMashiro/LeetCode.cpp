#include "leetcode/core.h"

namespace leetcode {
namespace problem_2444 {

using Func = std::function<long long(vector<int>&, int, int)>;

class CountSubarraysWithFixedBoundsSolution : public SolutionBase<Func> {
 public:
  //! 2444. Count Subarrays With Fixed Bounds
  //! https://leetcode.com/problems/count-subarrays-with-fixed-bounds/
  long long countSubarrays(vector<int>& nums, int minK, int maxK);

  CountSubarraysWithFixedBoundsSolution();
};

}  // namespace problem_2444
}  // namespace leetcode
