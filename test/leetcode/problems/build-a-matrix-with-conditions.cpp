#include "leetcode/problems/build-a-matrix-with-conditions.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2392 {

class BuildAMatrixWithConditionsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BuildAMatrixWithConditionsSolution solution;
};

TEST_P(BuildAMatrixWithConditionsTest, Example1) {
  int k = 3;
  vector<vector<int>> rowConditions = {{1, 2}, {3, 2}};
  vector<vector<int>> colConditions = {{2, 1}, {3, 2}};
  
  vector<vector<int>> result = solution.buildMatrix(k, rowConditions, colConditions);
  
  // 验证结果非空
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.size(), k);
  for (const auto& row : result) {
    EXPECT_EQ(row.size(), k);
  }
  
  // 验证包含 1 到 k 各一次
  int count = 0;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (result[i][j] != 0) {
        count++;
      }
    }
  }
  EXPECT_EQ(count, k);
  
  // 验证行约束：1 在 2 上方
  int row1 = -1, row2 = -1;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (result[i][j] == 1) row1 = i;
      if (result[i][j] == 2) row2 = i;
    }
  }
  EXPECT_LT(row1, row2);
  
  // 验证行约束：3 在 2 上方
  int row3 = -1;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (result[i][j] == 3) row3 = i;
    }
  }
  EXPECT_LT(row3, row2);
  
  // 验证列约束：2 在 1 左侧
  int col1 = -1, col2 = -1;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (result[i][j] == 1) col1 = j;
      if (result[i][j] == 2) col2 = j;
    }
  }
  EXPECT_LT(col2, col1);
  
  // 验证列约束：3 在 2 左侧
  int col3 = -1;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (result[i][j] == 3) col3 = j;
    }
  }
  EXPECT_LT(col3, col2);
}

TEST_P(BuildAMatrixWithConditionsTest, Example2) {
  int k = 3;
  vector<vector<int>> rowConditions = {{1, 2}, {2, 3}, {3, 1}, {2, 3}};
  vector<vector<int>> colConditions = {{2, 1}};
  
  vector<vector<int>> result = solution.buildMatrix(k, rowConditions, colConditions);
  
  // 验证结果为空（存在环）
  EXPECT_TRUE(result.empty());
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BuildAMatrixWithConditionsTest,
    ::testing::ValuesIn(BuildAMatrixWithConditionsSolution().getStrategyNames()));

}  // namespace problem_2392
}  // namespace leetcode
