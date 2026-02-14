#include "leetcode/problems/champagne-tower.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_799 {

class ChampagneTowerTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ChampagneTowerSolution solution;
};

TEST_P(ChampagneTowerTest, Example1) {
  // poured = 1, query_row = 1, query_glass = 1
  // 倒1杯到顶层，顶层满了，没有溢出，所以第1行第1个杯子是空的
  int poured = 1;
  int query_row = 1;
  int query_glass = 1;
  double expected = 0.0;
  EXPECT_DOUBLE_EQ(expected, solution.champagneTower(poured, query_row, query_glass));
}

TEST_P(ChampagneTowerTest, Example2) {
  // poured = 2, query_row = 1, query_glass = 1
  // 倒2杯到顶层，顶层满1杯，溢出1杯，平均分给下一行两个杯子，各0.5杯
  int poured = 2;
  int query_row = 1;
  int query_glass = 1;
  double expected = 0.5;
  EXPECT_DOUBLE_EQ(expected, solution.champagneTower(poured, query_row, query_glass));
}

TEST_P(ChampagneTowerTest, Example3) {
  // poured = 100000009, query_row = 33, query_glass = 17
  // 大量香槟，中间位置会满
  int poured = 100000009;
  int query_row = 33;
  int query_glass = 17;
  double expected = 1.0;
  EXPECT_DOUBLE_EQ(expected, solution.champagneTower(poured, query_row, query_glass));
}

TEST_P(ChampagneTowerTest, ZeroPoured) {
  // 没有倒香槟，所有杯子都是空的
  int poured = 0;
  int query_row = 0;
  int query_glass = 0;
  double expected = 0.0;
  EXPECT_DOUBLE_EQ(expected, solution.champagneTower(poured, query_row, query_glass));
}

TEST_P(ChampagneTowerTest, TopGlassFull) {
  // 倒1杯，顶层满了
  int poured = 1;
  int query_row = 0;
  int query_glass = 0;
  double expected = 1.0;
  EXPECT_DOUBLE_EQ(expected, solution.champagneTower(poured, query_row, query_glass));
}

TEST_P(ChampagneTowerTest, SecondRowBothHalf) {
  // 倒2杯，第1行两个杯子各0.5
  int poured = 2;
  int query_row = 1;
  int query_glass = 0;
  double expected = 0.5;
  EXPECT_DOUBLE_EQ(expected, solution.champagneTower(poured, query_row, query_glass));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ChampagneTowerTest,
    ::testing::ValuesIn(ChampagneTowerSolution().getStrategyNames()));

}  // namespace problem_799
}  // namespace leetcode
