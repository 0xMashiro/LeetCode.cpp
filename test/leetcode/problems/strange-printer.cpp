
#include "leetcode/problems/strange-printer.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_664 {

class StrangePrinterTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  StrangePrinterSolution solution;
};

TEST_P(StrangePrinterTest, Example1) {
  string s = "aaabbb";
  int expected = 2;
  EXPECT_EQ(expected, solution.strangePrinter(s));
}

TEST_P(StrangePrinterTest, Example2) {
  string s = "aba";
  int expected = 2;
  EXPECT_EQ(expected, solution.strangePrinter(s));
}

TEST_P(StrangePrinterTest, SingleChar) {
  string s = "a";
  int expected = 1;
  EXPECT_EQ(expected, solution.strangePrinter(s));
}

TEST_P(StrangePrinterTest, AllSame) {
  string s = "aaaaa";
  int expected = 1;
  EXPECT_EQ(expected, solution.strangePrinter(s));
}

TEST_P(StrangePrinterTest, AllDifferent) {
  string s = "abcde";
  int expected = 5;
  EXPECT_EQ(expected, solution.strangePrinter(s));
}

TEST_P(StrangePrinterTest, ComplexCase) {
  string s = "abaaba";
  int expected = 3;
  EXPECT_EQ(expected, solution.strangePrinter(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, StrangePrinterTest,
    ::testing::ValuesIn(StrangePrinterSolution().getStrategyNames()));

}  // namespace problem_664
}  // namespace leetcode
