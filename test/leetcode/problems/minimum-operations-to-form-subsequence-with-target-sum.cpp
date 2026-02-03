#include "leetcode/problems/minimum-operations-to-form-subsequence-with-target-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2835 {

class MinimumOperationsToFormSubsequenceWithTargetSumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumOperationsToFormSubsequenceWithTargetSumSolution solution;
};

TEST_P(MinimumOperationsToFormSubsequenceWithTargetSumTest, Example1) {
  vector<int> nums = {1, 2, 8};
  int target = 7;
  int expected = 1;
  EXPECT_EQ(expected, solution.minOperations(nums, target));
}

TEST_P(MinimumOperationsToFormSubsequenceWithTargetSumTest, Example2) {
  vector<int> nums = {1, 32, 1, 2};
  int target = 12;
  int expected = 2;
  EXPECT_EQ(expected, solution.minOperations(nums, target));
}

TEST_P(MinimumOperationsToFormSubsequenceWithTargetSumTest, Example3) {
  vector<int> nums = {1, 32, 1};
  int target = 35;
  int expected = -1;
  EXPECT_EQ(expected, solution.minOperations(nums, target));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumOperationsToFormSubsequenceWithTargetSumTest,
    ::testing::ValuesIn(MinimumOperationsToFormSubsequenceWithTargetSumSolution().getStrategyNames()));

}  // namespace problem_2835
}  // namespace leetcode
