#include "leetcode/core.h"

namespace leetcode {
namespace problem_1574 {

using Func = std::function<int(vector<int>&)>;

class ShortestSubarrayToBeRemovedToMakeArraySortedSolution : public SolutionBase<Func> {
 public:
  //! 1574. Shortest Subarray to be Removed to Make Array Sorted
  //! https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
  int findLengthOfShortestSubarray(vector<int>& arr);

  ShortestSubarrayToBeRemovedToMakeArraySortedSolution();
};

}  // namespace problem_1574
}  // namespace leetcode
