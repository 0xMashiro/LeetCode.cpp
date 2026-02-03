#include "leetcode/problems/spiral-matrix-iv.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2326 {

class SpiralMatrixIvTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SpiralMatrixIvSolution solution;
};

TEST_P(SpiralMatrixIvTest, Example1) {
  // Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
  // Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
  int m = 3, n = 5;
  std::vector<int> listVals = {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0};
  ListNode* head = constructLinkedList(listVals);
  
  vector<vector<int>> expected = {
    {3, 0, 2, 6, 8},
    {5, 0, -1, -1, 1},
    {5, 2, 4, 9, 7}
  };
  
  vector<vector<int>> result = solution.spiralMatrix(m, n, head);
  EXPECT_EQ(expected, result);
}

TEST_P(SpiralMatrixIvTest, Example2) {
  // Input: m = 1, n = 4, head = [0,1,2]
  // Output: [[0,1,2,-1]]
  int m = 1, n = 4;
  std::vector<int> listVals = {0, 1, 2};
  ListNode* head = constructLinkedList(listVals);
  
  vector<vector<int>> expected = {
    {0, 1, 2, -1}
  };
  
  vector<vector<int>> result = solution.spiralMatrix(m, n, head);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SpiralMatrixIvTest,
    ::testing::ValuesIn(SpiralMatrixIvSolution().getStrategyNames()));

}  // namespace problem_2326
}  // namespace leetcode
