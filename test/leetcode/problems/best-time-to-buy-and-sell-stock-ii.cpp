#include "leetcode/problems/best-time-to-buy-and-sell-stock-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_122 {

class BestTimeToBuyAndSellStockIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BestTimeToBuyAndSellStockIiSolution solution;
};

TEST_P(BestTimeToBuyAndSellStockIiTest, Example1) {
  vector<int> prices = {7, 1, 5, 3, 6, 4};
  EXPECT_EQ(7, solution.maxProfit(prices));
}

TEST_P(BestTimeToBuyAndSellStockIiTest, Example2) {
  vector<int> prices = {1, 2, 3, 4, 5};
  EXPECT_EQ(4, solution.maxProfit(prices));
}

TEST_P(BestTimeToBuyAndSellStockIiTest, Example3) {
  vector<int> prices = {7, 6, 4, 3, 1};
  EXPECT_EQ(0, solution.maxProfit(prices));
}

TEST_P(BestTimeToBuyAndSellStockIiTest, SingleElement) {
  vector<int> prices = {5};
  EXPECT_EQ(0, solution.maxProfit(prices));
}

TEST_P(BestTimeToBuyAndSellStockIiTest, TwoElementsUp) {
  vector<int> prices = {1, 5};
  EXPECT_EQ(4, solution.maxProfit(prices));
}

TEST_P(BestTimeToBuyAndSellStockIiTest, TwoElementsDown) {
  vector<int> prices = {5, 1};
  EXPECT_EQ(0, solution.maxProfit(prices));
}

TEST_P(BestTimeToBuyAndSellStockIiTest, FlatPrices) {
  vector<int> prices = {3, 3, 3, 3};
  EXPECT_EQ(0, solution.maxProfit(prices));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode,
    BestTimeToBuyAndSellStockIiTest,
    ::testing::ValuesIn(BestTimeToBuyAndSellStockIiSolution().getStrategyNames()));

}  // namespace problem_122
}  // namespace leetcode
