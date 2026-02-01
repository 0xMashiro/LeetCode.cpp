
#include "leetcode/problems/find-k-th-smallest-pair-distance.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_719 {

class FindKThSmallestPairDistanceTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindKThSmallestPairDistanceSolution solution;
};

// Example 1: nums = [1,3,1], k = 1, Output: 0
TEST_P(FindKThSmallestPairDistanceTest, Example1) {
  vector<int> nums = {1, 3, 1};
  int k = 1;
  int expected = 0;
  EXPECT_EQ(expected, solution.smallestDistancePair(nums, k));
}

// Example 2: nums = [1,1,1], k = 2, Output: 0
TEST_P(FindKThSmallestPairDistanceTest, Example2) {
  vector<int> nums = {1, 1, 1};
  int k = 2;
  int expected = 0;
  EXPECT_EQ(expected, solution.smallestDistancePair(nums, k));
}

// Example 3: nums = [1,6,1], k = 3, Output: 5
TEST_P(FindKThSmallestPairDistanceTest, Example3) {
  vector<int> nums = {1, 6, 1};
  int k = 3;
  int expected = 5;
  EXPECT_EQ(expected, solution.smallestDistancePair(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindKThSmallestPairDistanceTest,
    ::testing::ValuesIn(FindKThSmallestPairDistanceSolution().getStrategyNames()));

}  // namespace problem_719
}  // namespace leetcode
