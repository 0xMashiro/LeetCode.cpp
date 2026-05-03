#include "leetcode/problems/rotate-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_796 {

class RotateStringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RotateStringSolution solution;
};

TEST_P(RotateStringTest, Example1) {
  EXPECT_TRUE(solution.rotateString("abcde", "cdeab"));
}

TEST_P(RotateStringTest, Example2) {
  EXPECT_FALSE(solution.rotateString("abcde", "abced"));
}

TEST_P(RotateStringTest, SelfAuthoredSameString) {
  EXPECT_TRUE(solution.rotateString("abc", "abc"));
}

TEST_P(RotateStringTest, SelfAuthoredDifferentLengths) {
  EXPECT_FALSE(solution.rotateString("abc", "abcd"));
}

TEST_P(RotateStringTest, SelfAuthoredSingleCharSame) {
  EXPECT_TRUE(solution.rotateString("a", "a"));
}

TEST_P(RotateStringTest, SelfAuthoredSingleCharDifferent) {
  EXPECT_FALSE(solution.rotateString("a", "b"));
}

TEST_P(RotateStringTest, SelfAuthoredFullRotation) {
  EXPECT_TRUE(solution.rotateString("abcde", "abcde"));
}

TEST_P(RotateStringTest, SelfAuthoredNoMatch) {
  EXPECT_FALSE(solution.rotateString("abcde", "edcba"));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RotateStringTest,
    ::testing::ValuesIn(RotateStringSolution().getStrategyNames()));

}  // namespace problem_796
}  // namespace leetcode
