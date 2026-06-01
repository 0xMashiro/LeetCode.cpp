#include "leetcode/problems/minimum-cost-of-buying-candies-with-discount.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2144 {

class MinimumCostOfBuyingCandiesWithDiscountTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostOfBuyingCandiesWithDiscountSolution solution;
};

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, Example1) {
  vector<int> cost = {1, 2, 3};
  int expected = 5;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, Example2) {
  vector<int> cost = {6, 5, 7, 9, 2, 2};
  int expected = 23;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, Example3) {
  vector<int> cost = {5, 5};
  int expected = 10;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, SelfAuthoredSingleElement) {
  vector<int> cost = {7};
  int expected = 7;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, SelfAuthoredAllEqual) {
  vector<int> cost = {4, 4, 4, 4, 4, 4};
  // 排序后 [4,4,4,4,4,4]
  // 买 4+4=8, 免 4; 买 4+4=8, 免 4; 总 = 16
  int expected = 16;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, SelfAuthoredAscending) {
  vector<int> cost = {1, 2, 3, 4, 5, 6};
  // 排序后 [6,5,4,3,2,1]
  // 买 6+5=11, 免 4; 买 3+2=5, 免 1; 总 = 16
  int expected = 16;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

TEST_P(MinimumCostOfBuyingCandiesWithDiscountTest, SelfAuthoredExactlyThree) {
  vector<int> cost = {10, 20, 30};
  // 排序后 [30,20,10]
  // 买 30+20=50, 免 10; 总 = 50
  int expected = 50;
  EXPECT_EQ(expected, solution.minimumCost(cost));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostOfBuyingCandiesWithDiscountTest,
    ::testing::ValuesIn(MinimumCostOfBuyingCandiesWithDiscountSolution().getStrategyNames()));

}  // namespace problem_2144
}  // namespace leetcode
