
#include "leetcode/problems/two-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1 {

class TwoSumTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TwoSumSolution solution;
};

TEST_P(TwoSumTest, Example1) {
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;
  vector<int> expected = {0, 1};
  vector<int> result = solution.twoSum(nums, target);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(TwoSumTest, Example2) {
  vector<int> nums = {3, 2, 4};
  int target = 6;
  vector<int> expected = {1, 2};
  vector<int> result = solution.twoSum(nums, target);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(TwoSumTest, Example3) {
  vector<int> nums = {3, 3};
  int target = 6;
  vector<int> expected = {0, 1};
  vector<int> result = solution.twoSum(nums, target);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TwoSumTest,
    ::testing::ValuesIn(TwoSumSolution().getStrategyNames()));

}  // namespace problem_1
}  // namespace leetcode
