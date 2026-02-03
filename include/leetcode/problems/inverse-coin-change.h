#include "leetcode/core.h"

namespace leetcode {
namespace problem_3592 {

using Func = std::function<vector<int>(vector<int>&)>;

class InverseCoinChangeSolution : public SolutionBase<Func> {
 public:
  //! 3592. Inverse Coin Change
  //! https://leetcode.com/problems/inverse-coin-change/
  vector<int> findCoins(vector<int>& numWays);

  InverseCoinChangeSolution();
};

}  // namespace problem_3592
}  // namespace leetcode
