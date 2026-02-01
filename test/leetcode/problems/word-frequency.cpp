#include "leetcode/problems/word-frequency.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_192 {

class WordFrequencyTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  WordFrequencySolution solution;
};

TEST_P(WordFrequencyTest, Example1) {
  // 题目示例：
  // the day is sunny the the
  // the sunny is is
  string content = "the day is sunny the the\nthe sunny is is";
  auto result = solution.wordFrequency(content);
  
  // 期望结果按频率降序：the(4), is(3), sunny(2), day(1)
  ASSERT_EQ(4, result.size());
  EXPECT_EQ("the", result[0].first);
  EXPECT_EQ(4, result[0].second);
  EXPECT_EQ("is", result[1].first);
  EXPECT_EQ(3, result[1].second);
  EXPECT_EQ("sunny", result[2].first);
  EXPECT_EQ(2, result[2].second);
  EXPECT_EQ("day", result[3].first);
  EXPECT_EQ(1, result[3].second);
}

TEST_P(WordFrequencyTest, SingleWord) {
  string content = "hello";
  auto result = solution.wordFrequency(content);
  
  ASSERT_EQ(1, result.size());
  EXPECT_EQ("hello", result[0].first);
  EXPECT_EQ(1, result[0].second);
}

TEST_P(WordFrequencyTest, MultipleSpaces) {
  string content = "a  b   c    a";
  auto result = solution.wordFrequency(content);
  
  ASSERT_EQ(3, result.size());
  // 按频率排序：a(2), b(1), c(1)
  // 由于频率唯一性保证，b 和 c 的顺序不重要
  EXPECT_EQ("a", result[0].first);
  EXPECT_EQ(2, result[0].second);
}

TEST_P(WordFrequencyTest, EmptyContent) {
  string content = "";
  auto result = solution.wordFrequency(content);
  
  EXPECT_TRUE(result.empty());
}

TEST_P(WordFrequencyTest, AllSameWord) {
  string content = "test test test test";
  auto result = solution.wordFrequency(content);
  
  ASSERT_EQ(1, result.size());
  EXPECT_EQ("test", result[0].first);
  EXPECT_EQ(4, result[0].second);
}

TEST_P(WordFrequencyTest, DifferentWords) {
  string content = "apple banana cherry";
  auto result = solution.wordFrequency(content);
  
  ASSERT_EQ(3, result.size());
  // 每个单词出现 1 次，顺序不确定（但频率相同）
  for (const auto& pair : result) {
    EXPECT_EQ(1, pair.second);
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, WordFrequencyTest,
    ::testing::ValuesIn(WordFrequencySolution().getStrategyNames()));

}  // namespace problem_192
}  // namespace leetcode
