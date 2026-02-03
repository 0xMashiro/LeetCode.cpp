
#include "leetcode/problems/maximum-sum-obtained-of-any-permutation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1589 {

class MaximumSumObtainedOfAnyPermutationTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumSumObtainedOfAnyPermutationSolution solution;
};

TEST_P(MaximumSumObtainedOfAnyPermutationTest, Example1) {
  vector<int> nums = {1, 2, 3, 4, 5};
  vector<vector<int>> requests = {{1, 3}, {0, 1}};
  int expected = 19;
  EXPECT_EQ(expected, solution.maxSumRangeQuery(nums, requests));
}

TEST_P(MaximumSumObtainedOfAnyPermutationTest, Example2) {
  vector<int> nums = {1, 2, 3, 4, 5, 6};
  vector<vector<int>> requests = {{0, 1}};
  int expected = 11;
  EXPECT_EQ(expected, solution.maxSumRangeQuery(nums, requests));
}

TEST_P(MaximumSumObtainedOfAnyPermutationTest, Example3) {
  vector<int> nums = {1, 2, 3, 4, 5, 10};
  vector<vector<int>> requests = {{0, 2}, {1, 3}, {1, 1}};
  int expected = 47;
  EXPECT_EQ(expected, solution.maxSumRangeQuery(nums, requests));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumSumObtainedOfAnyPermutationTest,
    ::testing::ValuesIn(MaximumSumObtainedOfAnyPermutationSolution().getStrategyNames()));

}  // namespace problem_1589
}  // namespace leetcode
