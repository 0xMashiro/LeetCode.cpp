
#include "leetcode/problems/add-two-integers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2235 {

class AddTwoIntegersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AddTwoIntegersSolution solution;
};

TEST_P(AddTwoIntegersTest, Example1) {
  int num1 = 12;
  int num2 = 5;
  int expected = 17;
  EXPECT_EQ(expected, solution.sum(num1, num2));
}

TEST_P(AddTwoIntegersTest, Example2) {
  int num1 = -10;
  int num2 = 4;
  int expected = -6;
  EXPECT_EQ(expected, solution.sum(num1, num2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AddTwoIntegersTest,
    ::testing::ValuesIn(AddTwoIntegersSolution().getStrategyNames()));

}  // namespace problem_2235
}  // namespace leetcode
