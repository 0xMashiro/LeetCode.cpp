#include "leetcode/core.h"

namespace leetcode {
namespace problem_915 {

using Func = std::function<int(vector<int>&)>;

class PartitionArrayIntoDisjointIntervalsSolution : public SolutionBase<Func> {
 public:
  //! 915. Partition Array into Disjoint Intervals
  //! https://leetcode.com/problems/partition-array-into-disjoint-intervals/
  int partitionDisjoint(vector<int>& nums);

  PartitionArrayIntoDisjointIntervalsSolution();
};

}  // namespace problem_915
}  // namespace leetcode
