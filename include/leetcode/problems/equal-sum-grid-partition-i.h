#include "leetcode/core.h"

namespace leetcode {
namespace problem_3546 {

using Func = std::function<bool(vector<vector<int>> &)>;

class EqualSumGridPartitionISolution : public SolutionBase<Func> {
 public:
  //! 3546. Equal Sum Grid Partition I
  //! https://leetcode.com/problems/equal-sum-grid-partition-i/
  bool canPartitionGrid(vector<vector<int>> &grid);

  EqualSumGridPartitionISolution();
};

}  // namespace problem_3546
}  // namespace leetcode
