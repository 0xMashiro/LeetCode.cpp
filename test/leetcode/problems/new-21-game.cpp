#include "leetcode/problems/new-21-game.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_837 {

class New21GameTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  New21GameSolution solution;
};

TEST_P(New21GameTest, Example1) {
  // n = 10, k = 1, maxPts = 10
  // Alice 抽一张卡就停止，分数范围 [1, 10]
  // 分数 <= 10 的概率 = 1
  EXPECT_NEAR(solution.new21Game(10, 1, 10), 1.00000, 1e-5);
}

TEST_P(New21GameTest, Example2) {
  // n = 6, k = 1, maxPts = 10
  // Alice 抽一张卡就停止，分数范围 [1, 10]
  // 分数 <= 6 的概率 = 6/10 = 0.6
  EXPECT_NEAR(solution.new21Game(6, 1, 10), 0.60000, 1e-5);
}

TEST_P(New21GameTest, Example3) {
  // n = 21, k = 17, maxPts = 10
  EXPECT_NEAR(solution.new21Game(21, 17, 10), 0.73278, 1e-5);
}

TEST_P(New21GameTest, Edge_k_is_0) {
  // k = 0 时不需要抽卡，直接判断 0 <= n
  EXPECT_NEAR(solution.new21Game(5, 0, 10), 1.00000, 1e-5);
  EXPECT_NEAR(solution.new21Game(0, 0, 10), 1.00000, 1e-5);
}

TEST_P(New21GameTest, Edge_n_equals_k_minus_1) {
  // n = k - 1 时，停止时分数至少为 k，必然 > n
  // 所以概率为 0（当 k > 0 时）
  EXPECT_NEAR(solution.new21Game(0, 1, 10), 0.00000, 1e-5);
  EXPECT_NEAR(solution.new21Game(4, 5, 10), 0.00000, 1e-5);
}

TEST_P(New21GameTest, Edge_n_very_large) {
  // n >= k-1+maxPts 时，所有可能结果都 <= n
  EXPECT_NEAR(solution.new21Game(100, 10, 10), 1.00000, 1e-5);
  EXPECT_NEAR(solution.new21Game(19, 10, 10), 1.00000, 1e-5);  // 9+10=19
}

TEST_P(New21GameTest, Edge_maxPts_is_1) {
  // maxPts = 1 时，每次只能抽 1
  // n = 5, k = 3: 抽卡序列 0->1->2->3，最终分数为 3
  // 3 <= 5，所以概率为 1
  EXPECT_NEAR(solution.new21Game(5, 3, 1), 1.00000, 1e-5);
  
  // n = 2, k = 3: 最终分数为 3 > 2，概率为 0
  EXPECT_NEAR(solution.new21Game(2, 3, 1), 0.00000, 1e-5);
}

TEST_P(New21GameTest, SmallCase) {
  // n = 2, k = 2, maxPts = 2
  // 从 0 开始，抽卡直到 >= 2
  // 可能的情况：
  // - 抽到 2：停止，分数 2 <= 2 ✓，概率 1/2
  // - 抽到 1：继续，然后从 {1,2} 中抽
  //   - 抽到 1：分数 2 <= 2 ✓，概率 1/2 * 1/2 = 1/4
  //   - 抽到 2：分数 3 > 2 ✗，概率 1/2 * 1/2 = 1/4
  // 总概率 = 1/2 + 1/4 = 3/4 = 0.75
  EXPECT_NEAR(solution.new21Game(2, 2, 2), 0.75000, 1e-5);
}

TEST_P(New21GameTest, AdditionalCase1) {
  // n = 3, k = 2, maxPts = 3
  // dp[2] = dp[3] = 1 (停止时分数 <= 3)
  // dp[1] = (dp[2] + dp[3] + dp[4]) / 3 = (1 + 1 + 0) / 3 = 2/3
  // dp[0] = (dp[1] + dp[2] + dp[3]) / 3 = (2/3 + 1 + 1) / 3 = 8/9
  EXPECT_NEAR(solution.new21Game(3, 2, 3), 8.0/9.0, 1e-5);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, New21GameTest,
    ::testing::ValuesIn(New21GameSolution().getStrategyNames()));

}  // namespace problem_837
}  // namespace leetcode
