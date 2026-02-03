#include "leetcode/problems/minimum-number-of-operations-to-make-array-empty.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2870 {

class MinimumNumberOfOperationsToMakeArrayEmptyTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfOperationsToMakeArrayEmptySolution solution;
};

// Example 1: nums = [2,3,3,2,2,4,2,3,4], Output: 4
TEST_P(MinimumNumberOfOperationsToMakeArrayEmptyTest, Example1) {
  vector<int> nums = {2, 3, 3, 2, 2, 4, 2, 3, 4};
  EXPECT_EQ(4, solution.minOperations(nums));
}

// Example 2: nums = [2,1,2,2,3,3], Output: -1
TEST_P(MinimumNumberOfOperationsToMakeArrayEmptyTest, Example2) {
  vector<int> nums = {2, 1, 2, 2, 3, 3};
  EXPECT_EQ(-1, solution.minOperations(nums));
}

// Additional: Single element
TEST_P(MinimumNumberOfOperationsToMakeArrayEmptyTest, SingleElement) {
  vector<int> nums = {1, 1};
  EXPECT_EQ(1, solution.minOperations(nums));
}

// Additional: All same element, count = 3
TEST_P(MinimumNumberOfOperationsToMakeArrayEmptyTest, AllSameThree) {
  vector<int> nums = {5, 5, 5};
  EXPECT_EQ(1, solution.minOperations(nums));
}

// Additional: All same element, count = 4
TEST_P(MinimumNumberOfOperationsToMakeArrayEmptyTest, AllSameFour) {
  vector<int> nums = {5, 5, 5, 5};
  EXPECT_EQ(2, solution.minOperations(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfOperationsToMakeArrayEmptyTest,
    ::testing::ValuesIn(MinimumNumberOfOperationsToMakeArrayEmptySolution().getStrategyNames()));

}  // namespace problem_2870
}  // namespace leetcode
