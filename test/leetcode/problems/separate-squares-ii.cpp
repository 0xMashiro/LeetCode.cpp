#include "leetcode/problems/separate-squares-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3454 {

class SeparateSquaresIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SeparateSquaresIiSolution solution;
};

TEST_P(SeparateSquaresIiTest, Example1) {
  vector<vector<int>> squares = {{0, 0, 1}, {2, 2, 1}};
  double expected = 1.0;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresIiTest, Example2) {
  vector<vector<int>> squares = {{0, 0, 2}, {1, 1, 1}};
  double expected = 1.0;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

// 自定义测试用例
TEST_P(SeparateSquaresIiTest, SingleSquare) {
  vector<vector<int>> squares = {{0, 0, 2}};
  // 总面积 = 4，一半面积 = 2，线应该在 y = 1 处（切割正方形为两个面积为 2 的矩形）
  double expected = 1.0;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresIiTest, TwoNonOverlappingSquaresSameHeight) {
  vector<vector<int>> squares = {{0, 0, 1}, {2, 0, 1}};
  // 两个正方形面积各为1，总面积2，一半=1
  // 当 y=0.5 时，每个正方形线下部分面积 = 1*0.5 = 0.5，总线下面积 = 1
  // 所以最小 y 应该是 0.5
  double expected = 0.5;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresIiTest, TwoOverlappingSquares) {
  vector<vector<int>> squares = {{0, 0, 2}, {1, 0, 2}};
  // 两个正方形重叠部分为宽度1，高度2，重叠面积=2
  // 总面积 = 4 + 4 - 2 = 6，一半=3
  // 当 y=1 时，每个正方形线下矩形面积=宽度*高度=2*1=2，重叠宽度1，线下并集面积=2+2-1=3
  // 所以 y=1 满足，且是最小 y
  double expected = 1.0;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresIiTest, SquaresAtDifferentHeights) {
  vector<vector<int>> squares = {{0, 0, 1}, {0, 2, 1}};
  // 两个正方形上下分开，不重叠
  // 总面积=2，一半=1
  // 第一个正方形面积1，第二个面积1
  // 当 y=1 时，线下只有第一个正方形面积1，符合
  double expected = 1.0;
  double result = solution.separateSquares(squares);
  EXPECT_NEAR(expected, result, 1e-5);
}

TEST_P(SeparateSquaresIiTest, LargeNumbers) {
  vector<vector<int>> squares = {{0, 0, 1000000000}, {0, 500000000, 1000000000}};
  // 两个大正方形，部分重叠
  // 总面积需要计算，但算法应该能处理大数
  double result = solution.separateSquares(squares);
  // 不验证具体值，只确保不崩溃
  EXPECT_TRUE(result >= 0 && result <= 2000000000);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SeparateSquaresIiTest,
    ::testing::ValuesIn(SeparateSquaresIiSolution().getStrategyNames()));

}  // namespace problem_3454
}  // namespace leetcode