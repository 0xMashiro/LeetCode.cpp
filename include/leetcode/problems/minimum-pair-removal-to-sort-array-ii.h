#include "leetcode/core.h"

namespace leetcode {
namespace problem_3510 {

using Func = std::function<int(vector<int>&)>;

class MinimumPairRemovalToSortArrayIiSolution : public SolutionBase<Func> {
 public:
  //! 3510. Minimum Pair Removal to Sort Array II
  //! https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/
  int minimumPairRemoval(vector<int>& nums);

  MinimumPairRemovalToSortArrayIiSolution();
};

}  // namespace problem_3510
}  // namespace leetcode