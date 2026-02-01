#include "leetcode/core.h"

namespace leetcode {
namespace problem_496 {

using Func = std::function<vector<int>(vector<int>&, vector<int>&)>;

class NextGreaterElementISolution : public SolutionBase<Func> {
 public:
  //! 496. Next Greater Element I
  //! https://leetcode.com/problems/next-greater-element-i/
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2);

  NextGreaterElementISolution();
};

}  // namespace problem_496
}  // namespace leetcode
