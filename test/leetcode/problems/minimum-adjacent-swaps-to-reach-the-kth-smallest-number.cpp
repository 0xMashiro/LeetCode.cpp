#include "leetcode/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1850 {

class MinimumAdjacentSwapsToReachTheKthSmallestNumberTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution solution;
};

TEST_P(MinimumAdjacentSwapsToReachTheKthSmallestNumberTest, Example1) {
  string num = "5489355142";
  int k = 4;
  int expected = 2;
  EXPECT_EQ(expected, solution.getMinSwaps(num, k));
}

TEST_P(MinimumAdjacentSwapsToReachTheKthSmallestNumberTest, Example2) {
  string num = "11112";
  int k = 4;
  int expected = 4;
  EXPECT_EQ(expected, solution.getMinSwaps(num, k));
}

TEST_P(MinimumAdjacentSwapsToReachTheKthSmallestNumberTest, Example3) {
  string num = "00123";
  int k = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.getMinSwaps(num, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumAdjacentSwapsToReachTheKthSmallestNumberTest,
    ::testing::ValuesIn(MinimumAdjacentSwapsToReachTheKthSmallestNumberSolution().getStrategyNames()));

}  // namespace problem_1850
}  // namespace leetcode
