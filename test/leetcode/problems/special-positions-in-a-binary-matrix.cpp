
#include "leetcode/problems/special-positions-in-a-binary-matrix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1582 {

class SpecialPositionsInABinaryMatrixTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SpecialPositionsInABinaryMatrixSolution solution;
};

TEST_P(SpecialPositionsInABinaryMatrixTest, Example1) {
  vector<vector<int>> mat = {{1,0,0},{0,0,1},{1,0,0}};
  int expected = 1;
  EXPECT_EQ(expected, solution.numSpecial(mat));
}

TEST_P(SpecialPositionsInABinaryMatrixTest, Example2) {
  vector<vector<int>> mat = {{1,0,0},{0,1,0},{0,0,1}};
  int expected = 3;
  EXPECT_EQ(expected, solution.numSpecial(mat));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SpecialPositionsInABinaryMatrixTest,
    ::testing::ValuesIn(SpecialPositionsInABinaryMatrixSolution().getStrategyNames()));

}  // namespace problem_1582
}  // namespace leetcode
