#include "leetcode/problems/maximum-alternating-sum-of-squares.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3727 {

class MaximumAlternatingSumOfSquaresTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumAlternatingSumOfSquaresSolution solution;
};

TEST_P(MaximumAlternatingSumOfSquaresTest, Example1) {
  vector<int> nums = {1, 2, 3};
  long long expected = 12;
  EXPECT_EQ(expected, solution.maxAlternatingSum(nums));
}

TEST_P(MaximumAlternatingSumOfSquaresTest, Example2) {
  vector<int> nums = {1, -1, 2, -2, 3, -3};
  long long expected = 16;
  EXPECT_EQ(expected, solution.maxAlternatingSum(nums));
}

TEST_P(MaximumAlternatingSumOfSquaresTest, SingleElement) {
  vector<int> nums = {5};
  long long expected = 25;
  EXPECT_EQ(expected, solution.maxAlternatingSum(nums));
}

TEST_P(MaximumAlternatingSumOfSquaresTest, TwoElements) {
  vector<int> nums = {1, 2};
  // 按绝对值排序：[2, 1]
  // 正位置1个（2），负位置1个（1）
  // score = 4 - 1 = 3
  long long expected = 3;
  EXPECT_EQ(expected, solution.maxAlternatingSum(nums));
}

TEST_P(MaximumAlternatingSumOfSquaresTest, AllSameAbsoluteValue) {
  vector<int> nums = {-5, 5, -5, 5};
  // 按绝对值排序：都是25
  // 正位置2个，负位置2个
  // score = 25 + 25 - 25 - 25 = 0
  long long expected = 0;
  EXPECT_EQ(expected, solution.maxAlternatingSum(nums));
}

TEST_P(MaximumAlternatingSumOfSquaresTest, WithZeros) {
  vector<int> nums = {0, 0, 3, 4};
  // 按绝对值排序：[4, 3, 0, 0]
  // 正位置2个（4, 3），负位置2个（0, 0）
  // score = 16 + 9 - 0 - 0 = 25
  long long expected = 25;
  EXPECT_EQ(expected, solution.maxAlternatingSum(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumAlternatingSumOfSquaresTest,
    ::testing::ValuesIn(MaximumAlternatingSumOfSquaresSolution().getStrategyNames()));

}  // namespace problem_3727
}  // namespace leetcode
