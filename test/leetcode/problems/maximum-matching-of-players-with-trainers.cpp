#include "leetcode/problems/maximum-matching-of-players-with-trainers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2410 {

class MaximumMatchingOfPlayersWithTrainersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumMatchingOfPlayersWithTrainersSolution solution;
};

TEST_P(MaximumMatchingOfPlayersWithTrainersTest, Example1) {
  vector<int> players = {4, 7, 9};
  vector<int> trainers = {8, 2, 5, 8};
  int expected = 2;
  EXPECT_EQ(expected, solution.matchPlayersAndTrainers(players, trainers));
}

TEST_P(MaximumMatchingOfPlayersWithTrainersTest, Example2) {
  vector<int> players = {1, 1, 1};
  vector<int> trainers = {10};
  int expected = 1;
  EXPECT_EQ(expected, solution.matchPlayersAndTrainers(players, trainers));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumMatchingOfPlayersWithTrainersTest,
    ::testing::ValuesIn(MaximumMatchingOfPlayersWithTrainersSolution().getStrategyNames()));

}  // namespace problem_2410
}  // namespace leetcode
