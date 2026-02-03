
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2215 {

using Func = std::function<vector<vector<int>>(vector<int>&, vector<int>&)>;

class FindTheDifferenceOfTwoArraysSolution : public SolutionBase<Func> {
 public:
  //! 2215. Find the Difference of Two Arrays
  //! https://leetcode.com/problems/find-the-difference-of-two-arrays/
  vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2);

  FindTheDifferenceOfTwoArraysSolution();
};

}  // namespace problem_2215
}  // namespace leetcode
