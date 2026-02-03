
#include "leetcode/problems/collecting-chocolates.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2735 {

class CollectingChocolatesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CollectingChocolatesSolution solution;
};

TEST_P(CollectingChocolatesTest, Example1) {
  vector<int> nums = {20, 1, 15};
  int x = 5;
  long long expected = 13;
  EXPECT_EQ(expected, solution.minCost(nums, x));
}

TEST_P(CollectingChocolatesTest, Example2) {
  vector<int> nums = {1, 2, 3};
  int x = 4;
  long long expected = 6;
  EXPECT_EQ(expected, solution.minCost(nums, x));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CollectingChocolatesTest,
    ::testing::ValuesIn(CollectingChocolatesSolution().getStrategyNames()));

}  // namespace problem_2735
}  // namespace leetcode
