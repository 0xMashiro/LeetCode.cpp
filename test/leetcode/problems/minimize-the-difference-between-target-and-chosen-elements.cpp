
#include "leetcode/problems/minimize-the-difference-between-target-and-chosen-elements.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1981 {

class MinimizeTheDifferenceBetweenTargetAndChosenElementsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimizeTheDifferenceBetweenTargetAndChosenElementsSolution solution;
};

// Example 1: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13, Output: 0
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, Example1) {
  vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int target = 13;
  EXPECT_EQ(0, solution.minimizeTheDifference(mat, target));
}

// Example 2: mat = [[1],[2],[3]], target = 100, Output: 94
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, Example2) {
  vector<vector<int>> mat = {{1}, {2}, {3}};
  int target = 100;
  EXPECT_EQ(94, solution.minimizeTheDifference(mat, target));
}

// Example 3: mat = [[1,2,9,8,7]], target = 6, Output: 1
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, Example3) {
  vector<vector<int>> mat = {{1, 2, 9, 8, 7}};
  int target = 6;
  EXPECT_EQ(1, solution.minimizeTheDifference(mat, target));
}

// 边界测试：单行单列
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, SingleRowSingleCol) {
  vector<vector<int>> mat = {{5}};
  int target = 5;
  EXPECT_EQ(0, solution.minimizeTheDifference(mat, target));
}

// 边界测试：单行多列
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, SingleRowMultipleCols) {
  vector<vector<int>> mat = {{1, 10, 20, 30}};
  int target = 15;
  EXPECT_EQ(5, solution.minimizeTheDifference(mat, target));  // |10-15| = 5 或 |20-15| = 5
}

// 边界测试：多行单列
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, MultipleRowsSingleCol) {
  vector<vector<int>> mat = {{5}, {10}, {15}};
  int target = 30;
  EXPECT_EQ(0, solution.minimizeTheDifference(mat, target));  // 5+10+15 = 30
}

// 边界测试：target 很小
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, SmallTarget) {
  vector<vector<int>> mat = {{10, 20}, {15, 25}};
  int target = 1;
  EXPECT_EQ(24, solution.minimizeTheDifference(mat, target));  // 最小和 = 10+15 = 25, |25-1| = 24
}

// 边界测试：target 很大
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, LargeTarget) {
  vector<vector<int>> mat = {{1, 2}, {3, 4}};
  int target = 1000;
  // 最大和 = 2 + 4 = 6
  EXPECT_EQ(994, solution.minimizeTheDifference(mat, target));
}

// 边界测试：所有元素相同
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, AllSameElements) {
  vector<vector<int>> mat = {{5, 5, 5}, {5, 5, 5}};
  int target = 11;
  EXPECT_EQ(1, solution.minimizeTheDifference(mat, target));  // 和 = 10，|10-11| = 1
}

// 边界测试：target 恰好等于某个可能的和
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, ExactMatch) {
  vector<vector<int>> mat = {{1, 3, 5}, {2, 4, 6}};
  int target = 7;  // 1+6=7, 3+4=7, 5+2=7
  EXPECT_EQ(0, solution.minimizeTheDifference(mat, target));
}

// 边界测试：最大值约束
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, MaxConstraints) {
  // m=70, n=70, 所有元素为 70
  vector<vector<int>> mat(70, vector<int>(70, 70));
  int target = 2450;  // 70 * 70 / 2 = 2450，正好是总和的一半
  // 每行只能选一个 70，总和 = 70 * 70 = 4900
  EXPECT_EQ(2450, solution.minimizeTheDifference(mat, target));  // |4900-2450| = 2450
}

// 边界测试：target 为 1，最小和接近 target
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, TargetOne) {
  vector<vector<int>> mat = {{1, 2}, {1, 2}};
  int target = 1;
  // 最小和 = 1+1 = 2，|2-1| = 1
  EXPECT_EQ(1, solution.minimizeTheDifference(mat, target));
}

// 边界测试：多个相同值导致重复和
TEST_P(MinimizeTheDifferenceBetweenTargetAndChosenElementsTest, DuplicateSums) {
  vector<vector<int>> mat = {{1, 2}, {2, 1}};  // 两种选法都得到和 3
  int target = 3;
  EXPECT_EQ(0, solution.minimizeTheDifference(mat, target));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimizeTheDifferenceBetweenTargetAndChosenElementsTest,
    ::testing::ValuesIn(MinimizeTheDifferenceBetweenTargetAndChosenElementsSolution().getStrategyNames()));

}  // namespace problem_1981
}  // namespace leetcode
