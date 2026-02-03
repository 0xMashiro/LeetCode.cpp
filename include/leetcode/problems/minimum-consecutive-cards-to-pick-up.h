#include "leetcode/core.h"

namespace leetcode {
namespace problem_2260 {

using Func = std::function<int(vector<int>&)>;

class MinimumConsecutiveCardsToPickUpSolution : public SolutionBase<Func> {
 public:
  //! 2260. Minimum Consecutive Cards to Pick Up
  //! https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/
  int minimumCardPickup(vector<int>& cards);

  MinimumConsecutiveCardsToPickUpSolution();
};

}  // namespace problem_2260
}  // namespace leetcode
