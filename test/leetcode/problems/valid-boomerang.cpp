#include "leetcode/problems/valid-boomerang.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1037 {

class ValidBoomerangTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ValidBoomerangSolution solution;
};

// 示例1：三点不共线，返回 true
TEST_P(ValidBoomerangTest, Example1) {
  vector<vector<int>> points = {{1, 1}, {2, 3}, {3, 2}};
  EXPECT_TRUE(solution.isBoomerang(points));
}

// 示例2：三点共线，返回 false
TEST_P(ValidBoomerangTest, Example2) {
  vector<vector<int>> points = {{1, 1}, {2, 2}, {3, 3}};
  EXPECT_FALSE(solution.isBoomerang(points));
}

// 测试：三点中有重复点
TEST_P(ValidBoomerangTest, DuplicatePoints) {
  vector<vector<int>> points = {{1, 1}, {1, 1}, {3, 2}};
  EXPECT_FALSE(solution.isBoomerang(points));
}

// 测试：三点中有两个点重复
TEST_P(ValidBoomerangTest, TwoDuplicatePoints) {
  vector<vector<int>> points = {{0, 0}, {1, 0}, {0, 0}};
  EXPECT_FALSE(solution.isBoomerang(points));
}

// 测试：垂直线（共线）
TEST_P(ValidBoomerangTest, VerticalLine) {
  vector<vector<int>> points = {{1, 1}, {1, 2}, {1, 3}};
  EXPECT_FALSE(solution.isBoomerang(points));
}

// 测试：水平线（共线）
TEST_P(ValidBoomerangTest, HorizontalLine) {
  vector<vector<int>> points = {{1, 1}, {2, 1}, {3, 1}};
  EXPECT_FALSE(solution.isBoomerang(points));
}

// 测试：L形（不共线）
TEST_P(ValidBoomerangTest, LShape) {
  vector<vector<int>> points = {{0, 0}, {0, 1}, {1, 0}};
  EXPECT_TRUE(solution.isBoomerang(points));
}

// 测试：三角形
TEST_P(ValidBoomerangTest, Triangle) {
  vector<vector<int>> points = {{0, 0}, {2, 0}, {1, 2}};
  EXPECT_TRUE(solution.isBoomerang(points));
}

// 测试：边界值（最大值）
TEST_P(ValidBoomerangTest, MaxValues) {
  vector<vector<int>> points = {{0, 0}, {100, 0}, {0, 100}};
  EXPECT_TRUE(solution.isBoomerang(points));
}

// 测试：三点全相同
TEST_P(ValidBoomerangTest, AllSamePoints) {
  vector<vector<int>> points = {{5, 5}, {5, 5}, {5, 5}};
  EXPECT_FALSE(solution.isBoomerang(points));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ValidBoomerangTest,
    ::testing::ValuesIn(ValidBoomerangSolution().getStrategyNames()));

}  // namespace problem_1037
}  // namespace leetcode
