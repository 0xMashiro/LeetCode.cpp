#include "leetcode/problems/plus-one.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_66 {

class PlusOneTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PlusOneSolution solution;
};

TEST_P(PlusOneTest, Example1) {
  vector<int> digits = {1, 2, 3};
  vector<int> expected = {1, 2, 4};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, Example2) {
  vector<int> digits = {4, 3, 2, 1};
  vector<int> expected = {4, 3, 2, 2};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, Example3) {
  vector<int> digits = {9};
  vector<int> expected = {1, 0};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, SingleDigitNoCarry) {
  vector<int> digits = {5};
  vector<int> expected = {6};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, MultipleNines) {
  vector<int> digits = {9, 9, 9};
  vector<int> expected = {1, 0, 0, 0};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, MixedDigitsWithCarry) {
  vector<int> digits = {1, 9, 9};
  vector<int> expected = {2, 0, 0};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, LargeNumberNoCarry) {
  vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 9};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

TEST_P(PlusOneTest, ZeroLeadingDigit) {
  vector<int> digits = {0, 1, 2};
  // 根据题目描述，不会有前导零，但测试一下也无妨
  vector<int> expected = {0, 1, 3};
  vector<int> result = solution.plusOne(digits);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PlusOneTest,
    ::testing::ValuesIn(PlusOneSolution().getStrategyNames()));

}  // namespace problem_66
}  // namespace leetcode