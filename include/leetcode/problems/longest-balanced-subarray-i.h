#include "leetcode/core.h"

namespace leetcode {
namespace problem_3719 {

using Func = std::function<int(vector<int>&)>;

class LongestBalancedSubarrayISolution : public SolutionBase<Func> {
 public:
  int longestBalanced(vector<int>& nums);

  LongestBalancedSubarrayISolution();
};

}  // namespace problem_3719
}  // namespace leetcode