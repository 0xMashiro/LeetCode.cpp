
#include "leetcode/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3298 {

class CountSubstringsThatCanBeRearrangedToContainAStringIiTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountSubstringsThatCanBeRearrangedToContainAStringIiSolution solution;
};

// Example 1: word1 = "bcca", word2 = "abc", expected = 1
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, Example1) {
  std::string word1 = "bcca";
  std::string word2 = "abc";
  long long expected = 1;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Example 2: word1 = "abcabc", word2 = "abc", expected = 10
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, Example2) {
  std::string word1 = "abcabc";
  std::string word2 = "abc";
  long long expected = 10;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Example 3: word1 = "abcabc", word2 = "aaabc", expected = 0
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, Example3) {
  std::string word1 = "abcabc";
  std::string word2 = "aaabc";
  long long expected = 0;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Additional test: empty-like cases
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, Word2LongerThanWord1) {
  std::string word1 = "abc";
  std::string word2 = "abcd";
  long long expected = 0;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Single character match
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, SingleCharMatch) {
  std::string word1 = "aaa";
  std::string word2 = "a";
  // All substrings containing at least one 'a' are valid
  // Substrings: "a"(3), "aa"(2), "aaa"(1) = 6
  long long expected = 6;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Exact match
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, ExactMatch) {
  std::string word1 = "abc";
  std::string word2 = "abc";
  // Only the full string "abc" is valid
  long long expected = 1;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// No matching characters
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, NoMatch) {
  std::string word1 = "xyz";
  std::string word2 = "abc";
  long long expected = 0;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Multiple valid substrings - word1 = "aabb", word2 = "ab"
// Valid substrings that contain at least one 'a' and one 'b':
// "aab"(pos 0-2), "aabb"(0-3), "ab"(1-2), "abb"(1-3) = 4
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, MultipleValid) {
  std::string word1 = "aabb";
  std::string word2 = "ab";
  long long expected = 4;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// All same character - need more than available
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, InsufficientCount) {
  std::string word1 = "aaaa";
  std::string word2 = "aa";
  // All substrings with length >= 2 are valid
  // Length 2: 3 substrings
  // Length 3: 2 substrings
  // Length 4: 1 substring
  // Total: 6
  long long expected = 6;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

// Large valid substring
TEST_P(CountSubstringsThatCanBeRearrangedToContainAStringIiTest, LargeSubstring) {
  std::string word1 = "abcde";
  std::string word2 = "abc";
  // Substrings containing at least one a, one b, and one c:
  // Starting at 0: "abc", "abcd", "abcde" = 3
  // Starting at 1: "bc" has no a, "bcd" has no a, "bcde" has no a = 0
  // Starting at 2: all missing a or b = 0
  long long expected = 3;
  EXPECT_EQ(expected, solution.validSubstringCount(word1, word2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountSubstringsThatCanBeRearrangedToContainAStringIiTest,
    ::testing::ValuesIn(CountSubstringsThatCanBeRearrangedToContainAStringIiSolution().getStrategyNames()));

}  // namespace problem_3298
}  // namespace leetcode
