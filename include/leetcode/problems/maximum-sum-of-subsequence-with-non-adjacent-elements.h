#include "leetcode/core.h"

namespace leetcode {
namespace problem_3165 {

using Func = std::function<int(vector<int>&, vector<vector<int>>&)>;

class MaximumSumOfSubsequenceWithNonAdjacentElementsSolution : public SolutionBase<Func> {
 public:
  int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries);

  MaximumSumOfSubsequenceWithNonAdjacentElementsSolution();
};

}  // namespace problem_3165
}  // namespace leetcode
