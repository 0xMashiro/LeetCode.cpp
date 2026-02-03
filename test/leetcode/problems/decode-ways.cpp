#include "leetcode/problems/decode-ways.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_91 {

class DecodeWaysTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DecodeWaysSolution solution;
};

TEST_P(DecodeWaysTest, Example1) {
  // "12" 可以解码为 "AB" (1 2) 或 "L" (12)
  string s = "12";
  int expected = 2;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, Example2) {
  // "226" 可以解码为 "BZ" (2 26), "VF" (22 6), "BBF" (2 2 6)
  string s = "226";
  int expected = 3;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, Example3) {
  // "06" 无法解码，因为有前导零
  string s = "06";
  int expected = 0;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, ExampleFromDescription) {
  // "11106" 可以解码为 "AAJF" (1 1 10 6) 或 "KJF" (11 10 6)
  string s = "11106";
  int expected = 2;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, SingleDigitValid) {
  // 单个有效数字 "5" -> "E"
  string s = "5";
  int expected = 1;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, SingleDigitZero) {
  // 单个零 "0" 无法解码
  string s = "0";
  int expected = 0;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, StartsWithZero) {
  // 以零开头无法解码
  string s = "01";
  int expected = 0;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, ContainsZeroValid) {
  // "10" 可以解码为 "J"
  string s = "10";
  int expected = 1;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, ContainsZeroInvalid) {
  // "30" 无法解码，因为 30 > 26
  string s = "30";
  int expected = 0;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, ConsecutiveZeros) {
  // "00" 无法解码
  string s = "00";
  int expected = 0;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

TEST_P(DecodeWaysTest, LongString) {
  // "11106" 的更长版本，测试边界条件
  string s = "101";
  // "10 1" -> "JA" 或 "1 01"（无效）
  // 只有 "10 1" 一种
  int expected = 1;
  EXPECT_EQ(expected, solution.numDecodings(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DecodeWaysTest,
    ::testing::ValuesIn(DecodeWaysSolution().getStrategyNames()));

}  // namespace problem_91
}  // namespace leetcode
