#include "leetcode/problems/minimum-removals-to-balance-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3634 {

class MinimumRemovalsToBalanceArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumRemovalsToBalanceArraySolution solution;
};

TEST_P(MinimumRemovalsToBalanceArrayTest, Example1) {
  vector<int> nums = {2, 1, 5};
  int k = 2;
  int expected = 1;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

TEST_P(MinimumRemovalsToBalanceArrayTest, Example2) {
  vector<int> nums = {1, 6, 2, 9};
  int k = 3;
  int expected = 2;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

TEST_P(MinimumRemovalsToBalanceArrayTest, Example3) {
  vector<int> nums = {4, 6};
  int k = 2;
  int expected = 0;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

TEST_P(MinimumRemovalsToBalanceArrayTest, SingleElement) {
  vector<int> nums = {5};
  int k = 1;
  int expected = 0;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

TEST_P(MinimumRemovalsToBalanceArrayTest, AllSameElements) {
  vector<int> nums = {3, 3, 3, 3};
  int k = 1;
  int expected = 0;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

TEST_P(MinimumRemovalsToBalanceArrayTest, AlreadyBalanced) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int k = 5;
  int expected = 0;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

TEST_P(MinimumRemovalsToBalanceArrayTest, NeedRemoveAllButOne) {
  vector<int> nums = {1, 100};
  int k = 2;
  int expected = 1;
  EXPECT_EQ(expected, solution.minRemoval(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumRemovalsToBalanceArrayTest,
    ::testing::ValuesIn(MinimumRemovalsToBalanceArraySolution().getStrategyNames()));

}  // namespace problem_3634
}  // namespace leetcode