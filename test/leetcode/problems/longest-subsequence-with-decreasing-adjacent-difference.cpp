#include "leetcode/problems/longest-subsequence-with-decreasing-adjacent-difference.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3409 {

class LongestSubsequenceWithDecreasingAdjacentDifferenceTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestSubsequenceWithDecreasingAdjacentDifferenceSolution solution;
};

TEST_P(LongestSubsequenceWithDecreasingAdjacentDifferenceTest, Example1) {
  vector<int> nums = {16, 6, 3};
  int expected = 3;
  EXPECT_EQ(expected, solution.longestSubsequence(nums));
}

TEST_P(LongestSubsequenceWithDecreasingAdjacentDifferenceTest, Example2) {
  vector<int> nums = {6, 5, 3, 4, 2, 1};
  int expected = 4;
  EXPECT_EQ(expected, solution.longestSubsequence(nums));
}

TEST_P(LongestSubsequenceWithDecreasingAdjacentDifferenceTest, Example3) {
  vector<int> nums = {10, 20, 10, 19, 10, 20};
  int expected = 5;
  EXPECT_EQ(expected, solution.longestSubsequence(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestSubsequenceWithDecreasingAdjacentDifferenceTest,
    ::testing::ValuesIn(LongestSubsequenceWithDecreasingAdjacentDifferenceSolution().getStrategyNames()));

}  // namespace problem_3409
}  // namespace leetcode
