#include "leetcode/problems/smallest-subsequence-of-distinct-characters.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1081 {

class SmallestSubsequenceOfDistinctCharactersTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SmallestSubsequenceOfDistinctCharactersSolution solution;
};

TEST_P(SmallestSubsequenceOfDistinctCharactersTest, Example1) {
  string s = "bcabc";
  string expected = "abc";
  EXPECT_EQ(expected, solution.smallestSubsequence(s));
}

TEST_P(SmallestSubsequenceOfDistinctCharactersTest, Example2) {
  string s = "cbacdcbc";
  string expected = "acdb";
  EXPECT_EQ(expected, solution.smallestSubsequence(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SmallestSubsequenceOfDistinctCharactersTest,
    ::testing::ValuesIn(SmallestSubsequenceOfDistinctCharactersSolution().getStrategyNames()));

}  // namespace problem_1081
}  // namespace leetcode
