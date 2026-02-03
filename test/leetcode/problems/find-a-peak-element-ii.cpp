#include "leetcode/problems/find-a-peak-element-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1901 {

class FindAPeakElementIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindAPeakElementIiSolution solution;
  
  // 验证返回的位置是否是峰值
  bool isPeak(vector<vector<int>>& mat, vector<int>& pos) {
    int i = pos[0], j = pos[1];
    int m = mat.size(), n = mat[0].size();
    int val = mat[i][j];
    
    // 上方
    if (i > 0 && mat[i - 1][j] >= val) return false;
    // 下方
    if (i < m - 1 && mat[i + 1][j] >= val) return false;
    // 左方
    if (j > 0 && mat[i][j - 1] >= val) return false;
    // 右方
    if (j < n - 1 && mat[i][j + 1] >= val) return false;
    
    return true;
  }
};

TEST_P(FindAPeakElementIiTest, Example1) {
  vector<vector<int>> mat = {{1, 4}, {3, 2}};
  vector<int> result = solution.findPeakGrid(mat);
  // 验证返回的是有效的峰值位置
  EXPECT_TRUE(isPeak(mat, result));
  // 验证返回的是题目中的预期位置之一
  bool validPos = (result[0] == 0 && result[1] == 1) || (result[0] == 1 && result[1] == 0);
  EXPECT_TRUE(validPos);
}

TEST_P(FindAPeakElementIiTest, Example2) {
  vector<vector<int>> mat = {{10, 20, 15}, {21, 30, 14}, {7, 16, 32}};
  vector<int> result = solution.findPeakGrid(mat);
  // 验证返回的是有效的峰值位置
  EXPECT_TRUE(isPeak(mat, result));
  // 验证返回的是题目中的预期位置之一
  bool validPos = (result[0] == 1 && result[1] == 1) || (result[0] == 2 && result[1] == 2);
  EXPECT_TRUE(validPos);
}

TEST_P(FindAPeakElementIiTest, SingleRow) {
  vector<vector<int>> mat = {{1, 2, 3, 4, 5}};
  vector<int> result = solution.findPeakGrid(mat);
  EXPECT_TRUE(isPeak(mat, result));
  // 最大值5在位置[0,4]，是峰值
  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 4);
}

TEST_P(FindAPeakElementIiTest, SingleColumn) {
  vector<vector<int>> mat = {{1}, {3}, {2}, {4}, {5}};
  vector<int> result = solution.findPeakGrid(mat);
  EXPECT_TRUE(isPeak(mat, result));
  // 最大值5在位置[4,0]，是峰值
  EXPECT_EQ(result[0], 4);
  EXPECT_EQ(result[1], 0);
}

TEST_P(FindAPeakElementIiTest, SingleElement) {
  vector<vector<int>> mat = {{42}};
  vector<int> result = solution.findPeakGrid(mat);
  EXPECT_TRUE(isPeak(mat, result));
  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 0);
}

TEST_P(FindAPeakElementIiTest, LargerMatrix) {
  vector<vector<int>> mat = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  vector<int> result = solution.findPeakGrid(mat);
  EXPECT_TRUE(isPeak(mat, result));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindAPeakElementIiTest,
    ::testing::ValuesIn(FindAPeakElementIiSolution().getStrategyNames()));

}  // namespace problem_1901
}  // namespace leetcode
