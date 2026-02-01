#include "leetcode/problems/minimum-time-to-type-word-using-special-typewriter.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1974 {

class MinimumTimeToTypeWordUsingSpecialTypewriterTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumTimeToTypeWordUsingSpecialTypewriterSolution solution;
};

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, Example1) {
  string word = "abc";
  int expected = 5;
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, Example2) {
  string word = "bza";
  int expected = 7;
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, Example3) {
  string word = "zjpc";
  int expected = 34;
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, SingleCharacter) {
  // 边界：单个字符，如果是 'a' 则只需 1 秒输入
  string word = "a";
  int expected = 1;
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, SingleCharacterNotA) {
  // 边界：单个字符 'z'，需要移动 1 步（或 25 步，取最小），然后输入
  string word = "z";
  int expected = 2;  // 逆时针 1 步 + 1 秒输入
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, AllSameCharacter) {
  // 边界：连续相同字符
  string word = "aaa";
  int expected = 3;  // 每个 'a' 只需 1 秒输入
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, OppositeSide) {
  // 边界：跨圆对侧的字符，如 'a' 到 'n'
  string word = "n";
  int expected = 14;  // 13 步移动 + 1 秒输入
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

TEST_P(MinimumTimeToTypeWordUsingSpecialTypewriterTest, LongWord) {
  // 边界：较长的单词
  string word = "abcdefghijklmnopqrstuvwxyz";
  // 从 'a' 开始，依次输入 a,b,c,...,z
  // a: 0 移动 + 1 输入 = 1
  // b: 1 移动 + 1 输入 = 2
  // c: 1 移动 + 1 输入 = 2
  // ... 以此类推
  // 总计: 1 + 25*2 = 51
  int expected = 51;
  EXPECT_EQ(expected, solution.minTimeToType(word));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumTimeToTypeWordUsingSpecialTypewriterTest,
    ::testing::ValuesIn(MinimumTimeToTypeWordUsingSpecialTypewriterSolution().getStrategyNames()));

}  // namespace problem_1974
}  // namespace leetcode
