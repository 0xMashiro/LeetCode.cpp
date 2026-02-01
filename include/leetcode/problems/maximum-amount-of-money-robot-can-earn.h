#include "leetcode/core.h"

namespace leetcode {
namespace problem_3418 {

using Func = std::function<int(vector<vector<int>>&)>;

class MaximumAmountOfMoneyRobotCanEarnSolution : public SolutionBase<Func> {
 public:
  //! 3418. Maximum Amount of Money Robot Can Earn
  //! https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/
  int maximumAmount(vector<vector<int>>& coins);

  MaximumAmountOfMoneyRobotCanEarnSolution();
};

}  // namespace problem_3418
}  // namespace leetcode
