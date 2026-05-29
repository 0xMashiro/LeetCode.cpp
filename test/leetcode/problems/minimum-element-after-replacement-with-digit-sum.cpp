#include "leetcode/problems/minimum-element-after-replacement-with-digit-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3300 {

class MinimumElementAfterReplacementWithDigitSumTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumElementAfterReplacementWithDigitSumSolution solution;
};

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, Example1) {
  vector<int> nums = {10, 12, 13, 14};
  EXPECT_EQ(1, solution.minElement(nums));
}

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, Example2) {
  vector<int> nums = {1, 2, 3, 4};
  EXPECT_EQ(1, solution.minElement(nums));
}

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, Example3) {
  vector<int> nums = {999, 19, 199};
  EXPECT_EQ(10, solution.minElement(nums));
}

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, SelfAuthoredSingleElement) {
  vector<int> nums = {42};
  EXPECT_EQ(6, solution.minElement(nums));
}

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, SelfAuthoredAllSameDigitSum) {
  vector<int> nums = {9, 18, 27, 36, 45};
  // 9->9, 18->9, 27->9, 36->9, 45->9
  EXPECT_EQ(9, solution.minElement(nums));
}

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, SelfAuthoredMaxValues) {
  vector<int> nums = {10000, 9999, 8888};
  // 10000->1, 9999->36, 8888->32
  EXPECT_EQ(1, solution.minElement(nums));
}

TEST_P(MinimumElementAfterReplacementWithDigitSumTest, SelfAuthoredLargeArray) {
  vector<int> nums(100, 9999);  // 100 elements, each 9999 -> digit sum = 36
  EXPECT_EQ(36, solution.minElement(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumElementAfterReplacementWithDigitSumTest,
    ::testing::ValuesIn(MinimumElementAfterReplacementWithDigitSumSolution().getStrategyNames()));

}  // namespace problem_3300
}  // namespace leetcode
