#include "leetcode/problems/left-and-right-sum-differences.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2574 {

class LeftAndRightSumDifferencesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LeftAndRightSumDifferencesSolution solution;
};

TEST_P(LeftAndRightSumDifferencesTest, Example1) {
  vector<int> nums = {10, 4, 8, 3};
  vector<int> expected = {15, 1, 11, 22};
  EXPECT_EQ(expected, solution.leftRightDifference(nums));
}

TEST_P(LeftAndRightSumDifferencesTest, Example2) {
  vector<int> nums = {1};
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.leftRightDifference(nums));
}

TEST_P(LeftAndRightSumDifferencesTest, SelfAuthoredTwoElements) {
  vector<int> nums = {5, 7};
  // leftSum = [0, 5], rightSum = [7, 0], answer = [|0-7|, |5-0|] = [7, 5]
  vector<int> expected = {7, 5};
  EXPECT_EQ(expected, solution.leftRightDifference(nums));
}

TEST_P(LeftAndRightSumDifferencesTest, SelfAuthoredAllSame) {
  vector<int> nums = {3, 3, 3};
  // leftSum = [0,3,6], rightSum = [6,3,0], answer = [6,0,6]
  vector<int> expected = {6, 0, 6};
  EXPECT_EQ(expected, solution.leftRightDifference(nums));
}

TEST_P(LeftAndRightSumDifferencesTest, SelfAuthoredLargeValues) {
  vector<int> nums = {100000, 1, 100000};
  // leftSum = [0,100000,100001], rightSum = [100001,100000,0]
  // answer = [|0-100001|, |100000-100000|, |100001-0|] = [100001, 0, 100001]
  vector<int> expected = {100001, 0, 100001};
  EXPECT_EQ(expected, solution.leftRightDifference(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LeftAndRightSumDifferencesTest,
    ::testing::ValuesIn(LeftAndRightSumDifferencesSolution().getStrategyNames()));

}  // namespace problem_2574
}  // namespace leetcode
