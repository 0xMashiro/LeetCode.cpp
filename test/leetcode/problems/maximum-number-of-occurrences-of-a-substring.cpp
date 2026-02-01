#include "leetcode/problems/maximum-number-of-occurrences-of-a-substring.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1297 {

class MaximumNumberOfOccurrencesOfASubstringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  
  MaximumNumberOfOccurrencesOfASubstringSolution solution;
};

TEST_P(MaximumNumberOfOccurrencesOfASubstringTest, Example1) {
  string s = "aababcaab";
  int maxLetters = 2;
  int minSize = 3;
  int maxSize = 4;
  int expected = 2;
  EXPECT_EQ(expected, solution.maxFreq(s, maxLetters, minSize, maxSize));
}

TEST_P(MaximumNumberOfOccurrencesOfASubstringTest, Example2) {
  string s = "aaaa";
  int maxLetters = 1;
  int minSize = 3;
  int maxSize = 3;
  int expected = 2;
  EXPECT_EQ(expected, solution.maxFreq(s, maxLetters, minSize, maxSize));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    MaximumNumberOfOccurrencesOfASubstringTest,
    ::testing::ValuesIn(MaximumNumberOfOccurrencesOfASubstringSolution().getStrategyNames()));

}  // namespace problem_1297
}  // namespace leetcode
