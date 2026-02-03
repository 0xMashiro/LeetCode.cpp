#include "leetcode/problems/longest-square-streak-in-an-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2501 {

class LongestSquareStreakInAnArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestSquareStreakInAnArraySolution solution;
};

TEST_P(LongestSquareStreakInAnArrayTest, Example1) {
  // Input: nums = [4,3,6,16,8,2]
  // Output: 3
  // Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes [2,4,16].
  // - 4 = 2 * 2.
  // - 16 = 4 * 4.
  vector<int> nums = {4, 3, 6, 16, 8, 2};
  EXPECT_EQ(3, solution.longestSquareStreak(nums));
}

TEST_P(LongestSquareStreakInAnArrayTest, Example2) {
  // Input: nums = [2,3,5,6,7]
  // Output: -1
  // Explanation: There is no square streak in nums so return -1.
  vector<int> nums = {2, 3, 5, 6, 7};
  EXPECT_EQ(-1, solution.longestSquareStreak(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestSquareStreakInAnArrayTest,
    ::testing::ValuesIn(LongestSquareStreakInAnArraySolution().getStrategyNames()));

}  // namespace problem_2501
}  // namespace leetcode
