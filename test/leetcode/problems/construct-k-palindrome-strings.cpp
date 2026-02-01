
#include "leetcode/problems/construct-k-palindrome-strings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1400 {

class ConstructKPalindromeStringsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConstructKPalindromeStringsSolution solution;
};

// 示例 1: s = "annabelle", k = 2 -> true
TEST_P(ConstructKPalindromeStringsTest, Example1) {
  string s = "annabelle";
  int k = 2;
  EXPECT_TRUE(solution.canConstruct(s, k));
}

// 示例 2: s = "leetcode", k = 3 -> false
TEST_P(ConstructKPalindromeStringsTest, Example2) {
  string s = "leetcode";
  int k = 3;
  EXPECT_FALSE(solution.canConstruct(s, k));
}

// 示例 3: s = "true", k = 4 -> true
TEST_P(ConstructKPalindromeStringsTest, Example3) {
  string s = "true";
  int k = 4;
  EXPECT_TRUE(solution.canConstruct(s, k));
}

// 边界测试: k 等于字符串长度，每个字符单独成一个回文串
TEST_P(ConstructKPalindromeStringsTest, KEqualToLength) {
  string s = "abc";
  int k = 3;
  EXPECT_TRUE(solution.canConstruct(s, k));
}

// 边界测试: k 大于字符串长度 -> false
TEST_P(ConstructKPalindromeStringsTest, KGreaterThanLength) {
  string s = "abc";
  int k = 4;
  EXPECT_FALSE(solution.canConstruct(s, k));
}

// 边界测试: k = 1，检查整个字符串能否组成回文
TEST_P(ConstructKPalindromeStringsTest, KEqualOne) {
  // "aabbc" 可以重排为 "abcba"，是回文
  string s = "aabbc";
  int k = 1;
  EXPECT_TRUE(solution.canConstruct(s, k));
  
  // "abc" 不能组成回文
  string s2 = "abc";
  EXPECT_FALSE(solution.canConstruct(s2, k));
}

// 边界测试: 所有字符相同
TEST_P(ConstructKPalindromeStringsTest, AllSameChars) {
  string s = "aaaa";
  int k = 2;
  EXPECT_TRUE(solution.canConstruct(s, k));  // "aa" + "aa"
}

// 边界测试: 空字符串（根据约束 s.length >= 1，但测试边界）
TEST_P(ConstructKPalindromeStringsTest, SingleChar) {
  string s = "a";
  int k = 1;
  EXPECT_TRUE(solution.canConstruct(s, k));
}

// 边界测试: 大量奇数频次字符
TEST_P(ConstructKPalindromeStringsTest, ManyOddCounts) {
  string s = "abcde";  // 5个奇数频次字符
  int k = 3;  // 需要 k >= 5 才能构造
  EXPECT_FALSE(solution.canConstruct(s, k));
  
  int k2 = 5;  // 刚好每个字符单独成回文
  EXPECT_TRUE(solution.canConstruct(s, k2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode,
    ConstructKPalindromeStringsTest,
    ::testing::ValuesIn(ConstructKPalindromeStringsSolution().getStrategyNames()));

}  // namespace problem_1400
}  // namespace leetcode
