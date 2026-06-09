#include "leetcode/problems/maximum-total-subarray-value-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3689 {

class MaximumTotalSubarrayValueITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumTotalSubarrayValueISolution solution;
};

TEST_P(MaximumTotalSubarrayValueITest, Example1) {
  vector<int> nums = {1, 3, 2};
  int k = 2;
  EXPECT_EQ(4, solution.maxTotalValue(nums, k));
}

TEST_P(MaximumTotalSubarrayValueITest, Example2) {
  vector<int> nums = {4, 2, 5, 1};
  int k = 3;
  EXPECT_EQ(12, solution.maxTotalValue(nums, k));
}

TEST_P(MaximumTotalSubarrayValueITest, SelfAuthoredSingleElement) {
  vector<int> nums = {5};
  int k = 5;
  EXPECT_EQ(0, solution.maxTotalValue(nums, k));
}

TEST_P(MaximumTotalSubarrayValueITest, SelfAuthoredAllSame) {
  vector<int> nums = {7, 7, 7, 7};
  int k = 10;
  EXPECT_EQ(0, solution.maxTotalValue(nums, k));
}

TEST_P(MaximumTotalSubarrayValueITest, SelfAuthoredLargeValues) {
  vector<int> nums = {0, 1000000000};
  int k = 1;
  EXPECT_EQ(1000000000LL, solution.maxTotalValue(nums, k));
}

TEST_P(MaximumTotalSubarrayValueITest, SelfAuthoredLargeK) {
  vector<int> nums = {1, 100};
  int k = 100000;
  EXPECT_EQ(9900000LL, solution.maxTotalValue(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumTotalSubarrayValueITest,
    ::testing::ValuesIn(MaximumTotalSubarrayValueISolution().getStrategyNames()));

}  // namespace problem_3689
}  // namespace leetcode
