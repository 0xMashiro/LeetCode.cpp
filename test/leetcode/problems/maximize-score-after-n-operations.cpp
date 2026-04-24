#include "leetcode/problems/maximize-score-after-n-operations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1799 {

class MaximizeScoreAfterNOperationsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximizeScoreAfterNOperationsSolution solution;
};

TEST_P(MaximizeScoreAfterNOperationsTest, Example1) {
  vector<int> nums = {1, 2};
  EXPECT_EQ(1, solution.maxScore(nums));
}

TEST_P(MaximizeScoreAfterNOperationsTest, Example2) {
  vector<int> nums = {3, 4, 6, 8};
  EXPECT_EQ(11, solution.maxScore(nums));
}

TEST_P(MaximizeScoreAfterNOperationsTest, Example3) {
  vector<int> nums = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(14, solution.maxScore(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximizeScoreAfterNOperationsTest,
    ::testing::ValuesIn(MaximizeScoreAfterNOperationsSolution().getStrategyNames()));

}  // namespace problem_1799
}  // namespace leetcode
