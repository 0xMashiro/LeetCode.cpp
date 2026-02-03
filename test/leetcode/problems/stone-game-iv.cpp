
#include "leetcode/problems/stone-game-iv.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1510 {

class StoneGameIvTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  StoneGameIvSolution solution;
};

// Example 1: n = 1, 期望返回 true
// Alice 可以移除 1 个石子，Bob 没有可操作的石子，Alice 赢
TEST_P(StoneGameIvTest, Example1) {
  int n = 1;
  bool expected = true;
  EXPECT_EQ(expected, solution.winnerSquareGame(n));
}

// Example 2: n = 2, 期望返回 false
// Alice 只能移除 1 个石子，剩下 1 个；Bob 移除 1 个石子获胜
TEST_P(StoneGameIvTest, Example2) {
  int n = 2;
  bool expected = false;
  EXPECT_EQ(expected, solution.winnerSquareGame(n));
}

// Example 3: n = 4, 期望返回 true
// 4 是完全平方数，Alice 可以直接移除 4 个石子获胜
TEST_P(StoneGameIvTest, Example3) {
  int n = 4;
  bool expected = true;
  EXPECT_EQ(expected, solution.winnerSquareGame(n));
}

// 额外测试：n = 0（边界情况）
TEST_P(StoneGameIvTest, EdgeCaseZero) {
  int n = 0;
  bool expected = false;
  EXPECT_EQ(expected, solution.winnerSquareGame(n));
}

// 额外测试：n = 3
// Alice 移除 1 -> 剩下 2, Bob 移除 1 -> 剩下 1, Alice 移除 1 -> 0, Alice 赢
// 所以 n=3 时 Alice 赢
TEST_P(StoneGameIvTest, CaseN3) {
  int n = 3;
  bool expected = true;
  EXPECT_EQ(expected, solution.winnerSquareGame(n));
}

// 额外测试：n = 7
TEST_P(StoneGameIvTest, CaseN7) {
  int n = 7;
  // 7 的博弈分析
  bool expected = false;
  EXPECT_EQ(expected, solution.winnerSquareGame(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, StoneGameIvTest,
    ::testing::ValuesIn(StoneGameIvSolution().getStrategyNames()));

}  // namespace problem_1510
}  // namespace leetcode
