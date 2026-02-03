#include "leetcode/core.h"

namespace leetcode {
namespace problem_503 {

using Func = std::function<vector<int>(vector<int>&)>;

class NextGreaterElementIiSolution : public SolutionBase<Func> {
 public:
  //! 503. Next Greater Element II
  //! https://leetcode.com/problems/next-greater-element-ii/
  vector<int> nextGreaterElements(vector<int>& nums);

  NextGreaterElementIiSolution();
};

}  // namespace problem_503
}  // namespace leetcode
