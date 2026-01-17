
#include "leetcode/problems/find-the-largest-area-of-square-inside-two-rectangles.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3047 {

class FindTheLargestAreaOfSquareInsideTwoRectanglesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheLargestAreaOfSquareInsideTwoRectanglesSolution solution;
};

TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, Example1) {
  vector<vector<int>> bottomLeft = {{1, 1}, {2, 2}, {3, 1}};
  vector<vector<int>> topRight = {{3, 3}, {4, 4}, {6, 6}};
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 1);
}

TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, Example2) {
  vector<vector<int>> bottomLeft = {{1, 1}, {1, 3}, {1, 5}};
  vector<vector<int>> topRight = {{5, 5}, {5, 7}, {5, 9}};
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 4);
}

TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, Example3) {
  vector<vector<int>> bottomLeft = {{1, 1}, {2, 2}, {1, 2}};
  vector<vector<int>> topRight = {{3, 3}, {4, 4}, {3, 4}};
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 1);
}

TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, Example4) {
  vector<vector<int>> bottomLeft = {{1, 1}, {3, 3}, {3, 1}};
  vector<vector<int>> topRight = {{2, 2}, {4, 4}, {4, 2}};
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 0);
}

// 添加一些额外的测试用例
TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, NoIntersection) {
  vector<vector<int>> bottomLeft = {{1, 1}, {5, 5}};
  vector<vector<int>> topRight = {{2, 2}, {6, 6}};
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 0);
}

TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, PerfectOverlap) {
  vector<vector<int>> bottomLeft = {{1, 1}, {1, 1}};
  vector<vector<int>> topRight = {{5, 5}, {5, 5}};
  // 宽度和高度都是4，最大正方形边长4，面积16
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 16);
}

TEST_P(FindTheLargestAreaOfSquareInsideTwoRectanglesTest, LargeCoordinates) {
  vector<vector<int>> bottomLeft = {{1, 1}, {1000000, 1000000}};
  vector<vector<int>> topRight = {{10000000, 10000000}, {2000000, 2000000}};
  // 相交区域: x1 = max(1,1000000)=1000000, y1=1000000, x2=min(10000000,2000000)=2000000, y2=min(10000000,2000000)=2000000
  // 宽度=1000000, 高度=1000000, 边长=1000000, 面积=10^12
  EXPECT_EQ(solution.largestSquareArea(bottomLeft, topRight), 1000000000000LL);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindTheLargestAreaOfSquareInsideTwoRectanglesTest,
    ::testing::ValuesIn(FindTheLargestAreaOfSquareInsideTwoRectanglesSolution().getStrategyNames()));

}  // namespace problem_3047
}  // namespace leetcode