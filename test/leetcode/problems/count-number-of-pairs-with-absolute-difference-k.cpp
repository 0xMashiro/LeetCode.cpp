#include "leetcode/problems/count-number-of-pairs-with-absolute-difference-k.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2006 {

class CountNumberOfPairsWithAbsoluteDifferenceKTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountNumberOfPairsWithAbsoluteDifferenceKSolution solution;
};

TEST_P(CountNumberOfPairsWithAbsoluteDifferenceKTest, Example1) {
  vector<int> nums = {1, 2, 2, 1};
  int k = 1;
  EXPECT_EQ(4, solution.countKDifference(nums, k));
}

TEST_P(CountNumberOfPairsWithAbsoluteDifferenceKTest, Example2) {
  vector<int> nums = {1, 3};
  int k = 3;
  EXPECT_EQ(0, solution.countKDifference(nums, k));
}

TEST_P(CountNumberOfPairsWithAbsoluteDifferenceKTest, Example3) {
  vector<int> nums = {3, 2, 1, 5, 4};
  int k = 2;
  EXPECT_EQ(3, solution.countKDifference(nums, k));
}

TEST_P(CountNumberOfPairsWithAbsoluteDifferenceKTest,
       SelfAuthoredSingleElement) {
  vector<int> nums = {5};
  int k = 1;
  EXPECT_EQ(0, solution.countKDifference(nums, k));
}

TEST_P(CountNumberOfPairsWithAbsoluteDifferenceKTest, SelfAuthoredNoPairs) {
  vector<int> nums = {1, 2, 3};
  int k = 10;
  EXPECT_EQ(0, solution.countKDifference(nums, k));
}

TEST_P(CountNumberOfPairsWithAbsoluteDifferenceKTest, SelfAuthoredMaxDiff) {
  vector<int> nums = {1, 100};
  int k = 99;
  EXPECT_EQ(1, solution.countKDifference(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountNumberOfPairsWithAbsoluteDifferenceKTest,
    ::testing::ValuesIn(CountNumberOfPairsWithAbsoluteDifferenceKSolution()
                            .getStrategyNames()));

}  // namespace problem_2006
}  // namespace leetcode
