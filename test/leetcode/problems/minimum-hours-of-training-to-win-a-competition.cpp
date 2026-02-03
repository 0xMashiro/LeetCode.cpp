#include "leetcode/problems/minimum-hours-of-training-to-win-a-competition.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2383 {

class MinimumHoursOfTrainingToWinACompetitionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumHoursOfTrainingToWinACompetitionSolution solution;
};

TEST_P(MinimumHoursOfTrainingToWinACompetitionTest, Example1) {
  int initialEnergy = 5;
  int initialExperience = 3;
  vector<int> energy = {1, 4, 3, 2};
  vector<int> experience = {2, 6, 3, 1};
  EXPECT_EQ(8, solution.minNumberOfHours(initialEnergy, initialExperience, energy, experience));
}

TEST_P(MinimumHoursOfTrainingToWinACompetitionTest, Example2) {
  int initialEnergy = 2;
  int initialExperience = 4;
  vector<int> energy = {1};
  vector<int> experience = {3};
  EXPECT_EQ(0, solution.minNumberOfHours(initialEnergy, initialExperience, energy, experience));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumHoursOfTrainingToWinACompetitionTest,
    ::testing::ValuesIn(MinimumHoursOfTrainingToWinACompetitionSolution().getStrategyNames()));

}  // namespace problem_2383
}  // namespace leetcode
