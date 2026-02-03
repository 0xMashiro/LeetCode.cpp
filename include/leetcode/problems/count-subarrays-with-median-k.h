#include "leetcode/core.h"

namespace leetcode {
namespace problem_2488 {

using Func = std::function<int(vector<int>&, int)>;

class CountSubarraysWithMedianKSolution : public SolutionBase<Func> {
 public:
  int countSubarrays(vector<int>& nums, int k);
  CountSubarraysWithMedianKSolution();
};

}  // namespace problem_2488
}  // namespace leetcode