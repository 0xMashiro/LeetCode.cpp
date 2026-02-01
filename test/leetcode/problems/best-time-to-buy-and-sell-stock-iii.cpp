#include "leetcode/problems/best-time-to-buy-and-sell-stock-iii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_123 {

class BestTimeToBuyAndSellStockIiiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BestTimeToBuyAndSellStockIiiSolution solution;
};

// 示例 1：两次交易获得最大利润
TEST_P(BestTimeToBuyAndSellStockIiiTest, Example1) {
  vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
  int expected = 6;  // 买在 0 卖在 3 (利润 3)，买在 1 卖在 4 (利润 3)
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 示例 2：一次交易获得最大利润
TEST_P(BestTimeToBuyAndSellStockIiiTest, Example2) {
  vector<int> prices = {1, 2, 3, 4, 5};
  int expected = 4;  // 买在 1 卖在 5
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 示例 3：无法获利
TEST_P(BestTimeToBuyAndSellStockIiiTest, Example3) {
  vector<int> prices = {7, 6, 4, 3, 1};
  int expected = 0;  // 价格递减，无法获利
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 边界情况：空数组
TEST_P(BestTimeToBuyAndSellStockIiiTest, EmptyArray) {
  vector<int> prices = {};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 边界情况：只有一个元素
TEST_P(BestTimeToBuyAndSellStockIiiTest, SingleElement) {
  vector<int> prices = {5};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 边界情况：两个元素，可以交易一次
TEST_P(BestTimeToBuyAndSellStockIiiTest, TwoElements) {
  vector<int> prices = {1, 2};
  int expected = 1;
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 边界情况：价格相同
TEST_P(BestTimeToBuyAndSellStockIiiTest, SamePrice) {
  vector<int> prices = {5, 5, 5, 5, 5};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 复杂情况：多次波动
TEST_P(BestTimeToBuyAndSellStockIiiTest, ComplexPattern) {
  vector<int> prices = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
  // 最优策略：1->7 (利润6) 和 2->9 (利润7) = 13
  // 或者：1->4 (3) + 2->7 (5) + 2->9 (7) = 但不能超过两次交易
  // 实际最优：1->7 (6) + 2->9 (7) = 13
  int expected = 13;
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

// 边界情况：极大值
TEST_P(BestTimeToBuyAndSellStockIiiTest, LargeValues) {
  vector<int> prices = {100000, 0, 100000, 0, 100000};
  // 0->100000 (100000) + 0->100000 (100000) = 200000
  int expected = 200000;
  EXPECT_EQ(expected, solution.maxProfit(prices));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BestTimeToBuyAndSellStockIiiTest,
    ::testing::ValuesIn(BestTimeToBuyAndSellStockIiiSolution().getStrategyNames()));

}  // namespace problem_123
}  // namespace leetcode
