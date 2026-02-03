#include "leetcode/problems/split-array-largest-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_410 {

class SplitArrayLargestSumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SplitArrayLargestSumSolution solution;
};

TEST_P(SplitArrayLargestSumTest, Example1) {
  vector<int> nums = {7, 2, 5, 10, 8};
  int k = 2;
  int expected = 18;
  EXPECT_EQ(expected, solution.splitArray(nums, k));
}

TEST_P(SplitArrayLargestSumTest, Example2) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int k = 2;
  int expected = 9;
  EXPECT_EQ(expected, solution.splitArray(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SplitArrayLargestSumTest,
    ::testing::ValuesIn(SplitArrayLargestSumSolution().getStrategyNames()));

}  // namespace problem_410
}  // namespace leetcode
