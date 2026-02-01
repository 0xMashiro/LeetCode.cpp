#include "leetcode/problems/brace-expansion-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1096 {

class BraceExpansionIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BraceExpansionIiSolution solution;
};

// 示例 1: "{a,b}{c,{d,e}}" -> ["ac","ad","ae","bc","bd","be"]
TEST_P(BraceExpansionIiTest, Example1) {
  string expression = "{a,b}{c,{d,e}}";
  vector<string> expected = {"ac", "ad", "ae", "bc", "bd", "be"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 示例 2: "{{a,z},a{b,c},{ab,z}}" -> ["a","ab","ac","z"]
TEST_P(BraceExpansionIiTest, Example2) {
  string expression = "{{a,z},a{b,c},{ab,z}}";
  vector<string> expected = {"a", "ab", "ac", "z"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：单个字母
TEST_P(BraceExpansionIiTest, SingleLetter) {
  string expression = "a";
  vector<string> expected = {"a"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：简单花括号
TEST_P(BraceExpansionIiTest, SimpleBrace) {
  string expression = "{a,b,c}";
  vector<string> expected = {"a", "b", "c"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：简单连接
TEST_P(BraceExpansionIiTest, SimpleConcat) {
  string expression = "ab";
  vector<string> expected = {"ab"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：笛卡尔积
TEST_P(BraceExpansionIiTest, CartesianProduct) {
  string expression = "{a,b}{c,d}";
  vector<string> expected = {"ac", "ad", "bc", "bd"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：嵌套花括号
TEST_P(BraceExpansionIiTest, NestedBrace) {
  string expression = "{{a,b}}";
  vector<string> expected = {"a", "b"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：复杂表达式
TEST_P(BraceExpansionIiTest, ComplexExpression) {
  string expression = "a{b,c}{d,e}f{g,h}";
  vector<string> expected = {"abdfg", "abdfh", "abefg", "abefh", 
                             "acdfg", "acdfh", "acefg", "acefh"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：多层嵌套
TEST_P(BraceExpansionIiTest, DeepNested) {
  string expression = "{{{a}}}";
  vector<string> expected = {"a"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

// 边界：去重测试
TEST_P(BraceExpansionIiTest, DuplicateRemoval) {
  string expression = "{a,a,a}";
  vector<string> expected = {"a"};
  vector<string> result = solution.braceExpansionII(expression);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BraceExpansionIiTest,
    ::testing::ValuesIn(BraceExpansionIiSolution().getStrategyNames()));

}  // namespace problem_1096
}  // namespace leetcode
