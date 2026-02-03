
#include "leetcode/problems/build-array-from-permutation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1920 {

class BuildArrayFromPermutationTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BuildArrayFromPermutationSolution solution;
};

TEST_P(BuildArrayFromPermutationTest, Example1) {
  vector<int> nums = {0, 2, 1, 5, 3, 4};
  vector<int> expected = {0, 1, 2, 4, 5, 3};
  EXPECT_EQ(expected, solution.buildArray(nums));
}

TEST_P(BuildArrayFromPermutationTest, Example2) {
  vector<int> nums = {5, 0, 1, 2, 3, 4};
  vector<int> expected = {4, 5, 0, 1, 2, 3};
  EXPECT_EQ(expected, solution.buildArray(nums));
}

TEST_P(BuildArrayFromPermutationTest, SingleElement) {
  // 边界：单个元素
  vector<int> nums = {0};
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.buildArray(nums));
}

TEST_P(BuildArrayFromPermutationTest, TwoElements) {
  // 边界：两个元素
  vector<int> nums = {1, 0};
  vector<int> expected = {0, 1};
  EXPECT_EQ(expected, solution.buildArray(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BuildArrayFromPermutationTest,
    ::testing::ValuesIn(BuildArrayFromPermutationSolution().getStrategyNames()));

}  // namespace problem_1920
}  // namespace leetcode
