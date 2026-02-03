#include "leetcode/core.h"

namespace leetcode {
namespace problem_2025 {

using Func = std::function<int(vector<int>&, int)>;

class MaximumNumberOfWaysToPartitionAnArraySolution : public SolutionBase<Func> {
 public:
  int waysToPartition(vector<int>& nums, int k);
  MaximumNumberOfWaysToPartitionAnArraySolution();
};

}  // namespace problem_2025
}  // namespace leetcode
