#include "leetcode/problems/smallest-substring-with-identical-characters-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3398 {

class SmallestSubstringWithIdenticalCharactersITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SmallestSubstringWithIdenticalCharactersISolution solution;
};

TEST_P(SmallestSubstringWithIdenticalCharactersITest, Example1) {
  string s = "000001";
  int numOps = 1;
  int expected = 2;
  EXPECT_EQ(expected, solution.minLength(s, numOps));
}

TEST_P(SmallestSubstringWithIdenticalCharactersITest, Example2) {
  string s = "0000";
  int numOps = 2;
  int expected = 1;
  EXPECT_EQ(expected, solution.minLength(s, numOps));
}

TEST_P(SmallestSubstringWithIdenticalCharactersITest, Example3) {
  string s = "0101";
  int numOps = 0;
  int expected = 1;
  EXPECT_EQ(expected, solution.minLength(s, numOps));
}

TEST_P(SmallestSubstringWithIdenticalCharactersITest, WrongAnswerCase1) {
  // 输入: s = "000", numOps = 0
  // 期望: 3 (无法进行任何翻转，最长连续段长度为3)
  string s = "000";
  int numOps = 0;
  int expected = 3;
  EXPECT_EQ(expected, solution.minLength(s, numOps));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SmallestSubstringWithIdenticalCharactersITest,
    ::testing::ValuesIn(SmallestSubstringWithIdenticalCharactersISolution().getStrategyNames()));

}  // namespace problem_3398
}  // namespace leetcode