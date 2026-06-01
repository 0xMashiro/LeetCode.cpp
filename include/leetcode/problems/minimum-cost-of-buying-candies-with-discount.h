#include "leetcode/core.h"

namespace leetcode {
namespace problem_2144 {

using Func = std::function<int(vector<int>&)>;

class MinimumCostOfBuyingCandiesWithDiscountSolution : public SolutionBase<Func> {
 public:
  //! 2144. Minimum Cost of Buying Candies With Discount
  //! https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/
  int minimumCost(vector<int>& cost);

  MinimumCostOfBuyingCandiesWithDiscountSolution();
};

}  // namespace problem_2144
}  // namespace leetcode
