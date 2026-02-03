
#include "leetcode/problems/letter-combinations-of-a-phone-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_17 {

class LetterCombinationsOfAPhoneNumberTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LetterCombinationsOfAPhoneNumberSolution solution;
};

// 比较两个字符串向量（忽略顺序）
static void expectVectorsEqualUnordered(const vector<string>& expected, const vector<string>& actual) {
  vector<string> sortedExpected = expected;
  vector<string> sortedActual = actual;
  sort(sortedExpected.begin(), sortedExpected.end());
  sort(sortedActual.begin(), sortedActual.end());
  EXPECT_EQ(sortedExpected, sortedActual);
}

TEST_P(LetterCombinationsOfAPhoneNumberTest, Example1) {
  string digits = "23";
  vector<string> expected = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
  vector<string> result = solution.letterCombinations(digits);
  expectVectorsEqualUnordered(expected, result);
}

TEST_P(LetterCombinationsOfAPhoneNumberTest, Example2) {
  string digits = "2";
  vector<string> expected = {"a", "b", "c"};
  vector<string> result = solution.letterCombinations(digits);
  expectVectorsEqualUnordered(expected, result);
}

TEST_P(LetterCombinationsOfAPhoneNumberTest, Example3) {
  string digits = "";
  vector<string> expected = {};
  vector<string> result = solution.letterCombinations(digits);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LetterCombinationsOfAPhoneNumberTest,
    ::testing::ValuesIn(LetterCombinationsOfAPhoneNumberSolution().getStrategyNames()));

}  // namespace problem_17
}  // namespace leetcode
