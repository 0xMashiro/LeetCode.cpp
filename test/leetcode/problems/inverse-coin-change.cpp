#include "leetcode/problems/inverse-coin-change.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3592 {

class InverseCoinChangeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  InverseCoinChangeSolution solution;
};

// Example 1: numWays = [0,1,0,2,0,3,0,4,0,5], Output: [2,4,6]
TEST_P(InverseCoinChangeTest, Example1) {
  vector<int> numWays = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5};
  vector<int> expected = {2, 4, 6};
  vector<int> result = solution.findCoins(numWays);
  EXPECT_EQ(expected, result);
}

// Example 2: numWays = [1,2,2,3,4], Output: [1,2,5]
TEST_P(InverseCoinChangeTest, Example2) {
  vector<int> numWays = {1, 2, 2, 3, 4};
  vector<int> expected = {1, 2, 5};
  vector<int> result = solution.findCoins(numWays);
  EXPECT_EQ(expected, result);
}

// Example 3: numWays = [1,2,3,4,15], Output: []
TEST_P(InverseCoinChangeTest, Example3) {
  vector<int> numWays = {1, 2, 3, 4, 15};
  vector<int> expected = {};
  vector<int> result = solution.findCoins(numWays);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, InverseCoinChangeTest,
    ::testing::ValuesIn(InverseCoinChangeSolution().getStrategyNames()));

}  // namespace problem_3592
}  // namespace leetcode
