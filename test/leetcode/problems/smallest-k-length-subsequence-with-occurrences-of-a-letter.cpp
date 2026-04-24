#include "leetcode/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2030 {

class SmallestKLengthSubsequenceWithOccurrencesOfALetterTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution solution;
};

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, Example1) {
    string s = "leet";
    int k = 3;
    char letter = 'e';
    int repetition = 1;
    EXPECT_EQ("eet", solution.smallestSubsequence(s, k, letter, repetition));
}

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, Example2) {
    string s = "leetcode";
    int k = 4;
    char letter = 'e';
    int repetition = 2;
    EXPECT_EQ("ecde", solution.smallestSubsequence(s, k, letter, repetition));
}

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, Example3) {
    string s = "bb";
    int k = 2;
    char letter = 'b';
    int repetition = 2;
    EXPECT_EQ("bb", solution.smallestSubsequence(s, k, letter, repetition));
}

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, SelfAuthoredSingleChar) {
    string s = "a";
    int k = 1;
    char letter = 'a';
    int repetition = 1;
    EXPECT_EQ("a", solution.smallestSubsequence(s, k, letter, repetition));
}

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, SelfAuthoredAllLetter) {
    string s = "aaabbb";
    int k = 3;
    char letter = 'a';
    int repetition = 2;
    // 所有长度为3的子序列中，"aaa"（取前三个a）字典序最小，且含至少2个'a'
    EXPECT_EQ("aaa", solution.smallestSubsequence(s, k, letter, repetition));
}

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, SelfAuthoredLetterAtEnd) {
    string s = "abccba";
    int k = 4;
    char letter = 'c';
    int repetition = 2;
    // 字典序最小长度为4且至少2个'c'的子序列：取 s[0]='a', s[1]='b', s[2]='c', s[3]='c' → "abcc"
    EXPECT_EQ("abcc", solution.smallestSubsequence(s, k, letter, repetition));
}

TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, SelfAuthoredKEqualsN) {
    string s = "bacfe";
    int k = 5;
    char letter = 'e';
    int repetition = 1;
    // k == s.length(), 唯一长度为5的子序列就是整个字符串
    EXPECT_EQ("bacfe", solution.smallestSubsequence(s, k, letter, repetition));
}


// LeetCode 失败用例: WrongAnswerCase1
TEST_P(SmallestKLengthSubsequenceWithOccurrencesOfALetterTest, WrongAnswerCase1) {
  // 输入: s = "aaabbbcccddd", k = 3, letter = 'b', repetition = 2
    // 期望: "abb"
    string s = "aaabbbcccddd";
    int k = 3;
    char letter = 'b';
    int repetition = 2;
    EXPECT_EQ("abb", solution.smallestSubsequence(s, k, letter, repetition));
}
INSTANTIATE_TEST_SUITE_P(
    LeetCode, SmallestKLengthSubsequenceWithOccurrencesOfALetterTest,
    ::testing::ValuesIn(SmallestKLengthSubsequenceWithOccurrencesOfALetterSolution().getStrategyNames()));

}  // namespace problem_2030
}  // namespace leetcode
