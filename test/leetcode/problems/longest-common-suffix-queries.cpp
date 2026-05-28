#include "leetcode/problems/longest-common-suffix-queries.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3093 {

class LongestCommonSuffixQueriesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestCommonSuffixQueriesSolution solution;
};

TEST_P(LongestCommonSuffixQueriesTest, Example1) {
  vector<string> wordsContainer = {"abcd", "bcd", "xbcd"};
  vector<string> wordsQuery = {"cd", "bcd", "xyz"};
  vector<int> expected = {1, 1, 1};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, Example2) {
  vector<string> wordsContainer = {"abcdefgh", "poiuygh", "ghghgh"};
  vector<string> wordsQuery = {"gh", "acbfgh", "acbfegh"};
  vector<int> expected = {2, 0, 2};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, SelfAuthoredSingleContainer) {
  vector<string> wordsContainer = {"hello"};
  vector<string> wordsQuery = {"hello", "lo", "world"};
  vector<int> expected = {0, 0, 0};  // 只有一个 container，所有 query 都选它
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, SelfAuthoredEmptySuffix) {
  vector<string> wordsContainer = {"abc", "de", "fghi"};
  vector<string> wordsQuery = {"xyz", "uv"};
  // 最长公共后缀均为 ""，选最短长度: "de"(2) < "abc"(3) < "fghi"(4)，索引 1
  vector<int> expected = {1, 1};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, SelfAuthoredTieSameLen) {
  vector<string> wordsContainer = {"ab", "cd", "ef"};
  vector<string> wordsQuery = {"x"};
  // 所有 container 长度都是 2，公共后缀 ""，选索引最小的 0
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, SelfAuthoredExactMatch) {
  vector<string> wordsContainer = {"code", "decode", "encode"};
  vector<string> wordsQuery = {"code"};
  // "code" 与 "code" 完全匹配（后缀 "code"）
  // "decode" 和 "encode" 也共享后缀 "code"，但长度分别是 6 和 6，"code" 长度为 4，最短
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, SelfAuthoredLongerSuffixPreferred) {
  vector<string> wordsContainer = {"abc", "bc", "c"};
  vector<string> wordsQuery = {"abc"};
  // "abc" 与 "abc" 完全匹配（后缀 "abc"，长度 3），索引 0
  // 注意 "bc" 和 "c" 也匹配后缀 "bc" 和 "c"，但 "abc" 匹配了最长后缀 "abc"
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

TEST_P(LongestCommonSuffixQueriesTest, SelfAuthoredPartialMatch) {
  vector<string> wordsContainer = {"abcde", "bcde", "cde"};
  vector<string> wordsQuery = {"bcde"};
  // "bcde" 与 "bcde"(idx=1) 完全匹配 -> 后缀 "bcde"
  // "abcde" 也共享后缀 "bcde"，但长度 5 > 3(索引1的长度)
  // "cde" 只共享后缀 "cde"（长度 3 < 4)
  vector<int> expected = {1};
  EXPECT_EQ(expected, solution.stringIndices(wordsContainer, wordsQuery));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestCommonSuffixQueriesTest,
    ::testing::ValuesIn(LongestCommonSuffixQueriesSolution().getStrategyNames()));

}  // namespace problem_3093
}  // namespace leetcode
