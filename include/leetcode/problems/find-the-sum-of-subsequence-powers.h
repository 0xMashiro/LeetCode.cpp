#include "leetcode/core.h"

namespace leetcode {
namespace problem_3098 {

using Func = std::function<int(vector<int>&, int)>;

class FindTheSumOfSubsequencePowersSolution : public SolutionBase<Func> {
 public:
  //! 3098. Find the Sum of Subsequence Powers
  //! https://leetcode.com/problems/find-the-sum-of-subsequence-powers/
  int sumOfPowers(vector<int>& nums, int k);

  FindTheSumOfSubsequencePowersSolution();
};

}  // namespace problem_3098
}  // namespace leetcode
