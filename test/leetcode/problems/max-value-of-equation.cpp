#include "leetcode/problems/max-value-of-equation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1499 {

class MaxValueOfEquationTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaxValueOfEquationSolution solution;
};

TEST_P(MaxValueOfEquationTest, Example1) {
  vector<vector<int>> points = {{1, 3}, {2, 0}, {5, 10}, {6, -10}};
  int k = 1;
  // 第一和第二点：3 + 0 + |1 - 2| = 4
  // 第三和第四点：10 + (-10) + |5 - 6| = 1
  EXPECT_EQ(4, solution.findMaxValueOfEquation(points, k));
}

TEST_P(MaxValueOfEquationTest, Example2) {
  vector<vector<int>> points = {{0, 0}, {3, 0}, {9, 2}};
  int k = 3;
  // 第一和第二点：0 + 0 + |0 - 3| = 3
  EXPECT_EQ(3, solution.findMaxValueOfEquation(points, k));
}

TEST_P(MaxValueOfEquationTest, SinglePair) {
  // 只有两个点，必须选这对
  vector<vector<int>> points = {{1, 2}, {3, 4}};
  int k = 5;
  // 2 + 4 + |1 - 3| = 8
  EXPECT_EQ(8, solution.findMaxValueOfEquation(points, k));
}

TEST_P(MaxValueOfEquationTest, LargerK) {
  // k 足够大，可以选择任意点对
  vector<vector<int>> points = {{1, 1}, {2, 3}, {3, 5}, {4, 2}};
  int k = 10;
  // 最佳应该是 (2,3) 和 (3,5)：3 + 5 + 1 = 9
  // 或者是 (1,1) 和 (3,5)：1 + 5 + 2 = 8
  // 或者是 (2,3) 和 (4,2)：3 + 2 + 2 = 7
  EXPECT_EQ(9, solution.findMaxValueOfEquation(points, k));
}

TEST_P(MaxValueOfEquationTest, NegativeY) {
  // y 值可以是负数
  vector<vector<int>> points = {{-10, -5}, {-5, -10}, {0, -15}};
  int k = 10;
  // (-5) + (-10) + |-10 - (-5)| = -15 + 5 = -10
  // (-10) + (-15) + |-5 - 0| = -25 + 5 = -20
  EXPECT_EQ(-10, solution.findMaxValueOfEquation(points, k));
}

TEST_P(MaxValueOfEquationTest, AllSameY) {
  // y 值相同，看 x 的差值
  vector<vector<int>> points = {{1, 5}, {2, 5}, {3, 5}, {4, 5}};
  int k = 2;
  // 选择 (1,5) 和 (3,5)：5 + 5 + 2 = 12
  // 或 (2,5) 和 (4,5)：5 + 5 + 2 = 12
  EXPECT_EQ(12, solution.findMaxValueOfEquation(points, k));
}

TEST_P(MaxValueOfEquationTest, KExactlyMatch) {
  // k 刚好等于某些点对的 x 差值
  vector<vector<int>> points = {{0, 0}, {5, 10}, {10, 0}};
  int k = 5;
  // (0,0) 和 (5,10)：0 + 10 + 5 = 15
  // (5,10) 和 (10,0)：10 + 0 + 5 = 15
  EXPECT_EQ(15, solution.findMaxValueOfEquation(points, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaxValueOfEquationTest,
    ::testing::ValuesIn(MaxValueOfEquationSolution().getStrategyNames()));

}  // namespace problem_1499
}  // namespace leetcode
