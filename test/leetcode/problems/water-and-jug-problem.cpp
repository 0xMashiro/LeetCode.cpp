#include "leetcode/problems/water-and-jug-problem.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_365 {

class WaterAndJugProblemTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  WaterAndJugProblemSolution solution;
};

TEST_P(WaterAndJugProblemTest, Example1) {
  // x = 3, y = 5, target = 4 -> true
  EXPECT_TRUE(solution.canMeasureWater(3, 5, 4));
}

TEST_P(WaterAndJugProblemTest, Example2) {
  // x = 2, y = 6, target = 5 -> false
  EXPECT_FALSE(solution.canMeasureWater(2, 6, 5));
}

TEST_P(WaterAndJugProblemTest, Example3) {
  // x = 1, y = 2, target = 3 -> true
  EXPECT_TRUE(solution.canMeasureWater(1, 2, 3));
}

TEST_P(WaterAndJugProblemTest, TargetZero) {
  // target = 0 应该总是可以实现（两个空壶）
  EXPECT_TRUE(solution.canMeasureWater(3, 5, 0));
}

TEST_P(WaterAndJugProblemTest, TargetExceedsCapacity) {
  // target > x + y 应该返回 false
  EXPECT_FALSE(solution.canMeasureWater(3, 5, 10));
}

TEST_P(WaterAndJugProblemTest, EqualJugs) {
  // 相同容量的壶
  EXPECT_TRUE(solution.canMeasureWater(5, 5, 5));
  EXPECT_TRUE(solution.canMeasureWater(5, 5, 10));
  EXPECT_FALSE(solution.canMeasureWater(5, 5, 7));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, WaterAndJugProblemTest,
    ::testing::ValuesIn(WaterAndJugProblemSolution().getStrategyNames()));

}  // namespace problem_365
}  // namespace leetcode
