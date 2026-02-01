#include "leetcode/problems/minimum-number-of-valid-strings-to-form-target-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3291 {

class MinimumNumberOfValidStringsToFormTargetITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfValidStringsToFormTargetISolution solution;
};

TEST_P(MinimumNumberOfValidStringsToFormTargetITest, Example1) {
  vector<string> words = {"abc", "aaaaa", "bcdef"};
  string target = "aabcdabc";
  int expected = 3;
  EXPECT_EQ(expected, solution.minValidStrings(words, target));
}

TEST_P(MinimumNumberOfValidStringsToFormTargetITest, Example2) {
  vector<string> words = {"abababab", "ab"};
  string target = "ababaababa";
  int expected = 2;
  EXPECT_EQ(expected, solution.minValidStrings(words, target));
}

TEST_P(MinimumNumberOfValidStringsToFormTargetITest, Example3) {
  vector<string> words = {"abcdef"};
  string target = "xyz";
  int expected = -1;
  EXPECT_EQ(expected, solution.minValidStrings(words, target));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfValidStringsToFormTargetITest,
    ::testing::ValuesIn(MinimumNumberOfValidStringsToFormTargetISolution().getStrategyNames()));

}  // namespace problem_3291
}  // namespace leetcode
