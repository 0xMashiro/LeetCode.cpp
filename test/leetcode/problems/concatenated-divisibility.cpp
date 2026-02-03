#include "leetcode/problems/concatenated-divisibility.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3533 {

class ConcatenatedDivisibilityTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConcatenatedDivisibilitySolution solution;
};

// Example 1: nums = [3,12,45], k = 5 -> [3,12,45]
TEST_P(ConcatenatedDivisibilityTest, Example1) {
  vector<int> nums = {3, 12, 45};
  int k = 5;
  vector<int> expected = {3, 12, 45};
  vector<int> result = solution.concatenatedDivisibility(nums, k);
  EXPECT_EQ(expected, result);
}

// Example 2: nums = [10,5], k = 10 -> [5,10]
TEST_P(ConcatenatedDivisibilityTest, Example2) {
  vector<int> nums = {10, 5};
  int k = 10;
  vector<int> expected = {5, 10};
  vector<int> result = solution.concatenatedDivisibility(nums, k);
  EXPECT_EQ(expected, result);
}

// Example 3: nums = [1,2,3], k = 5 -> []
TEST_P(ConcatenatedDivisibilityTest, Example3) {
  vector<int> nums = {1, 2, 3};
  int k = 5;
  vector<int> expected = {};
  vector<int> result = solution.concatenatedDivisibility(nums, k);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConcatenatedDivisibilityTest,
    ::testing::ValuesIn(ConcatenatedDivisibilitySolution().getStrategyNames()));

}  // namespace problem_3533
}  // namespace leetcode
