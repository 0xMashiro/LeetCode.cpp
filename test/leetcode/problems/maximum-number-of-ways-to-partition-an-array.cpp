#include "leetcode/problems/maximum-number-of-ways-to-partition-an-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2025 {

class MaximumNumberOfWaysToPartitionAnArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  MaximumNumberOfWaysToPartitionAnArraySolution solution;
};

TEST_P(MaximumNumberOfWaysToPartitionAnArrayTest, Example1) {
  vector<int> nums = {2, -1, 2};
  int k = 3;
  EXPECT_EQ(1, solution.waysToPartition(nums, k));
}

TEST_P(MaximumNumberOfWaysToPartitionAnArrayTest, Example2) {
  vector<int> nums = {0, 0, 0};
  int k = 1;
  EXPECT_EQ(2, solution.waysToPartition(nums, k));
}

TEST_P(MaximumNumberOfWaysToPartitionAnArrayTest, Example3) {
  vector<int> nums = {22, 4, -25, -20, -15, 15, -16, 7, 19, -10, 0, -13, -14};
  int k = -33;
  EXPECT_EQ(4, solution.waysToPartition(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumNumberOfWaysToPartitionAnArrayTest,
    ::testing::ValuesIn(MaximumNumberOfWaysToPartitionAnArraySolution().getStrategyNames()));

}  // namespace problem_2025
}  // namespace leetcode
