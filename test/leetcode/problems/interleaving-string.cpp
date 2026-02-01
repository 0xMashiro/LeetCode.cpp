#include "leetcode/problems/interleaving-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_97 {

class InterleavingStringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  InterleavingStringSolution solution;
};

TEST_P(InterleavingStringTest, Example1) {
  string s1 = "aabcc";
  string s2 = "dbbca";
  string s3 = "aadbbcbcac";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, Example2) {
  string s1 = "aabcc";
  string s2 = "dbbca";
  string s3 = "aadbbbaccc";
  EXPECT_FALSE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, Example3_EmptyStrings) {
  string s1 = "";
  string s2 = "";
  string s3 = "";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, EmptyS1) {
  string s1 = "";
  string s2 = "abc";
  string s3 = "abc";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, EmptyS2) {
  string s1 = "abc";
  string s2 = "";
  string s3 = "abc";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, LengthMismatch) {
  string s1 = "a";
  string s2 = "b";
  string s3 = "abc";  // 长度不匹配
  EXPECT_FALSE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, SingleChar) {
  string s1 = "a";
  string s2 = "b";
  string s3 = "ab";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, SameChars) {
  string s1 = "aaa";
  string s2 = "aaa";
  string s3 = "aaaaaa";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, CannotInterleave) {
  string s1 = "a";
  string s2 = "b";
  string s3 = "ba";
  EXPECT_TRUE(solution.isInterleave(s1, s2, s3));
}

TEST_P(InterleavingStringTest, WrongOrder) {
  string s1 = "abc";
  string s2 = "def";
  string s3 = "abedcf";  // 不是交错顺序
  EXPECT_FALSE(solution.isInterleave(s1, s2, s3));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, InterleavingStringTest,
    ::testing::ValuesIn(InterleavingStringSolution().getStrategyNames()));

}  // namespace problem_97
}  // namespace leetcode
