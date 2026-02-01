#include "leetcode/problems/redistribute-characters-to-make-all-strings-equal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1897 {

class RedistributeCharactersToMakeAllStringsEqualTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RedistributeCharactersToMakeAllStringsEqualSolution solution;
};

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, Example1) {
  vector<string> words = {"abc", "aabc", "bc"};
  EXPECT_TRUE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, Example2) {
  vector<string> words = {"ab", "a"};
  EXPECT_FALSE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, SingleWord) {
  // 只有一个字符串，本身就是相等的
  vector<string> words = {"abc"};
  EXPECT_TRUE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, AllSameStrings) {
  // 所有字符串已经相等
  vector<string> words = {"abc", "abc", "abc"};
  EXPECT_TRUE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, EmptyStrings) {
  // 空字符串的情况
  vector<string> words = {"", "", ""};
  EXPECT_TRUE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, CanRedistributeDifferentLengths) {
  // 字符串长度不同，但可以重新分配
  // {"ab", "ab", "ab"}: 'a'=3, 'b'=3，都能被 3 整除
  vector<string> words = {"ab", "ab", "ab"};
  EXPECT_TRUE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, CannotRedistribute) {
  // 字符数量不能被 n 整除
  vector<string> words = {"abc", "def", "ghi"};
  // 'a','b','c','d','e','f','g','h','i' 各出现1次，不能被3整除
  EXPECT_FALSE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, LargeN) {
  // 多个字符串的情况
  vector<string> words = {"aaaa", "aaaa", "aaaa", "aaaa"};
  EXPECT_TRUE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, TwoWordsOddCount) {
  // 两个字符串，某种字符出现奇数次
  vector<string> words = {"aa", "a"};
  // 'a' 出现3次，不能被2整除
  EXPECT_FALSE(solution.makeEqual(words));
}

TEST_P(RedistributeCharactersToMakeAllStringsEqualTest, DifferentLengthsCannot) {
  // 长度不同且无法重新分配
  vector<string> words = {"a", "b", "ab"};
  // 总字符数 4，不能被 3 整除
  EXPECT_FALSE(solution.makeEqual(words));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RedistributeCharactersToMakeAllStringsEqualTest,
    ::testing::ValuesIn(RedistributeCharactersToMakeAllStringsEqualSolution().getStrategyNames()));

}  // namespace problem_1897
}  // namespace leetcode
