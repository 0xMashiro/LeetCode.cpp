#include "leetcode/problems/number-of-substrings-containing-all-three-characters.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1358 {

class NumberOfSubstringsContainingAllThreeCharactersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfSubstringsContainingAllThreeCharactersSolution solution;
};

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, Example1) {
  string s = "abcabc";
  int expected = 10;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, Example2) {
  string s = "aaacb";
  int expected = 3;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, Example3) {
  string s = "abc";
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, AllSameChar) {
  // 边界：只有一种字符，无法满足条件
  string s = "aaaaa";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, TwoCharsOnly) {
  // 边界：只有两种字符
  string s = "ababab";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, MinimumLength) {
  // 边界：最小长度 3，且满足条件
  string s = "abc";
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, RepeatedPattern) {
  // 边界：重复模式 "abcabcabc"
  // i=2: min=0, +1; i=3: min=1, +2; i=4: min=2, +3; i=5: min=3, +4
  // i=6: min=4, +5; i=7: min=5, +6; i=8: min=6, +7
  // total = 1+2+3+4+5+6+7 = 28
  string s = "abcabcabc";
  int expected = 28;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, AllCharsAtEnd) {
  // 边界：所有需要的字符都在末尾 "aaaaabbbbbccccc"
  // a在位置0-4, b在5-9, c在10-14
  // 当处理c时，last_a=4, last_b=9不再更新，每个c贡献min(4,9,i)+1=5
  // 共5个c，总计 5*5 = 25
  string s = "aaaaabbbbbccccc";
  int expected = 25;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, CbaPattern) {
  // 边界：逆序
  string s = "cba";
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

TEST_P(NumberOfSubstringsContainingAllThreeCharactersTest, LongString) {
  // 边界：较长字符串 "a"*10000 + "b"*10000 + "c"*10000
  // 最后10000个位置，每个位置的min_pos都是9999（最后一个a的位置）
  // 每个位置贡献 10000，总计 10000 * 10000 = 100000000
  string s = string(10000, 'a') + string(10000, 'b') + string(10000, 'c');
  long long expected = 100000000LL;
  EXPECT_EQ(expected, solution.numberOfSubstrings(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfSubstringsContainingAllThreeCharactersTest,
    ::testing::ValuesIn(NumberOfSubstringsContainingAllThreeCharactersSolution().getStrategyNames()));

}  // namespace problem_1358
}  // namespace leetcode
