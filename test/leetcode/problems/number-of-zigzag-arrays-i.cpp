#include "leetcode/problems/number-of-zigzag-arrays-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3699 {

class NumberOfZigzagArraysITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfZigzagArraysISolution solution;
};

TEST_P(NumberOfZigzagArraysITest, Example1) {
  int n = 3, l = 4, r = 5;
  int expected = 2;
  EXPECT_EQ(expected, solution.zigZagArrays(n, l, r));
}

TEST_P(NumberOfZigzagArraysITest, Example2) {
  int n = 3, l = 1, r = 3;
  int expected = 10;
  EXPECT_EQ(expected, solution.zigZagArrays(n, l, r));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfZigzagArraysITest,
    ::testing::ValuesIn(NumberOfZigzagArraysISolution().getStrategyNames()));

}  // namespace problem_3699
}  // namespace leetcode
