#include "leetcode/core.h"

namespace leetcode {
namespace problem_2006 {

using Func = std::function<int(vector<int>&, int)>;

class CountNumberOfPairsWithAbsoluteDifferenceKSolution
    : public SolutionBase<Func> {
 public:
  int countKDifference(vector<int>& nums, int k);

  CountNumberOfPairsWithAbsoluteDifferenceKSolution();
};

}  // namespace problem_2006
}  // namespace leetcode
