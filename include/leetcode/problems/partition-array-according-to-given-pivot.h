#include "leetcode/core.h"

namespace leetcode {
namespace problem_2161 {

using Func = std::function<vector<int>(vector<int>&, int)>;

class PartitionArrayAccordingToGivenPivotSolution : public SolutionBase<Func> {
 public:
  //! 2161. Partition Array According to Given Pivot
  //! https://leetcode.com/problems/partition-array-according-to-given-pivot/
  vector<int> pivotArray(vector<int>& nums, int pivot);

  PartitionArrayAccordingToGivenPivotSolution();
};

}  // namespace problem_2161
}  // namespace leetcode
