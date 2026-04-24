#include "leetcode/problems/odd-string-difference.h"
#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2451 {

class OddStringDifferenceTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  OddStringDifferenceSolution solution;
};

TEST_P(OddStringDifferenceTest, Example1) {
  vector<string> words = {"adc", "wzy", "abc"};
  string expected = "abc";
  EXPECT_EQ(expected, solution.oddString(words));
}

TEST_P(OddStringDifferenceTest, Example2) {
  vector<string> words = {"aaa", "bob", "ccc", "ddd"};
  string expected = "bob";
  EXPECT_EQ(expected, solution.oddString(words));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, OddStringDifferenceTest,
    ::testing::ValuesIn(OddStringDifferenceSolution().getStrategyNames()));

}  // namespace problem_2451
}  // namespace leetcode
