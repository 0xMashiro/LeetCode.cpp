#include "leetcode/core.h"

namespace leetcode {
namespace problem_3689 {

using Func = std::function<long long(vector<int>&, int)>;

class MaximumTotalSubarrayValueISolution : public SolutionBase<Func> {
 public:
  //! 3689. Maximum Total Subarray Value I
  //! https://leetcode.com/problems/maximum-total-subarray-value-i/
  long long maxTotalValue(vector<int>& nums, int k);

  MaximumTotalSubarrayValueISolution();
};

}  // namespace problem_3689
}  // namespace leetcode
