#include "leetcode/core.h"

namespace leetcode {
namespace problem_1296 {

using Func = std::function<bool(vector<int>&, int)>;

class DivideArrayInSetsOfKConsecutiveNumbersSolution : public SolutionBase<Func> {
 public:
  //! 1296. Divide Array in Sets of K Consecutive Numbers
  //! https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
  bool isPossibleDivide(vector<int>& nums, int k);

  DivideArrayInSetsOfKConsecutiveNumbersSolution();
};

}  // namespace problem_1296
}  // namespace leetcode
