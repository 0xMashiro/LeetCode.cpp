#include "leetcode/problems/total-appeal-of-a-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2262 {

class TotalAppealOfAStringTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TotalAppealOfAStringSolution solution;
};

// 示例 1：s = "abbca"
// 长度1：5个子串，每个吸引力1，总和=5
// 长度2：4个子串，吸引力2,1,2,2，总和=7
// 长度3：3个子串，吸引力2,2,3，总和=7
// 长度4：2个子串，吸引力3,3，总和=6
// 长度5：1个子串，吸引力3，总和=3
// 总计：5+7+7+6+3 = 28
TEST_P(TotalAppealOfAStringTest, Example1) {
  string s = "abbca";
  EXPECT_EQ(28, solution.appealSum(s));
}

// 示例 2：s = "code"
// 长度1：4个子串，每个吸引力1，总和=4
// 长度2：3个子串，每个吸引力2，总和=6
// 长度3：2个子串，每个吸引力3，总和=6
// 长度4：1个子串，吸引力4，总和=4
// 总计：4+6+6+4 = 20
TEST_P(TotalAppealOfAStringTest, Example2) {
  string s = "code";
  EXPECT_EQ(20, solution.appealSum(s));
}

// 边界情况：单个字符
TEST_P(TotalAppealOfAStringTest, SingleCharacter) {
  string s = "a";
  EXPECT_EQ(1, solution.appealSum(s));
}

// 边界情况：两个相同字符
TEST_P(TotalAppealOfAStringTest, TwoSameCharacters) {
  string s = "aa";
  // 子串："a", "a", "aa"
  // "a"(第一个): 吸引力=1
  // "a"(第二个): 吸引力=1
  // "aa": 吸引力=1（只有'a'一种不同字符）
  // 总计：1+1+1 = 3
  EXPECT_EQ(3, solution.appealSum(s));
}

// 边界情况：两个不同字符
TEST_P(TotalAppealOfAStringTest, TwoDifferentCharacters) {
  string s = "ab";
  // 子串："a", "b", "ab"
  // "a": 吸引力=1
  // "b": 吸引力=1
  // "ab": 吸引力=2
  // 总计：1+1+2 = 4
  EXPECT_EQ(4, solution.appealSum(s));
}

// 边界情况：所有字符相同
TEST_P(TotalAppealOfAStringTest, AllSameCharacters) {
  string s = "aaaa";
  // 所有子串的吸引力都是1
  // 子串总数 = 4+3+2+1 = 10
  EXPECT_EQ(10, solution.appealSum(s));
}

// 边界情况：所有字符都不同
TEST_P(TotalAppealOfAStringTest, AllDifferentCharacters) {
  string s = "abcd";
  // 长度1：4个子串，每个吸引力1，总和=4
  // 长度2：3个子串，每个吸引力2，总和=6
  // 长度3：2个子串，每个吸引力3，总和=6
  // 长度4：1个子串，吸引力4，总和=4
  // 总计：4+6+6+4 = 20
  EXPECT_EQ(20, solution.appealSum(s));
}

// 复杂情况：重复字符交错
TEST_P(TotalAppealOfAStringTest, InterleavedCharacters) {
  string s = "abab";
  // 手动计算：
  // 长度1：4个子串，每个吸引力1，总和=4
  // 长度2："ab","ba","ab"，每个吸引力2，总和=6
  // 长度3："aba","bab"，每个吸引力2，总和=4
  // 长度4："abab"，吸引力2，总和=2
  // 总计：4+6+4+2 = 16
  EXPECT_EQ(16, solution.appealSum(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TotalAppealOfAStringTest,
    ::testing::ValuesIn(TotalAppealOfAStringSolution().getStrategyNames()));

}  // namespace problem_2262
}  // namespace leetcode
