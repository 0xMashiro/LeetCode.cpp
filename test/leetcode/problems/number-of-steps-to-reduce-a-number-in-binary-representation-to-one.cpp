#include "leetcode/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1404 {

class NumberOfStepsToReduceANumberInBinaryRepresentationToOneTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution solution;
};

TEST_P(NumberOfStepsToReduceANumberInBinaryRepresentationToOneTest, Example1) {
  string s = "1101";
  int expected = 6;
  EXPECT_EQ(expected, solution.numSteps(s));
}

TEST_P(NumberOfStepsToReduceANumberInBinaryRepresentationToOneTest, Example2) {
  string s = "10";
  int expected = 1;
  EXPECT_EQ(expected, solution.numSteps(s));
}

TEST_P(NumberOfStepsToReduceANumberInBinaryRepresentationToOneTest, Example3) {
  string s = "1";
  int expected = 0;
  EXPECT_EQ(expected, solution.numSteps(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfStepsToReduceANumberInBinaryRepresentationToOneTest,
    ::testing::ValuesIn(NumberOfStepsToReduceANumberInBinaryRepresentationToOneSolution().getStrategyNames()));

}  // namespace problem_1404
}  // namespace leetcode
