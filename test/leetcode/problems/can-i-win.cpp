#include "leetcode/problems/can-i-win.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_464 {

class CanIWinTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CanIWinSolution solution;
};

TEST_P(CanIWinTest, Example1) {
  // maxChoosableInteger = 10, desiredTotal = 11
  // 无论先手选什么，后手都能赢
  EXPECT_FALSE(solution.canIWin(10, 11));
}

TEST_P(CanIWinTest, Example2) {
  // maxChoosableInteger = 10, desiredTotal = 0
  // 目标为0，先手直接获胜
  EXPECT_TRUE(solution.canIWin(10, 0));
}

TEST_P(CanIWinTest, Example3) {
  // maxChoosableInteger = 10, desiredTotal = 1
  // 先手选1即可获胜
  EXPECT_TRUE(solution.canIWin(10, 1));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CanIWinTest,
    ::testing::ValuesIn(CanIWinSolution().getStrategyNames()));

}  // namespace problem_464
}  // namespace leetcode
