#include "leetcode/problems/number-of-rectangles-that-can-form-the-largest-square.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1725 {

class NumberOfRectanglesThatCanFormTheLargestSquareTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfRectanglesThatCanFormTheLargestSquareSolution solution;
};

TEST_P(NumberOfRectanglesThatCanFormTheLargestSquareTest, Example1) {
  vector<vector<int>> rectangles = {{5, 8}, {3, 9}, {5, 12}, {16, 5}};
  int expected = 3;
  EXPECT_EQ(expected, solution.countGoodRectangles(rectangles));
}

TEST_P(NumberOfRectanglesThatCanFormTheLargestSquareTest, Example2) {
  vector<vector<int>> rectangles = {{2, 3}, {3, 7}, {4, 3}, {3, 7}};
  int expected = 3;
  EXPECT_EQ(expected, solution.countGoodRectangles(rectangles));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfRectanglesThatCanFormTheLargestSquareTest,
    ::testing::ValuesIn(NumberOfRectanglesThatCanFormTheLargestSquareSolution().getStrategyNames()));

}  // namespace problem_1725
}  // namespace leetcode
