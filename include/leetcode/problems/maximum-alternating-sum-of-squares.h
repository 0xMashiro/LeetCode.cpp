#include "leetcode/core.h"

namespace leetcode {
namespace problem_3727 {

using Func = std::function<long long(vector<int>&)>;

class MaximumAlternatingSumOfSquaresSolution : public SolutionBase<Func> {
 public:
  //! 3727. Maximum Alternating Sum of Squares
  //! https://leetcode.com/problems/maximum-alternating-sum-of-squares/
  long long maxAlternatingSum(vector<int>& nums);

  MaximumAlternatingSumOfSquaresSolution();
};

}  // namespace problem_3727
}  // namespace leetcode
