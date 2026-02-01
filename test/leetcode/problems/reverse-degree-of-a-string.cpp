#include "leetcode/problems/reverse-degree-of-a-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3498 {

class ReverseDegreeOfAStringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ReverseDegreeOfAStringSolution solution;
};

TEST_P(ReverseDegreeOfAStringTest, Example1) {
  string s = "abc";
  int expected = 148;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

TEST_P(ReverseDegreeOfAStringTest, Example2) {
  string s = "zaza";
  int expected = 160;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

TEST_P(ReverseDegreeOfAStringTest, SingleCharacter) {
  // 单个字符 'a'，反向位置26，字符串位置1，结果26
  string s = "a";
  int expected = 26;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

TEST_P(ReverseDegreeOfAStringTest, SingleCharacterZ) {
  // 单个字符 'z'，反向位置1，字符串位置1，结果1
  string s = "z";
  int expected = 1;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

TEST_P(ReverseDegreeOfAStringTest, AllSameA) {
  // "aaa"，每个a的反向位置都是26
  // 26*1 + 26*2 + 26*3 = 26 + 52 + 78 = 156
  string s = "aaa";
  int expected = 156;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

TEST_P(ReverseDegreeOfAStringTest, AllSameZ) {
  // "zzz"，每个z的反向位置都是1
  // 1*1 + 1*2 + 1*3 = 1 + 2 + 3 = 6
  string s = "zzz";
  int expected = 6;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

TEST_P(ReverseDegreeOfAStringTest, ReverseAlphabet) {
  // "zyx"，反向位置分别为1, 2, 3
  // 1*1 + 2*2 + 3*3 = 1 + 4 + 9 = 14
  string s = "zyx";
  int expected = 14;
  EXPECT_EQ(expected, solution.reverseDegree(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ReverseDegreeOfAStringTest,
    ::testing::ValuesIn(ReverseDegreeOfAStringSolution().getStrategyNames()));

}  // namespace problem_3498
}  // namespace leetcode
