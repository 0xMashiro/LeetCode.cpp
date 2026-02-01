#include "leetcode/problems/convert-integer-to-the-sum-of-two-no-zero-integers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1317 {

class ConvertIntegerToTheSumOfTwoNoZeroIntegersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution solution;
};

TEST_P(ConvertIntegerToTheSumOfTwoNoZeroIntegersTest, Example1) {
  int n = 2;
  vector<int> result = solution.getNoZeroIntegers(n);
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0] + result[1], n);
}

TEST_P(ConvertIntegerToTheSumOfTwoNoZeroIntegersTest, Example2) {
  int n = 11;
  vector<int> result = solution.getNoZeroIntegers(n);
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0] + result[1], n);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConvertIntegerToTheSumOfTwoNoZeroIntegersTest,
    ::testing::ValuesIn(ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution().getStrategyNames()));

}  // namespace problem_1317
}  // namespace leetcode
