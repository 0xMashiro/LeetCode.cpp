#include "leetcode/problems/count-stepping-numbers-in-range.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2801 {

class CountSteppingNumbersInRangeTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountSteppingNumbersInRangeSolution solution;
};

TEST_P(CountSteppingNumbersInRangeTest, Example1) {
  string low = "1";
  string high = "11";
  int expected = 10;
  EXPECT_EQ(expected, solution.countSteppingNumbers(low, high));
}

TEST_P(CountSteppingNumbersInRangeTest, Example2) {
  string low = "90";
  string high = "101";
  int expected = 2;
  EXPECT_EQ(expected, solution.countSteppingNumbers(low, high));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountSteppingNumbersInRangeTest,
    ::testing::ValuesIn(CountSteppingNumbersInRangeSolution().getStrategyNames()));

}  // namespace problem_2801
}  // namespace leetcode
