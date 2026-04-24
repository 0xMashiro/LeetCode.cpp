#include "leetcode/core.h"

namespace leetcode {
namespace problem_321 {

using Func = std::function<vector<int>(vector<int>&, vector<int>&, int)>;

class CreateMaximumNumberSolution : public SolutionBase<Func> {
 public:
  //! 321. Create Maximum Number
  //! https://leetcode.com/problems/create-maximum-number/
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k);

  CreateMaximumNumberSolution();
};

}  // namespace problem_321
}  // namespace leetcode
