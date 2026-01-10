#include "leetcode/problems/minimum-ascii-delete-sum-for-two-strings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_712 {

class MinimumAsciiDeleteSumForTwoStringsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumAsciiDeleteSumForTwoStringsSolution solution;
  
  // Helper function to compute ASCII sum
  static int asciiSum(const string& s) {
    int sum = 0;
    for (char c : s) {
      sum += static_cast<int>(c);
    }
    return sum;
  }
};

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, Example1) {
  string s1 = "sea";
  string s2 = "eat";
  int expected = 231;
  int result = solution.minimumDeleteSum(s1, s2);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, Example2) {
  string s1 = "delete";
  string s2 = "leet";
  int expected = 403;
  int result = solution.minimumDeleteSum(s1, s2);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, EmptyStrings) {
  {
    string s1 = "";
    string s2 = "";
    int expected = 0;
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
  {
    string s1 = "a";
    string s2 = "";
    // delete 'a' from s1, nothing from s2
    int expected = static_cast<int>('a');  // 97
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
  {
    string s1 = "";
    string s2 = "b";
    int expected = static_cast<int>('b');  // 98
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
}

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, SameString) {
  {
    string s1 = "abc";
    string s2 = "abc";
    int expected = 0;  // no deletions needed
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
  {
    string s1 = "hello";
    string s2 = "hello";
    int expected = 0;
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
}

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, NoCommonCharacters) {
  {
    string s1 = "abc";
    string s2 = "def";
    // delete all characters from both strings
    int expected = asciiSum(s1) + asciiSum(s2);
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
}

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, SingleCommonCharacter) {
  {
    string s1 = "axx";
    string s2 = "byy";
    // only 'x' and 'y' are different, no common characters
    // Actually there's no common character, so delete all
    int expected = asciiSum(s1) + asciiSum(s2);
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
  {
    string s1 = "a";
    string s2 = "a";
    int expected = 0;
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
  {
    string s1 = "ab";
    string s2 = "ac";
    // common 'a', need to delete 'b' and 'c'
    int expected = static_cast<int>('b') + static_cast<int>('c');
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
}

TEST_P(MinimumAsciiDeleteSumForTwoStringsTest, LongStrings) {
  // Test with strings of length up to 100 (small enough)
  {
    string s1(100, 'a');  // 100 'a's
    string s2(100, 'a');
    int expected = 0;
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
  {
    string s1(100, 'a');
    string s2(50, 'a');  // 50 'a's
    // need to delete 50 'a's from s1
    int expected = 50 * static_cast<int>('a');
    int result = solution.minimumDeleteSum(s1, s2);
    EXPECT_EQ(expected, result);
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumAsciiDeleteSumForTwoStringsTest,
    ::testing::ValuesIn(MinimumAsciiDeleteSumForTwoStringsSolution().getStrategyNames()));

}  // namespace problem_712
}  // namespace leetcode