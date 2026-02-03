#include "leetcode/problems/minimum-cost-to-acquire-required-items.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3789 {

class MinimumCostToAcquireRequiredItemsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostToAcquireRequiredItemsSolution solution;
};

TEST_P(MinimumCostToAcquireRequiredItemsTest, Example1) {
  int cost1 = 3, cost2 = 2, costBoth = 1, need1 = 3, need2 = 2;
  long long expected = 3;
  EXPECT_EQ(expected, solution.minimumCost(cost1, cost2, costBoth, need1, need2));
}

TEST_P(MinimumCostToAcquireRequiredItemsTest, Example2) {
  int cost1 = 5, cost2 = 4, costBoth = 15, need1 = 2, need2 = 3;
  long long expected = 22;
  EXPECT_EQ(expected, solution.minimumCost(cost1, cost2, costBoth, need1, need2));
}

TEST_P(MinimumCostToAcquireRequiredItemsTest, Example3) {
  int cost1 = 5, cost2 = 4, costBoth = 15, need1 = 0, need2 = 0;
  long long expected = 0;
  EXPECT_EQ(expected, solution.minimumCost(cost1, cost2, costBoth, need1, need2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostToAcquireRequiredItemsTest,
    ::testing::ValuesIn(MinimumCostToAcquireRequiredItemsSolution().getStrategyNames()));

}  // namespace problem_3789
}  // namespace leetcode
