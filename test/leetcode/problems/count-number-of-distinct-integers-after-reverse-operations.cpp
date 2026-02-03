
#include "leetcode/problems/count-number-of-distinct-integers-after-reverse-operations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2442 {

class CountNumberOfDistinctIntegersAfterReverseOperationsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountNumberOfDistinctIntegersAfterReverseOperationsSolution solution;
};

TEST_P(CountNumberOfDistinctIntegersAfterReverseOperationsTest, Example1) {
  vector<int> nums = {1, 13, 10, 12, 31};
  int expected = 6;
  EXPECT_EQ(expected, solution.countDistinctIntegers(nums));
}

TEST_P(CountNumberOfDistinctIntegersAfterReverseOperationsTest, Example2) {
  vector<int> nums = {2, 2, 2};
  int expected = 1;
  EXPECT_EQ(expected, solution.countDistinctIntegers(nums));
}

TEST_P(CountNumberOfDistinctIntegersAfterReverseOperationsTest, SingleElement) {
  vector<int> nums = {123};
  int expected = 2;  // 123 和 321
  EXPECT_EQ(expected, solution.countDistinctIntegers(nums));
}

TEST_P(CountNumberOfDistinctIntegersAfterReverseOperationsTest, Palindrome) {
  vector<int> nums = {121, 11, 12321};
  int expected = 3;  // 121, 11, 12321，它们反转后还是自身
  EXPECT_EQ(expected, solution.countDistinctIntegers(nums));
}

TEST_P(CountNumberOfDistinctIntegersAfterReverseOperationsTest, TrailingZeros) {
  vector<int> nums = {100, 1000, 10};
  int expected = 4;  // 原数：100, 1000, 10；反转后都是 1；总共 {1, 10, 100, 1000}
  EXPECT_EQ(expected, solution.countDistinctIntegers(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountNumberOfDistinctIntegersAfterReverseOperationsTest,
    ::testing::ValuesIn(CountNumberOfDistinctIntegersAfterReverseOperationsSolution().getStrategyNames()));

}  // namespace problem_2442
}  // namespace leetcode
