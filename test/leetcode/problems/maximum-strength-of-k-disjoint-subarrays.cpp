#include "leetcode/problems/maximum-strength-of-k-disjoint-subarrays.h"
#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3077 {

class MaximumStrengthOfKDisjointSubarraysTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  MaximumStrengthOfKDisjointSubarraysSolution solution;
};

TEST_P(MaximumStrengthOfKDisjointSubarraysTest, Example1) {
  vector<int> nums = {1, 2, 3, -1, 2};
  int k = 3;
  long long expected = 22;
  EXPECT_EQ(expected, solution.maximumStrength(nums, k));
}

TEST_P(MaximumStrengthOfKDisjointSubarraysTest, Example2) {
  vector<int> nums = {12, -2, -2, -2, -2};
  int k = 5;
  long long expected = 64;
  EXPECT_EQ(expected, solution.maximumStrength(nums, k));
}

TEST_P(MaximumStrengthOfKDisjointSubarraysTest, Example3) {
  vector<int> nums = {-1, -2, -3};
  int k = 1;
  long long expected = -1;
  EXPECT_EQ(expected, solution.maximumStrength(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumStrengthOfKDisjointSubarraysTest,
    ::testing::ValuesIn(MaximumStrengthOfKDisjointSubarraysSolution().getStrategyNames()));

}  // namespace problem_3077
}  // namespace leetcode