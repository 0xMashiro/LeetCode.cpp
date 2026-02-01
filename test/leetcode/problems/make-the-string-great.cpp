#include "leetcode/problems/make-the-string-great.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1544 {

class MakeTheStringGreatTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MakeTheStringGreatSolution solution;
};

// 示例 1: "leEeetcode" -> "leetcode"
TEST_P(MakeTheStringGreatTest, Example1) {
  std::string s = "leEeetcode";
  std::string expected = "leetcode";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 示例 2: "abBAcC" -> ""
TEST_P(MakeTheStringGreatTest, Example2) {
  std::string s = "abBAcC";
  std::string expected = "";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 示例 3: "s" -> "s"
TEST_P(MakeTheStringGreatTest, Example3) {
  std::string s = "s";
  std::string expected = "s";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 测试空字符串
TEST_P(MakeTheStringGreatTest, EmptyString) {
  std::string s = "";
  std::string expected = "";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 测试已经好的字符串
TEST_P(MakeTheStringGreatTest, AlreadyGood) {
  std::string s = "leetcode";
  std::string expected = "leetcode";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 测试连续多个坏对
TEST_P(MakeTheStringGreatTest, MultipleBadPairs) {
  std::string s = "aAbBcC";
  std::string expected = "";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 测试嵌套坏对
TEST_P(MakeTheStringGreatTest, NestedBadPairs) {
  std::string s = "abBA";
  std::string expected = "";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 测试大写字母在前的情况
TEST_P(MakeTheStringGreatTest, UpperCaseFirst) {
  std::string s = "Aa";
  std::string expected = "";
  EXPECT_EQ(expected, solution.makeGood(s));
}

// 测试多个不相邻的坏对
TEST_P(MakeTheStringGreatTest, NonAdjacentBadPairs) {
  std::string s = "aAbb";
  std::string expected = "bb";
  EXPECT_EQ(expected, solution.makeGood(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MakeTheStringGreatTest,
    ::testing::ValuesIn(MakeTheStringGreatSolution().getStrategyNames()));

}  // namespace problem_1544
}  // namespace leetcode
