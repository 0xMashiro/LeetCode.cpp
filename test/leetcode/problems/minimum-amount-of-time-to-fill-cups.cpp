#include "leetcode/problems/minimum-amount-of-time-to-fill-cups.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2335 {

class MinimumAmountOfTimeToFillCupsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumAmountOfTimeToFillCupsSolution solution;
};

TEST_P(MinimumAmountOfTimeToFillCupsTest, Example1) {
  vector<int> amount = {1, 4, 2};
  EXPECT_EQ(4, solution.fillCups(amount));
}

TEST_P(MinimumAmountOfTimeToFillCupsTest, Example2) {
  vector<int> amount = {5, 4, 4};
  EXPECT_EQ(7, solution.fillCups(amount));
}

TEST_P(MinimumAmountOfTimeToFillCupsTest, Example3) {
  vector<int> amount = {5, 0, 0};
  EXPECT_EQ(5, solution.fillCups(amount));
}

TEST_P(MinimumAmountOfTimeToFillCupsTest, AllZero) {
  vector<int> amount = {0, 0, 0};
  EXPECT_EQ(0, solution.fillCups(amount));
}

TEST_P(MinimumAmountOfTimeToFillCupsTest, OneCupEach) {
  vector<int> amount = {1, 1, 1};
  EXPECT_EQ(2, solution.fillCups(amount));
}

TEST_P(MinimumAmountOfTimeToFillCupsTest, TwoCupsSame) {
  vector<int> amount = {2, 2, 0};
  EXPECT_EQ(2, solution.fillCups(amount));
}

TEST_P(MinimumAmountOfTimeToFillCupsTest, BalancedLarge) {
  vector<int> amount = {100, 100, 100};
  EXPECT_EQ(150, solution.fillCups(amount));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumAmountOfTimeToFillCupsTest,
    ::testing::ValuesIn(MinimumAmountOfTimeToFillCupsSolution().getStrategyNames()));

}  // namespace problem_2335
}  // namespace leetcode