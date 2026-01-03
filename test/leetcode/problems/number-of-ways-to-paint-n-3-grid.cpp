#include "leetcode/problems/number-of-ways-to-paint-n-3-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1411 {

class NumberOfWaysToPaintN3GridTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfWaysToPaintN3GridSolution solution;
};

TEST_P(NumberOfWaysToPaintN3GridTest, Example1) {
  EXPECT_EQ(solution.numOfWays(1), 12);
}

TEST_P(NumberOfWaysToPaintN3GridTest, Example2) {
  EXPECT_EQ(solution.numOfWays(5000), 30228214);
}

// 添加一些额外的测试用例
TEST_P(NumberOfWaysToPaintN3GridTest, N2) {
  // 手动计算 n=2 的结果
  // 用动态规划验证，先计算预期值
  // 我们可以运行一次 solution1(2) 得到结果，但为了不依赖实现，我们预先计算
  // 计算得到 n=2 时结果为 54
  EXPECT_EQ(solution.numOfWays(2), 54);
}

TEST_P(NumberOfWaysToPaintN3GridTest, N3) {
  // n=3 的结果为 246
  EXPECT_EQ(solution.numOfWays(3), 246);
}

TEST_P(NumberOfWaysToPaintN3GridTest, N4) {
  // n=4 的结果为 1122
  EXPECT_EQ(solution.numOfWays(4), 1122);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfWaysToPaintN3GridTest,
    ::testing::ValuesIn(NumberOfWaysToPaintN3GridSolution().getStrategyNames()));

}  // namespace problem_1411
}  // namespace leetcode