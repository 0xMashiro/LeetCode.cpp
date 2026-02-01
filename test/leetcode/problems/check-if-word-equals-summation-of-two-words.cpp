#include "leetcode/problems/check-if-word-equals-summation-of-two-words.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1880 {

class CheckIfWordEqualsSummationOfTwoWordsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CheckIfWordEqualsSummationOfTwoWordsSolution solution;
};

// Example 1: "acb" + "cba" = "cdb" -> 21 + 210 = 231 ✓
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, Example1) {
  string firstWord = "acb";
  string secondWord = "cba";
  string targetWord = "cdb";
  EXPECT_TRUE(solution.isSumEqual(firstWord, secondWord, targetWord));
}

// Example 2: "aaa" + "a" = "aab" -> 0 + 0 = 1 ✗
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, Example2) {
  string firstWord = "aaa";
  string secondWord = "a";
  string targetWord = "aab";
  EXPECT_FALSE(solution.isSumEqual(firstWord, secondWord, targetWord));
}

// Example 3: "aaa" + "a" = "aaaa" -> 0 + 0 = 0 ✓
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, Example3) {
  string firstWord = "aaa";
  string secondWord = "a";
  string targetWord = "aaaa";
  EXPECT_TRUE(solution.isSumEqual(firstWord, secondWord, targetWord));
}

// 边界测试：单个字符
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, SingleCharacter) {
  // "a" + "b" = "b" -> 0 + 1 = 1 ✓
  EXPECT_TRUE(solution.isSumEqual("a", "b", "b"));
  // "b" + "c" = "e" -> 1 + 2 = 3 (e is 4) ✗
  EXPECT_FALSE(solution.isSumEqual("b", "c", "e"));
  // "b" + "c" = "d" -> 1 + 2 = 3 (d is 3) ✓
  EXPECT_TRUE(solution.isSumEqual("b", "c", "d"));
}

// 边界测试：最大数字
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, MaxValues) {
  // "j" + "j" = "bi" -> 9 + 9 = 18 ✓ (b=1, i=8)
  EXPECT_TRUE(solution.isSumEqual("j", "j", "bi"));
  // "j" + "a" = "j" -> 9 + 0 = 9 ✓
  EXPECT_TRUE(solution.isSumEqual("j", "a", "j"));
}

// 边界测试：前导零
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, LeadingZeros) {
  // "aaa" + "a" = "aaaa" -> 0 + 0 = 0 ✓
  EXPECT_TRUE(solution.isSumEqual("aaa", "a", "aaaa"));
  // "ab" + "ac" = "ad" -> 01 + 02 = 03 -> 1 + 2 = 3 ✓
  EXPECT_TRUE(solution.isSumEqual("ab", "ac", "ad"));
}

// 边界测试：8字符长度（最大值）
TEST_P(CheckIfWordEqualsSummationOfTwoWordsTest, MaxLength) {
  // "aaaaaaaa" + "aaaaaaaa" = "aaaaaaaa" -> 0 + 0 = 0 ✓
  EXPECT_TRUE(solution.isSumEqual("aaaaaaaa", "aaaaaaaa", "aaaaaaaa"));
  // "a" + "jjjjjjjj" = "jjjjjjjj" -> 0 + 99999999 = 99999999 ✓
  EXPECT_TRUE(solution.isSumEqual("a", "jjjjjjjj", "jjjjjjjj"));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CheckIfWordEqualsSummationOfTwoWordsTest,
    ::testing::ValuesIn(CheckIfWordEqualsSummationOfTwoWordsSolution().getStrategyNames()));

}  // namespace problem_1880
}  // namespace leetcode
