#include "leetcode/problems/trapping-rain-water.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_42 {

class TrappingRainWaterTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TrappingRainWaterSolution solution;
};

// 题目示例 1
TEST_P(TrappingRainWaterTest, Example1) {
  vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int expected = 6;
  EXPECT_EQ(expected, solution.trap(height));
}

// 题目示例 2
TEST_P(TrappingRainWaterTest, Example2) {
  vector<int> height = {4, 2, 0, 3, 2, 5};
  int expected = 9;
  EXPECT_EQ(expected, solution.trap(height));
}

// 边界情况：空数组
TEST_P(TrappingRainWaterTest, EmptyArray) {
  vector<int> height = {};
  int expected = 0;
  EXPECT_EQ(expected, solution.trap(height));
}

// 边界情况：单元素
TEST_P(TrappingRainWaterTest, SingleElement) {
  vector<int> height = {5};
  int expected = 0;
  EXPECT_EQ(expected, solution.trap(height));
}

// 边界情况：两个元素
TEST_P(TrappingRainWaterTest, TwoElements) {
  vector<int> height = {4, 2};
  int expected = 0;
  EXPECT_EQ(expected, solution.trap(height));
}

// 边界情况：单调递增，无法积水
TEST_P(TrappingRainWaterTest, MonotonicIncreasing) {
  vector<int> height = {0, 1, 2, 3, 4, 5};
  int expected = 0;
  EXPECT_EQ(expected, solution.trap(height));
}

// 边界情况：单调递减，无法积水
TEST_P(TrappingRainWaterTest, MonotonicDecreasing) {
  vector<int> height = {5, 4, 3, 2, 1, 0};
  int expected = 0;
  EXPECT_EQ(expected, solution.trap(height));
}

// 边界情况：所有高度相同
TEST_P(TrappingRainWaterTest, AllSameHeight) {
  vector<int> height = {3, 3, 3, 3, 3};
  int expected = 0;
  EXPECT_EQ(expected, solution.trap(height));
}

// 特殊情况：V 字形
TEST_P(TrappingRainWaterTest, VShape) {
  vector<int> height = {5, 0, 5};
  int expected = 5;
  EXPECT_EQ(expected, solution.trap(height));
}

// 特殊情况：多个积水区域
TEST_P(TrappingRainWaterTest, MultiplePools) {
  vector<int> height = {3, 0, 2, 0, 4};
  int expected = 7;  // (3-0) + (3-2) + (4-0) = 3 + 1 + 4 = 8? 不对，重新算
  // 位置 1: min(3, 4) - 0 = 3
  // 位置 2: min(3, 4) - 2 = 1  
  // 位置 3: min(4, 4) - 0 = 4
  // 总计: 3 + 1 + 4 = 8？等等，再仔细算
  // left_max:  [3, 3, 3, 3, 4]
  // right_max: [4, 4, 4, 4, 4]
  // 位置 0: min(3,4) - 3 = 0
  // 位置 1: min(3,4) - 0 = 3
  // 位置 2: min(3,4) - 2 = 1
  // 位置 3: min(3,4) - 0 = 3
  // 位置 4: min(4,4) - 4 = 0
  // 总计: 3 + 1 + 3 = 7
  EXPECT_EQ(expected, solution.trap(height));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TrappingRainWaterTest,
    ::testing::ValuesIn(TrappingRainWaterSolution().getStrategyNames()));

}  // namespace problem_42
}  // namespace leetcode
