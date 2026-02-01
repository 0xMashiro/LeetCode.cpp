
#include "leetcode/problems/count-substrings-that-satisfy-k-constraint-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3258 {

class CountSubstringsThatSatisfyKConstraintITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountSubstringsThatSatisfyKConstraintISolution solution;
};

TEST_P(CountSubstringsThatSatisfyKConstraintITest, Example1) {
  string s = "10101";
  int k = 1;
  int expected = 12;
  EXPECT_EQ(expected, solution.countKConstraintSubstrings(s, k));
}

TEST_P(CountSubstringsThatSatisfyKConstraintITest, Example2) {
  string s = "1010101";
  int k = 2;
  int expected = 25;
  EXPECT_EQ(expected, solution.countKConstraintSubstrings(s, k));
}

TEST_P(CountSubstringsThatSatisfyKConstraintITest, Example3) {
  string s = "11111";
  int k = 1;
  int expected = 15;
  EXPECT_EQ(expected, solution.countKConstraintSubstrings(s, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountSubstringsThatSatisfyKConstraintITest,
    ::testing::ValuesIn(CountSubstringsThatSatisfyKConstraintISolution().getStrategyNames()));

}  // namespace problem_3258
}  // namespace leetcode
