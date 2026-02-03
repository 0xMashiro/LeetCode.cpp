
#include "leetcode/problems/final-array-state-after-k-multiplication-operations-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3264 {

class FinalArrayStateAfterKMultiplicationOperationsITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FinalArrayStateAfterKMultiplicationOperationsISolution solution;
};

TEST_P(FinalArrayStateAfterKMultiplicationOperationsITest, Example1) {
  vector<int> nums = {2, 1, 3, 5, 6};
  int k = 5;
  int multiplier = 2;
  vector<int> expected = {8, 4, 6, 5, 6};
  EXPECT_EQ(expected, solution.getFinalState(nums, k, multiplier));
}

TEST_P(FinalArrayStateAfterKMultiplicationOperationsITest, Example2) {
  vector<int> nums = {1, 2};
  int k = 3;
  int multiplier = 4;
  vector<int> expected = {16, 8};
  EXPECT_EQ(expected, solution.getFinalState(nums, k, multiplier));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FinalArrayStateAfterKMultiplicationOperationsITest,
    ::testing::ValuesIn(FinalArrayStateAfterKMultiplicationOperationsISolution().getStrategyNames()));

}  // namespace problem_3264
}  // namespace leetcode
