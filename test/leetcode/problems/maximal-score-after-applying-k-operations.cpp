#include "leetcode/problems/maximal-score-after-applying-k-operations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2530 {

class MaximalScoreAfterApplyingKOperationsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximalScoreAfterApplyingKOperationsSolution solution;
};

TEST_P(MaximalScoreAfterApplyingKOperationsTest, Example1) {
  vector<int> nums = {10, 10, 10, 10, 10};
  int k = 5;
  long long expected = 50;
  EXPECT_EQ(expected, solution.maxKelements(nums, k));
}

TEST_P(MaximalScoreAfterApplyingKOperationsTest, Example2) {
  vector<int> nums = {1, 10, 3, 3, 3};
  int k = 3;
  long long expected = 17;
  EXPECT_EQ(expected, solution.maxKelements(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximalScoreAfterApplyingKOperationsTest,
    ::testing::ValuesIn(MaximalScoreAfterApplyingKOperationsSolution().getStrategyNames()));

}  // namespace problem_2530
}  // namespace leetcode