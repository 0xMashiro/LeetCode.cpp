#include "leetcode/core.h"

namespace leetcode {
namespace problem_3077 {

using Func = std::function<long long(vector<int>&, int)>;

class MaximumStrengthOfKDisjointSubarraysSolution : public SolutionBase<Func> {
 public:
  long long maximumStrength(vector<int>& nums, int k);
  MaximumStrengthOfKDisjointSubarraysSolution();
};

}  // namespace problem_3077
}  // namespace leetcode