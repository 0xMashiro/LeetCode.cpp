
#include "leetcode/problems/get-maximum-in-generated-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1646 {

class GetMaximumInGeneratedArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  GetMaximumInGeneratedArraySolution solution;
};

TEST_P(GetMaximumInGeneratedArrayTest, Example1) {
  int n = 7;
  int expected = 3;
  EXPECT_EQ(expected, solution.getMaximumGenerated(n));
}

TEST_P(GetMaximumInGeneratedArrayTest, Example2) {
  int n = 2;
  int expected = 1;
  EXPECT_EQ(expected, solution.getMaximumGenerated(n));
}

TEST_P(GetMaximumInGeneratedArrayTest, Example3) {
  int n = 3;
  int expected = 2;
  EXPECT_EQ(expected, solution.getMaximumGenerated(n));
}

TEST_P(GetMaximumInGeneratedArrayTest, EdgeCaseN0) {
  int n = 0;
  int expected = 0;
  EXPECT_EQ(expected, solution.getMaximumGenerated(n));
}

TEST_P(GetMaximumInGeneratedArrayTest, EdgeCaseN1) {
  int n = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.getMaximumGenerated(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, GetMaximumInGeneratedArrayTest,
    ::testing::ValuesIn(GetMaximumInGeneratedArraySolution().getStrategyNames()));

}  // namespace problem_1646
}  // namespace leetcode
