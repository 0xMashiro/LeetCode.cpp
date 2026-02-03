#include "leetcode/problems/find-the-sum-of-subsequence-powers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3098 {

class FindTheSumOfSubsequencePowersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheSumOfSubsequencePowersSolution solution;
};

// Example 1: nums = [1,2,3,4], k = 3, expected = 4
TEST_P(FindTheSumOfSubsequencePowersTest, Example1) {
  vector<int> nums = {1, 2, 3, 4};
  int k = 3;
  int expected = 4;
  EXPECT_EQ(expected, solution.sumOfPowers(nums, k));
}

// Example 2: nums = [2,2], k = 2, expected = 0
TEST_P(FindTheSumOfSubsequencePowersTest, Example2) {
  vector<int> nums = {2, 2};
  int k = 2;
  int expected = 0;
  EXPECT_EQ(expected, solution.sumOfPowers(nums, k));
}

// Example 3: nums = [4,3,-1], k = 2, expected = 10
TEST_P(FindTheSumOfSubsequencePowersTest, Example3) {
  vector<int> nums = {4, 3, -1};
  int k = 2;
  int expected = 10;
  EXPECT_EQ(expected, solution.sumOfPowers(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindTheSumOfSubsequencePowersTest,
    ::testing::ValuesIn(FindTheSumOfSubsequencePowersSolution().getStrategyNames()));

}  // namespace problem_3098
}  // namespace leetcode
