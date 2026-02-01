#include "leetcode/problems/longest-balanced-subarray-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3719 {

class LongestBalancedSubarrayITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestBalancedSubarrayISolution solution;
};

TEST_P(LongestBalancedSubarrayITest, Example1) {
  vector<int> nums = {2, 5, 4, 3};
  EXPECT_EQ(4, solution.longestBalanced(nums));
}

TEST_P(LongestBalancedSubarrayITest, Example2) {
  vector<int> nums = {3, 2, 2, 5, 4};
  EXPECT_EQ(5, solution.longestBalanced(nums));
}

TEST_P(LongestBalancedSubarrayITest, Example3) {
  vector<int> nums = {1, 2, 3, 2};
  EXPECT_EQ(3, solution.longestBalanced(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestBalancedSubarrayITest,
    ::testing::ValuesIn(LongestBalancedSubarrayISolution().getStrategyNames()));

}  // namespace problem_3719
}  // namespace leetcode