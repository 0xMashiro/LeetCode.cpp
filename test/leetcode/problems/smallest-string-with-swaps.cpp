#include "leetcode/problems/smallest-string-with-swaps.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1202 {

class SmallestStringWithSwapsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SmallestStringWithSwapsSolution solution;
};

TEST_P(SmallestStringWithSwapsTest, Example1) {
  std::string s = "dcab";
  std::vector<std::vector<int>> pairs = {{0, 3}, {1, 2}};
  EXPECT_EQ("bacd", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, Example2) {
  std::string s = "dcab";
  std::vector<std::vector<int>> pairs = {{0, 3}, {1, 2}, {0, 2}};
  EXPECT_EQ("abcd", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, Example3) {
  std::string s = "cba";
  std::vector<std::vector<int>> pairs = {{0, 1}, {1, 2}};
  EXPECT_EQ("abc", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, EmptyPairs) {
  // 没有可交换的对，字符串保持不变
  std::string s = "zxy";
  std::vector<std::vector<int>> pairs = {};
  EXPECT_EQ("zxy", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, SingleChar) {
  // 单字符字符串
  std::string s = "a";
  std::vector<std::vector<int>> pairs = {};
  EXPECT_EQ("a", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, AllSameChar) {
  // 所有字符相同
  std::string s = "aaaa";
  std::vector<std::vector<int>> pairs = {{0, 1}, {2, 3}};
  EXPECT_EQ("aaaa", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, AlreadySorted) {
  // 已经是有序的
  std::string s = "abcd";
  std::vector<std::vector<int>> pairs = {{0, 3}, {1, 2}};
  EXPECT_EQ("abcd", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, ReverseSorted) {
  // 完全逆序，可以全交换
  std::string s = "dcba";
  std::vector<std::vector<int>> pairs = {{0, 1}, {1, 2}, {2, 3}};
  EXPECT_EQ("abcd", solution.smallestStringWithSwaps(s, pairs));
}

TEST_P(SmallestStringWithSwapsTest, MultipleComponents) {
  // 多个独立的连通分量
  // s = "qgyrk", pairs = {{0,1}, {2,3}}
  // 分量1: {0,1}, 字符 'q','g' -> 排序后 'g','q' -> 位置0,1
  // 分量2: {2,3}, 字符 'y','r' -> 排序后 'r','y' -> 位置2,3
  // 分量3: {4}, 字符 'k' -> 位置4
  // 结果: "gqryk"
  std::string s = "qgyrk";
  std::vector<std::vector<int>> pairs = {{0, 1}, {2, 3}};
  EXPECT_EQ("gqryk", solution.smallestStringWithSwaps(s, pairs));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SmallestStringWithSwapsTest,
    ::testing::ValuesIn(SmallestStringWithSwapsSolution().getStrategyNames()));

}  // namespace problem_1202
}  // namespace leetcode
