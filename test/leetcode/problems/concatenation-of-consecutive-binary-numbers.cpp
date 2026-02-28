
#include "leetcode/problems/concatenation-of-consecutive-binary-numbers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1680 {

class ConcatenationOfConsecutiveBinaryNumbersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConcatenationOfConsecutiveBinaryNumbersSolution solution;
};

TEST_P(ConcatenationOfConsecutiveBinaryNumbersTest, Example1) {
  int n = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.concatenatedBinary(n));
}

TEST_P(ConcatenationOfConsecutiveBinaryNumbersTest, Example2) {
  int n = 3;
  int expected = 27;
  EXPECT_EQ(expected, solution.concatenatedBinary(n));
}

TEST_P(ConcatenationOfConsecutiveBinaryNumbersTest, Example3) {
  int n = 12;
  int expected = 505379714;
  EXPECT_EQ(expected, solution.concatenatedBinary(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConcatenationOfConsecutiveBinaryNumbersTest,
    ::testing::ValuesIn(ConcatenationOfConsecutiveBinaryNumbersSolution().getStrategyNames()));

}  // namespace problem_1680
}  // namespace leetcode
