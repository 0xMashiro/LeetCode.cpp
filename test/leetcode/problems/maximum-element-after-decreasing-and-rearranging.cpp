#include "leetcode/problems/maximum-element-after-decreasing-and-rearranging.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1846 {

class MaximumElementAfterDecreasingAndRearrangingTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumElementAfterDecreasingAndRearrangingSolution solution;
};

TEST_P(MaximumElementAfterDecreasingAndRearrangingTest, Example1) {
  std::vector<int> arr = {2, 2, 1, 2, 1};
  int expected = 2;
  EXPECT_EQ(expected, solution.maximumElementAfterDecrementingAndRearranging(arr));
}

TEST_P(MaximumElementAfterDecreasingAndRearrangingTest, Example2) {
  std::vector<int> arr = {100, 1, 1000};
  int expected = 3;
  EXPECT_EQ(expected, solution.maximumElementAfterDecrementingAndRearranging(arr));
}

TEST_P(MaximumElementAfterDecreasingAndRearrangingTest, Example3) {
  std::vector<int> arr = {1, 2, 3, 4, 5};
  int expected = 5;
  EXPECT_EQ(expected, solution.maximumElementAfterDecrementingAndRearranging(arr));
}

TEST_P(MaximumElementAfterDecreasingAndRearrangingTest, SelfAuthoredSingleElement) {
  std::vector<int> arr = {5};
  int expected = 1;
  EXPECT_EQ(expected, solution.maximumElementAfterDecrementingAndRearranging(arr));
}

TEST_P(MaximumElementAfterDecreasingAndRearrangingTest, SelfAuthoredAllSameLargeValues) {
  std::vector<int> arr = {1000000000, 1000000000, 1000000000};
  int expected = 3;
  EXPECT_EQ(expected, solution.maximumElementAfterDecrementingAndRearranging(arr));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumElementAfterDecreasingAndRearrangingTest,
    ::testing::ValuesIn(MaximumElementAfterDecreasingAndRearrangingSolution().getStrategyNames()));

}  // namespace problem_1846
}  // namespace leetcode
