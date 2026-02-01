#include "leetcode/problems/rotate-function.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_396 {

class RotateFunctionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RotateFunctionSolution solution;
};

TEST_P(RotateFunctionTest, Example1) {
  vector<int> nums = {4, 3, 2, 6};
  // F(0) = 0*4 + 1*3 + 2*2 + 3*6 = 0 + 3 + 4 + 18 = 25
  // F(1) = 0*6 + 1*4 + 2*3 + 3*2 = 0 + 4 + 6 + 6 = 16
  // F(2) = 0*2 + 1*6 + 2*4 + 3*3 = 0 + 6 + 8 + 9 = 23
  // F(3) = 0*3 + 1*2 + 2*6 + 3*4 = 0 + 2 + 12 + 12 = 26
  // max = 26
  EXPECT_EQ(26, solution.maxRotateFunction(nums));
}

TEST_P(RotateFunctionTest, Example2) {
  vector<int> nums = {100};
  // F(0) = 0*100 = 0
  EXPECT_EQ(0, solution.maxRotateFunction(nums));
}

TEST_P(RotateFunctionTest, TwoElements) {
  vector<int> nums = {1, 2};
  // F(0) = 0*1 + 1*2 = 2
  // F(1) = 0*2 + 1*1 = 1
  // max = 2
  EXPECT_EQ(2, solution.maxRotateFunction(nums));
}

TEST_P(RotateFunctionTest, AllSameElements) {
  vector<int> nums = {5, 5, 5, 5};
  // F(0) = 0*5 + 1*5 + 2*5 + 3*5 = 0 + 5 + 10 + 15 = 30
  // F(1) = 0*5 + 1*5 + 2*5 + 3*5 = 30
  // 所有F(k)都相等
  EXPECT_EQ(30, solution.maxRotateFunction(nums));
}

TEST_P(RotateFunctionTest, NegativeNumbers) {
  vector<int> nums = {-1, -2, -3};
  // F(0) = 0*(-1) + 1*(-2) + 2*(-3) = 0 - 2 - 6 = -8
  // F(1) = 0*(-3) + 1*(-1) + 2*(-2) = 0 - 1 - 4 = -5
  // F(2) = 0*(-2) + 1*(-3) + 2*(-1) = 0 - 3 - 2 = -5
  // max = -5
  EXPECT_EQ(-5, solution.maxRotateFunction(nums));
}

TEST_P(RotateFunctionTest, MixedNumbers) {
  vector<int> nums = {1, -1, 2, -2};
  // F(0) = 0*1 + 1*(-1) + 2*2 + 3*(-2) = 0 - 1 + 4 - 6 = -3
  // F(1) = 0*(-2) + 1*1 + 2*(-1) + 3*2 = 0 + 1 - 2 + 6 = 5
  // F(2) = 0*2 + 1*(-2) + 2*1 + 3*(-1) = 0 - 2 + 2 - 3 = -3
  // F(3) = 0*(-1) + 1*2 + 2*(-2) + 3*1 = 0 + 2 - 4 + 3 = 1
  // max = 5
  EXPECT_EQ(5, solution.maxRotateFunction(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RotateFunctionTest,
    ::testing::ValuesIn(RotateFunctionSolution().getStrategyNames()));

}  // namespace problem_396
}  // namespace leetcode
