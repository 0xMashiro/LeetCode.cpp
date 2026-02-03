#include "leetcode/problems/check-if-two-string-arrays-are-equivalent.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1662 {

class CheckIfTwoStringArraysAreEquivalentTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CheckIfTwoStringArraysAreEquivalentSolution solution;
};

// 示例1: word1 = ["ab", "c"], word2 = ["a", "bc"] -> true
TEST_P(CheckIfTwoStringArraysAreEquivalentTest, Example1) {
  vector<string> word1 = {"ab", "c"};
  vector<string> word2 = {"a", "bc"};
  EXPECT_TRUE(solution.arrayStringsAreEqual(word1, word2));
}

// 示例2: word1 = ["a", "cb"], word2 = ["ab", "c"] -> false
TEST_P(CheckIfTwoStringArraysAreEquivalentTest, Example2) {
  vector<string> word1 = {"a", "cb"};
  vector<string> word2 = {"ab", "c"};
  EXPECT_FALSE(solution.arrayStringsAreEqual(word1, word2));
}

// 示例3: word1 = ["abc", "d", "defg"], word2 = ["abcddefg"] -> true
TEST_P(CheckIfTwoStringArraysAreEquivalentTest, Example3) {
  vector<string> word1 = {"abc", "d", "defg"};
  vector<string> word2 = {"abcddefg"};
  EXPECT_TRUE(solution.arrayStringsAreEqual(word1, word2));
}

// 边界：空字符串元素
TEST_P(CheckIfTwoStringArraysAreEquivalentTest, EmptyStringElements) {
  vector<string> word1 = {"", "a"};
  vector<string> word2 = {"a", ""};
  EXPECT_TRUE(solution.arrayStringsAreEqual(word1, word2));
}

// 边界：单元素数组
TEST_P(CheckIfTwoStringArraysAreEquivalentTest, SingleElement) {
  vector<string> word1 = {"abc"};
  vector<string> word2 = {"abc"};
  EXPECT_TRUE(solution.arrayStringsAreEqual(word1, word2));
}

// 边界：数组元素个数不同但拼接结果相同
TEST_P(CheckIfTwoStringArraysAreEquivalentTest, DifferentArrayLength) {
  vector<string> word1 = {"a", "b", "c"};
  vector<string> word2 = {"ab", "c"};
  EXPECT_TRUE(solution.arrayStringsAreEqual(word1, word2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CheckIfTwoStringArraysAreEquivalentTest,
    ::testing::ValuesIn(CheckIfTwoStringArraysAreEquivalentSolution().getStrategyNames()));

}  // namespace problem_1662
}  // namespace leetcode
