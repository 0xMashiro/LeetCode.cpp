
#include "leetcode/problems/sort-characters-by-frequency.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_451 {

class SortCharactersByFrequencyTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SortCharactersByFrequencySolution solution;
};

// 验证结果字符串是否满足频率降序的要求
static bool isValidFrequencySort(const string& original, const string& result) {
  // 检查结果是否包含原字符串的所有字符
  if (original.size() != result.size()) return false;
  
  // 统计原字符串和结果的频率
  unordered_map<char, int> origFreq, resultFreq;
  for (char c : original) origFreq[c]++;
  for (char c : result) resultFreq[c]++;
  if (origFreq != resultFreq) return false;
  
  // 检查相同字符是否连续（频率排序的要求）
  for (size_t i = 1; i < result.size(); ++i) {
    if (result[i] == result[i-1]) continue;  // 相同字符连续，OK
    // 不同字符，检查频率是否非递增
    if (resultFreq[result[i]] > resultFreq[result[i-1]]) {
      return false;  // 后面的字符频率更高，违反降序
    }
  }
  return true;
}

TEST_P(SortCharactersByFrequencyTest, Example1) {
  string s = "tree";
  string result = solution.frequencySort(s);
  // 'e'出现2次，'r'和't'各1次，有效输出如"eert"、"eetr"等
  EXPECT_TRUE(isValidFrequencySort(s, result));
}

TEST_P(SortCharactersByFrequencyTest, Example2) {
  string s = "cccaaa";
  string result = solution.frequencySort(s);
  // 'c'和'a'都出现3次，有效输出如"aaaccc"、"cccaaa"
  EXPECT_TRUE(isValidFrequencySort(s, result));
}

TEST_P(SortCharactersByFrequencyTest, Example3) {
  string s = "Aabb";
  string result = solution.frequencySort(s);
  // 'b'出现2次，'A'和'a'各1次，'A'和'a'被视为不同字符
  // 有效输出如"bbAa"、"bbaA"
  EXPECT_TRUE(isValidFrequencySort(s, result));
}

TEST_P(SortCharactersByFrequencyTest, SingleChar) {
  string s = "a";
  string result = solution.frequencySort(s);
  EXPECT_EQ(result, "a");
}

TEST_P(SortCharactersByFrequencyTest, AllSameChar) {
  string s = "aaaa";
  string result = solution.frequencySort(s);
  EXPECT_EQ(result, "aaaa");
}

TEST_P(SortCharactersByFrequencyTest, AllDifferent) {
  string s = "abcd";
  string result = solution.frequencySort(s);
  // 所有字符频率都是1，任意顺序都有效
  EXPECT_TRUE(isValidFrequencySort(s, result));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SortCharactersByFrequencyTest,
    ::testing::ValuesIn(SortCharactersByFrequencySolution().getStrategyNames()));

}  // namespace problem_451
}  // namespace leetcode
