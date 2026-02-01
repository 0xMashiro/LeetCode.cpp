#include "leetcode/problems/string-compression.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_443 {

class StringCompressionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  StringCompressionSolution solution;
};

TEST_P(StringCompressionTest, Example1) {
  vector<char> chars = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
  int expectedLen = 6;
  vector<char> expected = {'a', '2', 'b', '2', 'c', '3'};

  int result = solution.compress(chars);
  EXPECT_EQ(expectedLen, result);
  for (int i = 0; i < expectedLen; ++i) {
    EXPECT_EQ(expected[i], chars[i]);
  }
}

TEST_P(StringCompressionTest, Example2) {
  vector<char> chars = {'a'};
  int expectedLen = 1;
  vector<char> expected = {'a'};

  int result = solution.compress(chars);
  EXPECT_EQ(expectedLen, result);
  for (int i = 0; i < expectedLen; ++i) {
    EXPECT_EQ(expected[i], chars[i]);
  }
}

TEST_P(StringCompressionTest, Example3) {
  vector<char> chars = {'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b',
                        'b', 'b', 'b', 'b', 'b'};
  int expectedLen = 4;
  vector<char> expected = {'a', 'b', '1', '2'};

  int result = solution.compress(chars);
  EXPECT_EQ(expectedLen, result);
  for (int i = 0; i < expectedLen; ++i) {
    EXPECT_EQ(expected[i], chars[i]);
  }
}

TEST_P(StringCompressionTest, AllSameSingleChar) {
  vector<char> chars = {'a', 'a', 'a'};
  int expectedLen = 2;
  vector<char> expected = {'a', '3'};

  int result = solution.compress(chars);
  EXPECT_EQ(expectedLen, result);
  for (int i = 0; i < expectedLen; ++i) {
    EXPECT_EQ(expected[i], chars[i]);
  }
}

TEST_P(StringCompressionTest, AllDifferentChars) {
  vector<char> chars = {'a', 'b', 'c'};
  int expectedLen = 3;
  vector<char> expected = {'a', 'b', 'c'};

  int result = solution.compress(chars);
  EXPECT_EQ(expectedLen, result);
  for (int i = 0; i < expectedLen; ++i) {
    EXPECT_EQ(expected[i], chars[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, StringCompressionTest,
    ::testing::ValuesIn(StringCompressionSolution().getStrategyNames()));

}  // namespace problem_443
}  // namespace leetcode
