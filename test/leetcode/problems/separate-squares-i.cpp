#include "leetcode/problems/separate-squares-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3453 {

class SeparateSquaresITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SeparateSquaresISolution solution;
};

TEST_P(SeparateSquaresITest, Example1) {
  vector<vector<int>> squares = {{0, 0, 1}, {2, 2, 1}};
  double expected = 1.00000;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresITest, Example2) {
  vector<vector<int>> squares = {{0, 0, 2}, {1, 1, 1}};
  double expected = 1.16667;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

// 添加额外测试
TEST_P(SeparateSquaresITest, SingleSquare) {
  vector<vector<int>> squares = {{0, 0, 2}};
  // 总面积4，一半面积2，线在y=1处
  double expected = 1.0;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresITest, OverlappingSquares) {
  vector<vector<int>> squares = {{0, 0, 2}, {0, 0, 1}};
  // 总面积4+1=5，一半2.5。
  // 计算得 t = 5/6 ≈ 0.83333
  double expected = 5.0 / 6.0; // 0.8333333333
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SeparateSquaresITest,
    ::testing::ValuesIn(SeparateSquaresISolution().getStrategyNames()));

}  // namespace problem_3453
}  // namespace leetcode