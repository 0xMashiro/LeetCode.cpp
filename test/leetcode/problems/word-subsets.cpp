#include "leetcode/problems/word-subsets.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_916 {

class WordSubsetsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  WordSubsetsSolution solution;
};

TEST_P(WordSubsetsTest, Example1) {
  vector<string> words1 = {"amazon", "apple", "facebook", "google", "leetcode"};
  vector<string> words2 = {"e", "o"};
  vector<string> expected = {"facebook", "google", "leetcode"};
  vector<string> result = solution.wordSubsets(words1, words2);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(WordSubsetsTest, Example2) {
  vector<string> words1 = {"amazon", "apple", "facebook", "google", "leetcode"};
  vector<string> words2 = {"lc", "eo"};
  vector<string> expected = {"leetcode"};
  vector<string> result = solution.wordSubsets(words1, words2);
  EXPECT_EQ(expected, result);
}

TEST_P(WordSubsetsTest, Example3) {
  vector<string> words1 = {"acaac", "cccbb", "aacbb", "caacc", "bcbbb"};
  vector<string> words2 = {"c", "cc", "b"};
  vector<string> expected = {"cccbb"};
  vector<string> result = solution.wordSubsets(words1, words2);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, WordSubsetsTest,
    ::testing::ValuesIn(WordSubsetsSolution().getStrategyNames()));

}  // namespace problem_916
}  // namespace leetcode
