
#include "leetcode/problems/convert-1d-array-into-2d-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2022 {

class Convert1dArrayInto2dArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  Convert1dArrayInto2dArraySolution solution;
};

TEST_P(Convert1dArrayInto2dArrayTest, Example1) {
  vector<int> original = {1, 2, 3, 4};
  int m = 2, n = 2;
  vector<vector<int>> expected = {{1, 2}, {3, 4}};
  EXPECT_EQ(expected, solution.construct2DArray(original, m, n));
}

TEST_P(Convert1dArrayInto2dArrayTest, Example2) {
  vector<int> original = {1, 2, 3};
  int m = 1, n = 3;
  vector<vector<int>> expected = {{1, 2, 3}};
  EXPECT_EQ(expected, solution.construct2DArray(original, m, n));
}

TEST_P(Convert1dArrayInto2dArrayTest, Example3) {
  vector<int> original = {1, 2};
  int m = 1, n = 1;
  vector<vector<int>> expected = {};
  EXPECT_EQ(expected, solution.construct2DArray(original, m, n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, Convert1dArrayInto2dArrayTest,
    ::testing::ValuesIn(Convert1dArrayInto2dArraySolution().getStrategyNames()));

}  // namespace problem_2022
}  // namespace leetcode
