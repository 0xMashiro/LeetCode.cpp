#include "leetcode/problems/smallest-string-with-a-given-numeric-value.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1663 {

class SmallestStringWithAGivenNumericValueTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SmallestStringWithAGivenNumericValueSolution solution;
};

TEST_P(SmallestStringWithAGivenNumericValueTest, Example1) {
  int n = 3, k = 27;
  string expected = "aay";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

TEST_P(SmallestStringWithAGivenNumericValueTest, Example2) {
  int n = 5, k = 73;
  string expected = "aaszz";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

TEST_P(SmallestStringWithAGivenNumericValueTest, AllA) {
  // 最小情况：全'a'
  int n = 5, k = 5;
  string expected = "aaaaa";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

TEST_P(SmallestStringWithAGivenNumericValueTest, AllZ) {
  // 最大情况：全'z'
  int n = 3, k = 78;  // 26 * 3 = 78
  string expected = "zzz";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

TEST_P(SmallestStringWithAGivenNumericValueTest, SingleA) {
  // 单字符，最小值
  int n = 1, k = 1;
  string expected = "a";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

TEST_P(SmallestStringWithAGivenNumericValueTest, SingleZ) {
  // 单字符，最大值
  int n = 1, k = 26;
  string expected = "z";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

TEST_P(SmallestStringWithAGivenNumericValueTest, SingleM) {
  // 单字符，中间值
  int n = 1, k = 13;  // 'm' = 13
  string expected = "m";
  EXPECT_EQ(expected, solution.getSmallestString(n, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SmallestStringWithAGivenNumericValueTest,
    ::testing::ValuesIn(SmallestStringWithAGivenNumericValueSolution().getStrategyNames()));

}  // namespace problem_1663
}  // namespace leetcode
