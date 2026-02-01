
#include "leetcode/problems/vowel-consonant-score.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3813 {

class VowelConsonantScoreTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  VowelConsonantScoreSolution solution;
};

// Example 1: s = "cooear", v=4, c=2, score=floor(4/2)=2
TEST_P(VowelConsonantScoreTest, Example1) {
  std::string s = "cooear";
  EXPECT_EQ(2, solution.vowelConsonantScore(s));
}

// Example 2: s = "axeyizou", v=5, c=3, score=floor(5/3)=1
TEST_P(VowelConsonantScoreTest, Example2) {
  std::string s = "axeyizou";
  EXPECT_EQ(1, solution.vowelConsonantScore(s));
}

// Example 3: s = "au 123", v=2, c=0, score=0
TEST_P(VowelConsonantScoreTest, Example3) {
  std::string s = "au 123";
  EXPECT_EQ(0, solution.vowelConsonantScore(s));
}

// 边界情况：只有元音，无辅音
TEST_P(VowelConsonantScoreTest, OnlyVowels) {
  std::string s = "aeiou";
  EXPECT_EQ(0, solution.vowelConsonantScore(s));
}

// 边界情况：只有辅音
TEST_P(VowelConsonantScoreTest, OnlyConsonants) {
  std::string s = "bcdfg";
  EXPECT_EQ(0, solution.vowelConsonantScore(s));
}

// 边界情况：只有空格和数字
TEST_P(VowelConsonantScoreTest, OnlySpacesAndDigits) {
  std::string s = "  123  456 ";
  EXPECT_EQ(0, solution.vowelConsonantScore(s));
}

// 边界情况：单字符元音
TEST_P(VowelConsonantScoreTest, SingleVowel) {
  std::string s = "a";
  EXPECT_EQ(0, solution.vowelConsonantScore(s));
}

// 边界情况：单字符辅音
TEST_P(VowelConsonantScoreTest, SingleConsonant) {
  std::string s = "b";
  EXPECT_EQ(0, solution.vowelConsonantScore(s));
}

// 边界情况：元音数量是辅音数量的整数倍
TEST_P(VowelConsonantScoreTest, ExactDivision) {
  std::string s = "aaab";
  EXPECT_EQ(3, solution.vowelConsonantScore(s));
}

// 边界情况：元音数量不是辅音数量的整数倍（测试向下取整）
TEST_P(VowelConsonantScoreTest, FloorDivision) {
  std::string s = "aaaab";
  EXPECT_EQ(4, solution.vowelConsonantScore(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, VowelConsonantScoreTest,
    ::testing::ValuesIn(VowelConsonantScoreSolution().getStrategyNames()));

}  // namespace problem_3813
}  // namespace leetcode
