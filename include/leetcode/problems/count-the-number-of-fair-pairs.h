
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2563 {

using Func = std::function<long long(vector<int>&, int, int)>;

class CountTheNumberOfFairPairsSolution : public SolutionBase<Func> {
 public:
  //! 2563. Count the Number of Fair Pairs
  //! https://leetcode.com/problems/count-the-number-of-fair-pairs/
  long long countFairPairs(vector<int>& nums, int lower, int upper);

  CountTheNumberOfFairPairsSolution();
};

}  // namespace problem_2563
}  // namespace leetcode
