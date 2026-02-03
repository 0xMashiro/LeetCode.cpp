#include "leetcode/problems/maximum-subarray-sum-with-length-divisible-by-k.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3381 {

class MaximumSubarraySumWithLengthDivisibleByKTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumSubarraySumWithLengthDivisibleByKSolution solution;
};

TEST_P(MaximumSubarraySumWithLengthDivisibleByKTest, Example1) {
  vector<int> nums = {1, 2};
  int k = 1;
  long long expected = 3;
  EXPECT_EQ(expected, solution.maxSubarraySum(nums, k));
}

TEST_P(MaximumSubarraySumWithLengthDivisibleByKTest, Example2) {
  vector<int> nums = {-1, -2, -3, -4, -5};
  int k = 4;
  long long expected = -10;
  EXPECT_EQ(expected, solution.maxSubarraySum(nums, k));
}

TEST_P(MaximumSubarraySumWithLengthDivisibleByKTest, Example3) {
  vector<int> nums = {-5, 1, 2, -3, 4};
  int k = 2;
  long long expected = 4;
  EXPECT_EQ(expected, solution.maxSubarraySum(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumSubarraySumWithLengthDivisibleByKTest,
    ::testing::ValuesIn(MaximumSubarraySumWithLengthDivisibleByKSolution().getStrategyNames()));

}  // namespace problem_3381
}  // namespace leetcode
