#include "leetcode/problems/maximum-amount-of-money-robot-can-earn.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3418 {

class MaximumAmountOfMoneyRobotCanEarnTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumAmountOfMoneyRobotCanEarnSolution solution;
};

TEST_P(MaximumAmountOfMoneyRobotCanEarnTest, Example1) {
  vector<vector<int>> coins = {{0, 1, -1}, {1, -2, 3}, {2, -3, 4}};
  int expected = 8;
  EXPECT_EQ(expected, solution.maximumAmount(coins));
}

TEST_P(MaximumAmountOfMoneyRobotCanEarnTest, Example2) {
  vector<vector<int>> coins = {{10, 10, 10}, {10, 10, 10}};
  int expected = 40;
  EXPECT_EQ(expected, solution.maximumAmount(coins));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumAmountOfMoneyRobotCanEarnTest,
    ::testing::ValuesIn(MaximumAmountOfMoneyRobotCanEarnSolution().getStrategyNames()));

}  // namespace problem_3418
}  // namespace leetcode
