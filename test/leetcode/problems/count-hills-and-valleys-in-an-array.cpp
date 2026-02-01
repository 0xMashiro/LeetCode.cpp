#include "leetcode/problems/count-hills-and-valleys-in-an-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2210 {

class CountHillsAndValleysInAnArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountHillsAndValleysInAnArraySolution solution;
};

// 示例 1: [2,4,1,1,6,5] -> 压缩后 [2,4,1,6,5]
// i=1(4): 山峰; i=2(1): 山谷; i=3(6): 山峰 -> 共 3 个
TEST_P(CountHillsAndValleysInAnArrayTest, Example1) {
  vector<int> nums = {2, 4, 1, 1, 6, 5};
  EXPECT_EQ(3, solution.countHillValley(nums));
}

// 示例 2: [6,6,5,5,4,1] -> 压缩后 [6,5,4,1]
// 没有山峰或山谷 -> 0 个
TEST_P(CountHillsAndValleysInAnArrayTest, Example2) {
  vector<int> nums = {6, 6, 5, 5, 4, 1};
  EXPECT_EQ(0, solution.countHillValley(nums));
}

// 全相同元素 -> 压缩后只有一个元素
TEST_P(CountHillsAndValleysInAnArrayTest, AllSameElements) {
  vector<int> nums = {1, 1, 1, 1, 1};
  EXPECT_EQ(0, solution.countHillValley(nums));
}

// 严格递增 -> 无山峰或山谷
TEST_P(CountHillsAndValleysInAnArrayTest, StrictlyIncreasing) {
  vector<int> nums = {1, 2, 3, 4, 5};
  EXPECT_EQ(0, solution.countHillValley(nums));
}

// 严格递减 -> 无山峰或山谷
TEST_P(CountHillsAndValleysInAnArrayTest, StrictlyDecreasing) {
  vector<int> nums = {5, 4, 3, 2, 1};
  EXPECT_EQ(0, solution.countHillValley(nums));
}

// 只有山峰: [1,5,1] -> 5 是山峰
TEST_P(CountHillsAndValleysInAnArrayTest, OnlyHill) {
  vector<int> nums = {1, 5, 1};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 只有山谷: [5,1,5] -> 1 是山谷
TEST_P(CountHillsAndValleysInAnArrayTest, OnlyValley) {
  vector<int> nums = {5, 1, 5};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 多个连续相同元素的山峰: [1,3,3,3,1] -> 压缩后 [1,3,1]，3 是山峰
TEST_P(CountHillsAndValleysInAnArrayTest, HillWithDuplicates) {
  vector<int> nums = {1, 3, 3, 3, 1};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 多个连续相同元素的山谷: [5,2,2,2,5] -> 压缩后 [5,2,5]，2 是山谷
TEST_P(CountHillsAndValleysInAnArrayTest, ValleyWithDuplicates) {
  vector<int> nums = {5, 2, 2, 2, 5};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 最小长度: [1,2,1] -> 2 是山峰
TEST_P(CountHillsAndValleysInAnArrayTest, MinimumLength) {
  vector<int> nums = {1, 2, 1};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 山峰 + 山谷组合: [1,3,1,3,1] -> 压缩后 [1,3,1,3,1]
// i=1(3): 山峰; i=2(1): 山谷; i=3(3): 山峰 -> 共 3 个
TEST_P(CountHillsAndValleysInAnArrayTest, HillAndValley) {
  vector<int> nums = {1, 3, 1, 3, 1};
  EXPECT_EQ(3, solution.countHillValley(nums));
}

// 先谷后峰: [5,1,5,1,5] -> 压缩后 [5,1,5,1,5]
// i=1(1): 山谷; i=2(5): 山峰; i=3(1): 山谷 -> 共 3 个
TEST_P(CountHillsAndValleysInAnArrayTest, ValleyThenHill) {
  vector<int> nums = {5, 1, 5, 1, 5};
  EXPECT_EQ(3, solution.countHillValley(nums));
}

// 平台后下降: [1,3,3,2] -> 压缩后 [1,3,2]
// i=1(3): 3>1 且 3>2，是山峰 -> 1 个
TEST_P(CountHillsAndValleysInAnArrayTest, PlateauThenDown) {
  vector<int> nums = {1, 3, 3, 2};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 平台后上升: [5,2,2,3] -> 压缩后 [5,2,3]
// i=1(2): 2<5 且 2<3，是山谷 -> 1 个
TEST_P(CountHillsAndValleysInAnArrayTest, PlateauThenUp) {
  vector<int> nums = {5, 2, 2, 3};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 平板形状: [1,2,2,1] -> 压缩后 [1,2,1]，2 是山峰
TEST_P(CountHillsAndValleysInAnArrayTest, FlatTopHill) {
  vector<int> nums = {1, 2, 2, 1};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 平板形状山谷: [5,3,3,5] -> 压缩后 [5,3,5]，3 是山谷
TEST_P(CountHillsAndValleysInAnArrayTest, FlatBottomValley) {
  vector<int> nums = {5, 3, 3, 5};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

// 波浪形: [1,3,2,4,3] -> 压缩后 [1,3,2,4,3]
// i=1(3): 山峰; i=2(2): 山谷; i=3(4): 山峰 -> 共 3 个
TEST_P(CountHillsAndValleysInAnArrayTest, WavePattern) {
  vector<int> nums = {1, 3, 2, 4, 3};
  EXPECT_EQ(3, solution.countHillValley(nums));
}

// 边界：中间有多个相等元素 [1,1,2,2,1,1] -> 压缩后 [1,2,1]，2 是山峰
TEST_P(CountHillsAndValleysInAnArrayTest, MultiDuplicates) {
  vector<int> nums = {1, 1, 2, 2, 1, 1};
  EXPECT_EQ(1, solution.countHillValley(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountHillsAndValleysInAnArrayTest,
    ::testing::ValuesIn(CountHillsAndValleysInAnArraySolution().getStrategyNames()));

}  // namespace problem_2210
}  // namespace leetcode
