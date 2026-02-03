#include "leetcode/core.h"

namespace leetcode {
namespace problem_3409 {

using Func = std::function<int(vector<int>&)>;

class LongestSubsequenceWithDecreasingAdjacentDifferenceSolution : public SolutionBase<Func> {
 public:
  int longestSubsequence(vector<int>& nums);

  LongestSubsequenceWithDecreasingAdjacentDifferenceSolution();
};

}  // namespace problem_3409
}  // namespace leetcode
