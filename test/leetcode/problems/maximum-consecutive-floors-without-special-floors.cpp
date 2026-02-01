#include "leetcode/problems/maximum-consecutive-floors-without-special-floors.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2274 {

class MaximumConsecutiveFloorsWithoutSpecialFloorsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumConsecutiveFloorsWithoutSpecialFloorsSolution solution;
};

// Example 1: bottom = 2, top = 9, special = [4,6], expected = 3
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, Example1) {
  int bottom = 2;
  int top = 9;
  vector<int> special = {4, 6};
  EXPECT_EQ(3, solution.maxConsecutive(bottom, top, special));
}

// Example 2: bottom = 6, top = 8, special = [7,6,8], expected = 0
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, Example2) {
  int bottom = 6;
  int top = 8;
  vector<int> special = {7, 6, 8};
  EXPECT_EQ(0, solution.maxConsecutive(bottom, top, special));
}

// 边界测试：只有一个特殊楼层
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, SingleSpecial) {
  int bottom = 1;
  int top = 10;
  vector<int> special = {5};
  // 左边有 5-1=4 层 (1,2,3,4)，右边有 10-5=5 层 (6,7,8,9,10)
  EXPECT_EQ(5, solution.maxConsecutive(bottom, top, special));
}

// 边界测试：特殊楼层在边界
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, SpecialAtBoundaries) {
  int bottom = 1;
  int top = 5;
  vector<int> special = {1, 5};
  // 中间有 5-1-1=3 层 (2,3,4)
  EXPECT_EQ(3, solution.maxConsecutive(bottom, top, special));
}

// 边界测试：所有楼层都是特殊楼层
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, AllSpecial) {
  int bottom = 1;
  int top = 3;
  vector<int> special = {1, 2, 3};
  EXPECT_EQ(0, solution.maxConsecutive(bottom, top, special));
}

// 边界测试：没有特殊楼层（但题目约束 special.length >= 1，这里测试最小情况）
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, MinSpecial) {
  int bottom = 1;
  int top = 100;
  vector<int> special = {50};
  // 最大间隔是 max(50-1=49, 100-50=50) = 50
  EXPECT_EQ(50, solution.maxConsecutive(bottom, top, special));
}

// 测试大数值
TEST_P(MaximumConsecutiveFloorsWithoutSpecialFloorsTest, LargeValues) {
  int bottom = 1;
  int top = 1000000000;
  vector<int> special = {500000000};
  EXPECT_EQ(500000000, solution.maxConsecutive(bottom, top, special));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumConsecutiveFloorsWithoutSpecialFloorsTest,
    ::testing::ValuesIn(MaximumConsecutiveFloorsWithoutSpecialFloorsSolution().getStrategyNames()));

}  // namespace problem_2274
}  // namespace leetcode
