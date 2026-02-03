#include "leetcode/problems/find-maximum-number-of-string-pairs.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2744 {

class FindMaximumNumberOfStringPairsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindMaximumNumberOfStringPairsSolution solution;
};

TEST_P(FindMaximumNumberOfStringPairsTest, Example1) {
  vector<string> words = {"cd", "ac", "dc", "ca", "zz"};
  int expected = 2;
  EXPECT_EQ(expected, solution.maximumNumberOfStringPairs(words));
}

TEST_P(FindMaximumNumberOfStringPairsTest, Example2) {
  vector<string> words = {"ab", "ba", "cc"};
  int expected = 1;
  EXPECT_EQ(expected, solution.maximumNumberOfStringPairs(words));
}

TEST_P(FindMaximumNumberOfStringPairsTest, Example3) {
  vector<string> words = {"aa", "ab"};
  int expected = 0;
  EXPECT_EQ(expected, solution.maximumNumberOfStringPairs(words));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindMaximumNumberOfStringPairsTest,
    ::testing::ValuesIn(FindMaximumNumberOfStringPairsSolution().getStrategyNames()));

}  // namespace problem_2744
}  // namespace leetcode
