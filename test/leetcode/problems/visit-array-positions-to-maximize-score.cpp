#include "leetcode/problems/visit-array-positions-to-maximize-score.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2786 {

class VisitArrayPositionsToMaximizeScoreTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  VisitArrayPositionsToMaximizeScoreSolution solution;
};

TEST_P(VisitArrayPositionsToMaximizeScoreTest, Example1) {
  // Input: nums = [2,3,6,1,9,2], x = 5
  // Output: 13
  // Explanation: 0 -> 2 -> 3 -> 4, score = 2 + 6 + 1 + 9 - 5 = 13
  vector<int> nums = {2, 3, 6, 1, 9, 2};
  int x = 5;
  EXPECT_EQ(13, solution.maxScore(nums, x));
}

TEST_P(VisitArrayPositionsToMaximizeScoreTest, Example2) {
  // Input: nums = [2,4,6,8], x = 3
  // Output: 20
  // Explanation: All same parity, no penalty. Score = 2 + 4 + 6 + 8 = 20
  vector<int> nums = {2, 4, 6, 8};
  int x = 3;
  EXPECT_EQ(20, solution.maxScore(nums, x));
}

TEST_P(VisitArrayPositionsToMaximizeScoreTest, AllOdd) {
  // All odd numbers, no penalty
  vector<int> nums = {1, 3, 5, 7};
  int x = 10;
  EXPECT_EQ(16, solution.maxScore(nums, x));
}

TEST_P(VisitArrayPositionsToMaximizeScoreTest, MinSize) {
  // Minimum size: 2 elements
  vector<int> nums = {1, 2};
  int x = 5;
  // From 0 to 1: 1 + 2 - 5 = -2, or just stay at 0: 1
  // But we can also go 0->1, getting 1+2-5=-2, worse than just 1
  // Or skip 1, just get 1
  // Actually we must consider: best is max(1, 1+2-5) = 1 if we skip, or just 1
  // Wait, we can choose to not visit all positions
  // But the algorithm should handle this
  EXPECT_EQ(1, solution.maxScore(nums, x));
}

TEST_P(VisitArrayPositionsToMaximizeScoreTest, StartWithOdd) {
  vector<int> nums = {3, 2, 4, 6};
  int x = 5;
  // 3 -> 2 -> 4 -> 6: 3+2+4+6 - 5 = 10 (one parity change)
  // Or just 3 + 4 + 6 - 5 = 8 (skip 2)
  // Or 3 + 2 - 5 = 0 (stop early)
  // Best: 3 + 2 + 4 + 6 - 5 = 10
  EXPECT_EQ(10, solution.maxScore(nums, x));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, VisitArrayPositionsToMaximizeScoreTest,
    ::testing::ValuesIn(VisitArrayPositionsToMaximizeScoreSolution().getStrategyNames()));

}  // namespace problem_2786
}  // namespace leetcode
