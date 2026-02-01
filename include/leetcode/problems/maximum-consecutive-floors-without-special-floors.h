#include "leetcode/core.h"

namespace leetcode {
namespace problem_2274 {

using Func = std::function<int(int, int, vector<int>&)>;

class MaximumConsecutiveFloorsWithoutSpecialFloorsSolution : public SolutionBase<Func> {
 public:
  //! 2274. Maximum Consecutive Floors Without Special Floors
  //! https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/
  int maxConsecutive(int bottom, int top, vector<int>& special);

  MaximumConsecutiveFloorsWithoutSpecialFloorsSolution();
};

}  // namespace problem_2274
}  // namespace leetcode
