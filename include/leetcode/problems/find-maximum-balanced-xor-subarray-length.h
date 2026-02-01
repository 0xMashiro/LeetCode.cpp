#include "leetcode/core.h"

namespace leetcode {
namespace problem_3755 {

using Func = std::function<int(vector<int>&)>;

class FindMaximumBalancedXorSubarrayLengthSolution : public SolutionBase<Func> {
 public:
  //! 3755. Find Maximum Balanced XOR Subarray Length
  //! https://leetcode.com/problems/find-maximum-balanced-xor-subarray-length/
  int maxBalancedSubarray(vector<int>& nums);

  FindMaximumBalancedXorSubarrayLengthSolution();
};

}  // namespace problem_3755
}  // namespace leetcode
