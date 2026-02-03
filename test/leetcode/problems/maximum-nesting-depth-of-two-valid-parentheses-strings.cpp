#include "leetcode/problems/maximum-nesting-depth-of-two-valid-parentheses-strings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1111 {

class MaximumNestingDepthOfTwoValidParenthesesStringsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  // 验证答案是否有效：A 和 B 都是 VPS，并计算最大深度
  bool validateAnswer(const string& seq, const vector<int>& answer) {
    int n = seq.size();
    if (answer.size() != n) return false;
    
    // 构建 A 和 B 字符串
    string a, b;
    for (int i = 0; i < n; ++i) {
      if (answer[i] == 0) {
        a += seq[i];
      } else {
        b += seq[i];
      }
    }
    
    // 验证 A 是 VPS
    int depth_a = 0;
    for (char c : a) {
      if (c == '(') ++depth_a;
      else --depth_a;
      if (depth_a < 0) return false;
    }
    if (depth_a != 0) return false;
    
    // 验证 B 是 VPS
    int depth_b = 0;
    for (char c : b) {
      if (c == '(') ++depth_b;
      else --depth_b;
      if (depth_b < 0) return false;
    }
    if (depth_b != 0) return false;
    
    return true;
  }
  
  // 计算 VPS 的嵌套深度
  int calculateDepth(const string& s) {
    int current = 0, max_depth = 0;
    for (char c : s) {
      if (c == '(') {
        ++current;
        max_depth = std::max(max_depth, current);
      } else {
        --current;
      }
    }
    return max_depth;
  }

  MaximumNestingDepthOfTwoValidParenthesesStringsSolution solution;
};

TEST_P(MaximumNestingDepthOfTwoValidParenthesesStringsTest, Example1) {
  string seq = "(()())";
  vector<int> result = solution.maxDepthAfterSplit(seq);
  EXPECT_TRUE(validateAnswer(seq, result));
  
  // 构建 A 和 B 并检查最大深度
  string a, b;
  for (int i = 0; i < seq.size(); ++i) {
    if (result[i] == 0) a += seq[i];
    else b += seq[i];
  }
  EXPECT_LE(std::max(calculateDepth(a), calculateDepth(b)), 2);
}

TEST_P(MaximumNestingDepthOfTwoValidParenthesesStringsTest, Example2) {
  string seq = "()(())()";
  vector<int> result = solution.maxDepthAfterSplit(seq);
  EXPECT_TRUE(validateAnswer(seq, result));
  
  string a, b;
  for (int i = 0; i < seq.size(); ++i) {
    if (result[i] == 0) a += seq[i];
    else b += seq[i];
  }
  EXPECT_LE(std::max(calculateDepth(a), calculateDepth(b)), 2);
}

TEST_P(MaximumNestingDepthOfTwoValidParenthesesStringsTest, SimpleCase1) {
  // "()" 深度为 1，分割后应该一个给 A 一个给 B
  string seq = "()";
  vector<int> result = solution.maxDepthAfterSplit(seq);
  EXPECT_TRUE(validateAnswer(seq, result));
}

TEST_P(MaximumNestingDepthOfTwoValidParenthesesStringsTest, SimpleCase2) {
  // "()()" 深度为 1
  string seq = "()()";
  vector<int> result = solution.maxDepthAfterSplit(seq);
  EXPECT_TRUE(validateAnswer(seq, result));
}

TEST_P(MaximumNestingDepthOfTwoValidParenthesesStringsTest, DeepNesting) {
  // "((()))" 深度为 3
  string seq = "((()))";
  vector<int> result = solution.maxDepthAfterSplit(seq);
  EXPECT_TRUE(validateAnswer(seq, result));
  
  // 验证最大深度优化效果（应该 <= 2）
  string a, b;
  for (int i = 0; i < seq.size(); ++i) {
    if (result[i] == 0) a += seq[i];
    else b += seq[i];
  }
  EXPECT_LE(std::max(calculateDepth(a), calculateDepth(b)), 2);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumNestingDepthOfTwoValidParenthesesStringsTest,
    ::testing::ValuesIn(MaximumNestingDepthOfTwoValidParenthesesStringsSolution().getStrategyNames()));

}  // namespace problem_1111
}  // namespace leetcode