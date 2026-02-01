#include "leetcode/core.h"

namespace leetcode {
namespace problem_1815 {

using Func = std::function<int(int, vector<int>&)>;

class MaximumNumberOfGroupsGettingFreshDonutsSolution : public SolutionBase<Func> {
 public:
  //! 1815. Maximum Number of Groups Getting Fresh Donuts
  //! https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/
  int maxHappyGroups(int batchSize, vector<int>& groups);

  MaximumNumberOfGroupsGettingFreshDonutsSolution();
};

}  // namespace problem_1815
}  // namespace leetcode
