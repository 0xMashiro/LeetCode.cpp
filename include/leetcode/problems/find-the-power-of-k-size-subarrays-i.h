
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3254 {

using Func = std::function<vector<int>(vector<int>&, int)>;

class FindThePowerOfKSizeSubarraysISolution : public SolutionBase<Func> {
 public:
  //! 3254. Find the Power of K-Size Subarrays I
  //! https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/
  vector<int> resultsArray(vector<int>& nums, int k);

  FindThePowerOfKSizeSubarraysISolution();
};

}  // namespace problem_3254
}  // namespace leetcode
