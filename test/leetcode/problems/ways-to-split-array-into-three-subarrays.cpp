#include "leetcode/problems/ways-to-split-array-into-three-subarrays.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1712 {

class WaysToSplitArrayIntoThreeSubarraysTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  WaysToSplitArrayIntoThreeSubarraysSolution solution;
};

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, Example1) {
  vector<int> nums = {1, 1, 1};
  EXPECT_EQ(1, solution.waysToSplit(nums));
}

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, Example2) {
  vector<int> nums = {1, 2, 2, 2, 5, 0};
  EXPECT_EQ(3, solution.waysToSplit(nums));
}

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, Example3) {
  vector<int> nums = {3, 2, 1};
  EXPECT_EQ(0, solution.waysToSplit(nums));
}

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, AllZeros) {
  // 边界：全 0
  vector<int> nums = {0, 0, 0, 0, 0};
  // left 可以在位置 0, 1, 2
  // 对于每个 left，mid 和 right 也有很多选择
  // n=5, 可能的分割: C(4,2) = 6 种
  EXPECT_EQ(6, solution.waysToSplit(nums));
}

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, MinimumLength) {
  // 边界：最小长度 3
  vector<int> nums = {1, 2, 3};
  // [1] [2] [3]: 1 <= 2 <= 3 ✓
  EXPECT_EQ(1, solution.waysToSplit(nums));
}

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, NoValidSplit) {
  // 边界：递减序列，无法分割
  vector<int> nums = {10, 5, 1, 1};
  EXPECT_EQ(0, solution.waysToSplit(nums));
}

TEST_P(WaysToSplitArrayIntoThreeSubarraysTest, LargeNumbers) {
  // 边界：大数字
  vector<int> nums = {10000, 10000, 10000, 10000};
  // [10000] [10000] [10000, 10000]: 10000 <= 10000 <= 20000 ✓
  // [10000] [10000, 10000] [10000]: 10000 <= 20000 <= 10000 ✗
  // [10000, 10000] [10000] [10000]: 20000 <= 10000 ✗
  EXPECT_EQ(1, solution.waysToSplit(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, WaysToSplitArrayIntoThreeSubarraysTest,
    ::testing::ValuesIn(WaysToSplitArrayIntoThreeSubarraysSolution().getStrategyNames()));

}  // namespace problem_1712
}  // namespace leetcode
