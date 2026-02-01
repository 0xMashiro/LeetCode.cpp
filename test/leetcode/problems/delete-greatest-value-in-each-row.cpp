#include "leetcode/problems/delete-greatest-value-in-each-row.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2500 {

class DeleteGreatestValueInEachRowTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DeleteGreatestValueInEachRowSolution solution;
};

TEST_P(DeleteGreatestValueInEachRowTest, Example1) {
  vector<vector<int>> grid = {{1, 2, 4}, {3, 3, 1}};
  EXPECT_EQ(8, solution.deleteGreatestValue(grid));
}

TEST_P(DeleteGreatestValueInEachRowTest, Example2) {
  vector<vector<int>> grid = {{10}};
  EXPECT_EQ(10, solution.deleteGreatestValue(grid));
}

TEST_P(DeleteGreatestValueInEachRowTest, SingleRow) {
  vector<vector<int>> grid = {{5, 3, 8, 1}};
  // 排序后: [8, 5, 3, 1], 每轮最大值: 8 + 5 + 3 + 1 = 17
  EXPECT_EQ(17, solution.deleteGreatestValue(grid));
}

TEST_P(DeleteGreatestValueInEachRowTest, SingleColumn) {
  vector<vector<int>> grid = {{1}, {3}, {2}, {5}};
  // 只有一列，每轮取最大值: max(1,3,2,5) = 5
  EXPECT_EQ(5, solution.deleteGreatestValue(grid));
}

TEST_P(DeleteGreatestValueInEachRowTest, AllSameValues) {
  vector<vector<int>> grid = {{5, 5}, {5, 5}, {5, 5}};
  // 每轮最大值都是 5, 共 2 轮: 5 + 5 = 10
  EXPECT_EQ(10, solution.deleteGreatestValue(grid));
}

TEST_P(DeleteGreatestValueInEachRowTest, IncreasingDecreasing) {
  vector<vector<int>> grid = {{1, 2, 3}, {3, 2, 1}};
  // 排序后: [3,2,1] 和 [3,2,1]
  // 第1轮: max(3,3) = 3
  // 第2轮: max(2,2) = 2
  // 第3轮: max(1,1) = 1
  // 总和: 3 + 2 + 1 = 6
  EXPECT_EQ(6, solution.deleteGreatestValue(grid));
}

TEST_P(DeleteGreatestValueInEachRowTest, LargerGrid) {
  vector<vector<int>> grid = {{10, 20, 30}, {15, 25, 35}, {5, 50, 40}};
  // 排序后: [30,20,10], [35,25,15], [50,40,5]
  // 第1轮: max(30,35,50) = 50
  // 第2轮: max(20,25,40) = 40
  // 第3轮: max(10,15,5) = 15
  // 总和: 50 + 40 + 15 = 105
  EXPECT_EQ(105, solution.deleteGreatestValue(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DeleteGreatestValueInEachRowTest,
    ::testing::ValuesIn(DeleteGreatestValueInEachRowSolution().getStrategyNames()));

}  // namespace problem_2500
}  // namespace leetcode
