
#include "leetcode/problems/count-the-number-of-infection-sequences.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2954 {

class CountTheNumberOfInfectionSequencesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheNumberOfInfectionSequencesSolution solution;
};

TEST_P(CountTheNumberOfInfectionSequencesTest, Example1) {
  int n = 5;
  vector<int> sick = {0, 4};
  int expected = 4;
  EXPECT_EQ(expected, solution.numberOfSequence(n, sick));
}

TEST_P(CountTheNumberOfInfectionSequencesTest, Example2) {
  int n = 4;
  vector<int> sick = {1};
  int expected = 3;
  EXPECT_EQ(expected, solution.numberOfSequence(n, sick));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountTheNumberOfInfectionSequencesTest,
    ::testing::ValuesIn(CountTheNumberOfInfectionSequencesSolution().getStrategyNames()));

}  // namespace problem_2954
}  // namespace leetcode
