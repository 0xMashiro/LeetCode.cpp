
#include "leetcode/problems/number-of-balanced-integers-in-a-range.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3791 {

class NumberOfBalancedIntegersInARangeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfBalancedIntegersInARangeSolution solution;
};

TEST_P(NumberOfBalancedIntegersInARangeTest, Example1) {
  long long low = 1;
  long long high = 100;
  EXPECT_EQ(9, solution.countBalanced(low, high));
}

TEST_P(NumberOfBalancedIntegersInARangeTest, Example2) {
  long long low = 120;
  long long high = 129;
  EXPECT_EQ(1, solution.countBalanced(low, high));
}

TEST_P(NumberOfBalancedIntegersInARangeTest, Example3) {
  long long low = 1234;
  long long high = 1234;
  EXPECT_EQ(0, solution.countBalanced(low, high));
}

TEST_P(NumberOfBalancedIntegersInARangeTest, SingleDigit) {
  // 个位数不是平衡数（至少需要两位）
  long long low = 1;
  long long high = 9;
  EXPECT_EQ(0, solution.countBalanced(low, high));
}

TEST_P(NumberOfBalancedIntegersInARangeTest, AllTwoDigitBalanced) {
  // 11-99 中，11, 22, ..., 99 都是平衡数（9个）
  long long low = 11;
  long long high = 99;
  EXPECT_EQ(9, solution.countBalanced(low, high));
}

TEST_P(NumberOfBalancedIntegersInARangeTest, LargeRange) {
  // 测试大范围
  long long low = 1;
  long long high = 1000000;
  // 这个范围内有很多平衡数，我们只验证结果为正
  long long result = solution.countBalanced(low, high);
  EXPECT_GT(result, 0);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfBalancedIntegersInARangeTest,
    ::testing::ValuesIn(NumberOfBalancedIntegersInARangeSolution().getStrategyNames()));

}  // namespace problem_3791
}  // namespace leetcode
