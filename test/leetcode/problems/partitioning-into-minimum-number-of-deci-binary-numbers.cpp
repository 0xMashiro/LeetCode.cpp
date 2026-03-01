#include "leetcode/problems/partitioning-into-minimum-number-of-deci-binary-numbers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1689 {

class PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution solution;
};

TEST_P(PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest, Example1) {
  string n = "32";
  int expected = 3;
  EXPECT_EQ(expected, solution.minPartitions(n));
}

TEST_P(PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest, Example2) {
  string n = "82734";
  int expected = 8;
  EXPECT_EQ(expected, solution.minPartitions(n));
}

TEST_P(PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest, Example3) {
  string n = "27346209830709182346";
  int expected = 9;
  EXPECT_EQ(expected, solution.minPartitions(n));
}

TEST_P(PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest, SingleDigit) {
  string n = "5";
  int expected = 5;
  EXPECT_EQ(expected, solution.minPartitions(n));
}

TEST_P(PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest, AllZeros) {
  string n = "10";
  int expected = 1;
  EXPECT_EQ(expected, solution.minPartitions(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PartitioningIntoMinimumNumberOfDeciBinaryNumbersTest,
    ::testing::ValuesIn(PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution().getStrategyNames()));

}  // namespace problem_1689
}  // namespace leetcode
