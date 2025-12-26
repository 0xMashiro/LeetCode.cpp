
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2483 {

using Func = std::function<int(string)>;

class MinimumPenaltyForAShopSolution : public SolutionBase<Func> {
 public:
  //! 2483. Minimum Penalty for a Shop
  //! https://leetcode.com/problems/minimum-penalty-for-a-shop/
  int bestClosingTime(string customers);

  MinimumPenaltyForAShopSolution();
};

}  // namespace problem_2483
}  // namespace leetcode