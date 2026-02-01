
#include "leetcode/core.h"

namespace leetcode {
namespace problem_719 {

using Func = std::function<int(vector<int>&, int)>;

class FindKThSmallestPairDistanceSolution : public SolutionBase<Func> {
 public:
  //! 719. Find K-th Smallest Pair Distance
  //! https://leetcode.com/problems/find-k-th-smallest-pair-distance/
  int smallestDistancePair(vector<int>& nums, int k);

  FindKThSmallestPairDistanceSolution();
};

}  // namespace problem_719
}  // namespace leetcode
