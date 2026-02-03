#include "leetcode/problems/minimum-length-of-string-after-operations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3223 {

class MinimumLengthOfStringAfterOperationsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumLengthOfStringAfterOperationsSolution solution;
};

// Example 1: s = "abaacbcbb", output = 5
TEST_P(MinimumLengthOfStringAfterOperationsTest, Example1) {
  string s = "abaacbcbb";
  EXPECT_EQ(5, solution.minimumLength(s));
}

// Example 2: s = "aa", output = 2
TEST_P(MinimumLengthOfStringAfterOperationsTest, Example2) {
  string s = "aa";
  EXPECT_EQ(2, solution.minimumLength(s));
}

// Edge case: single character
TEST_P(MinimumLengthOfStringAfterOperationsTest, SingleCharacter) {
  string s = "a";
  EXPECT_EQ(1, solution.minimumLength(s));
}

// Edge case: empty string (constraint says length >= 1, but test anyway)
TEST_P(MinimumLengthOfStringAfterOperationsTest, AllSameEven) {
  string s = "aaaa";
  // 4 'a's -> can perform operation once (pick middle 'a', delete left and right)
  // After operation: 2 'a's remain
  EXPECT_EQ(2, solution.minimumLength(s));
}

TEST_P(MinimumLengthOfStringAfterOperationsTest, AllSameOdd) {
  string s = "aaa";
  // 3 'a's -> can perform operation once, 1 'a' remains
  EXPECT_EQ(1, solution.minimumLength(s));
}

TEST_P(MinimumLengthOfStringAfterOperationsTest, AllDistinct) {
  string s = "abcdef";
  // No operations possible, all 6 remain
  EXPECT_EQ(6, solution.minimumLength(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    MinimumLengthOfStringAfterOperationsTest,
    ::testing::ValuesIn(MinimumLengthOfStringAfterOperationsSolution().getStrategyNames()));

}  // namespace problem_3223
}  // namespace leetcode
