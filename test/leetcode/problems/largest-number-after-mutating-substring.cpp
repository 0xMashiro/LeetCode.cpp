#include "leetcode/problems/largest-number-after-mutating-substring.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1946 {

class LargestNumberAfterMutatingSubstringTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LargestNumberAfterMutatingSubstringSolution solution;
};

TEST_P(LargestNumberAfterMutatingSubstringTest, Example1) {
  std::string num = "132";
  std::vector<int> change = {9, 8, 5, 0, 3, 6, 4, 2, 6, 8};
  // 1 maps to 8, 8 > 1，所以变异第一个字符
  EXPECT_EQ("832", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, Example2) {
  std::string num = "021";
  std::vector<int> change = {9, 4, 3, 5, 7, 2, 1, 9, 0, 6};
  // 0 -> 9, 2 -> 3, 1 -> 4，所有都变大，变异整个字符串
  EXPECT_EQ("934", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, Example3) {
  std::string num = "5";
  std::vector<int> change = {1, 4, 7, 5, 3, 2, 5, 6, 9, 4};
  // 5 -> 2，变小了，不变异
  EXPECT_EQ("5", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, SingleDigitIncrease) {
  std::string num = "0";
  std::vector<int> change = {9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // 0 -> 9，变大
  EXPECT_EQ("9", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, NoBeneficialChange) {
  // 所有数字变异后都变小或相等，不应该变异
  std::string num = "987";
  std::vector<int> change = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // 9->0, 8->0, 7->0 都变小，不变异
  EXPECT_EQ("987", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, NoBeneficialChangeAllEqual) {
  // 所有数字变异后都相等，不应该变异
  std::string num = "123";
  std::vector<int> change = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // 1->1, 2->2, 3->3 都相等，不变异
  EXPECT_EQ("123", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, PartialMutationMiddle) {
  std::string num = "334111";
  std::vector<int> change = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  // 3->7(变大), 3->7(变大), 4->6(变大), 1->9(变大), 1->9(变大), 1->9(变大)
  EXPECT_EQ("776999", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, StopWhenDecrease) {
  std::string num = "945";
  std::vector<int> change = {8, 9, 8, 8, 7, 6, 5, 4, 3, 2};
  // 9 -> 2 (变小，跳过)
  // 4 -> 7 (变大，开始变异)
  // 5 -> 6 (变大，继续变异)
  EXPECT_EQ("976", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, EqualValueContinue) {
  std::string num = "100";
  std::vector<int> change = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  // 1 -> 1 不变，但 0 -> 1 变大
  // 找到第一个 0 的位置，从那里开始变异
  EXPECT_EQ("111", solution.maximumNumber(num, change));
}

TEST_P(LargestNumberAfterMutatingSubstringTest, LargeNumber) {
  std::string num = "99999";
  std::vector<int> change = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
  // 9 -> 9 不变，也不会变大，所以不变异
  EXPECT_EQ("99999", solution.maximumNumber(num, change));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LargestNumberAfterMutatingSubstringTest,
    ::testing::ValuesIn(LargestNumberAfterMutatingSubstringSolution().getStrategyNames()));

}  // namespace problem_1946
}  // namespace leetcode
