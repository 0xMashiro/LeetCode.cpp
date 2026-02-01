#include "leetcode/problems/maximum-palindromes-after-operations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3035 {

class MaximumPalindromesAfterOperationsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumPalindromesAfterOperationsSolution solution;
};

TEST_P(MaximumPalindromesAfterOperationsTest, Example1) {
  vector<string> words = {"abbb", "ba", "aa"};
  EXPECT_EQ(3, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, Example2) {
  vector<string> words = {"abc", "ab"};
  EXPECT_EQ(2, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, Example3) {
  vector<string> words = {"cd", "ef", "a"};
  EXPECT_EQ(1, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, SingleWord) {
  // 边界：单个字符串
  vector<string> words = {"abcba"};
  EXPECT_EQ(1, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, AllEvenLength) {
  // 全是偶数长度但没有重复字符，无法构成回文
  vector<string> words = {"ab", "cd", "ef"};
  EXPECT_EQ(0, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, AllSameChar) {
  // 全是相同字符
  vector<string> words = {"aaa", "aa", "a"};
  EXPECT_EQ(3, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, ManySmallWords) {
  // 很多短字符串
  vector<string> words = {"a", "b", "c", "d", "e"};
  EXPECT_EQ(5, solution.maxPalindromesAfterOperations(words));  // 单字符本身就是回文
}

TEST_P(MaximumPalindromesAfterOperationsTest, LongWords) {
  // 较长的字符串，无重复字符
  vector<string> words = {"abcdefghij", "klmnopqrst"};
  EXPECT_EQ(0, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, MixedScenario) {
  // 混合场景
  vector<string> words = {"aab", "bcc", "caa"};
  // 总字符：a:4, b:2, c:4，共5对
  // 需要：1, 1, 1 对
  EXPECT_EQ(3, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, AllWordsPalindromes) {
  // 可以全部变成回文
  vector<string> words = {"aabb", "cc", "d"};
  // 总字符：a:2, b:2, c:2, d:1，共3对
  // 需要：2, 1, 0 对，排序后：0, 1, 2，总计3对正好够用
  EXPECT_EQ(3, solution.maxPalindromesAfterOperations(words));
}

TEST_P(MaximumPalindromesAfterOperationsTest, AllFivePalindromes) {
  // 全部可以变成回文（包括单字符）
  vector<string> words = {"aaa", "bbb", "cc", "d", "e"};
  // 总对数：1+1+1+0+0 = 3对
  // 需要：1, 1, 1, 0, 0 对，总计3对，正好够用
  // 单字符需求：2个（aaa和bbb），可用单字符4个，足够
  EXPECT_EQ(5, solution.maxPalindromesAfterOperations(words));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumPalindromesAfterOperationsTest,
    ::testing::ValuesIn(MaximumPalindromesAfterOperationsSolution().getStrategyNames()));

}  // namespace problem_3035
}  // namespace leetcode
