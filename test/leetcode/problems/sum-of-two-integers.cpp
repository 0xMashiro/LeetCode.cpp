#include "leetcode/problems/sum-of-two-integers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_371 {

class SumOfTwoIntegersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SumOfTwoIntegersSolution solution;
};

TEST_P(SumOfTwoIntegersTest, Example1) {
  int a = 1;
  int b = 2;
  EXPECT_EQ(3, solution.getSum(a, b));
}

TEST_P(SumOfTwoIntegersTest, Example2) {
  int a = 2;
  int b = 3;
  EXPECT_EQ(5, solution.getSum(a, b));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SumOfTwoIntegersTest,
    ::testing::ValuesIn(SumOfTwoIntegersSolution().getStrategyNames()));

}  // namespace problem_371
}  // namespace leetcode
