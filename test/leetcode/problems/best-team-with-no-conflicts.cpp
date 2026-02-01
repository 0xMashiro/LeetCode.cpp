#include "leetcode/problems/best-team-with-no-conflicts.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1626 {

class BestTeamWithNoConflictsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BestTeamWithNoConflictsSolution solution;
};

TEST_P(BestTeamWithNoConflictsTest, Example1) {
  vector<int> scores = {1, 3, 5, 10, 15};
  vector<int> ages = {1, 2, 3, 4, 5};
  EXPECT_EQ(34, solution.bestTeamScore(scores, ages));
}

TEST_P(BestTeamWithNoConflictsTest, Example2) {
  vector<int> scores = {4, 5, 6, 5};
  vector<int> ages = {2, 1, 2, 1};
  EXPECT_EQ(16, solution.bestTeamScore(scores, ages));
}

TEST_P(BestTeamWithNoConflictsTest, Example3) {
  vector<int> scores = {1, 2, 3, 5};
  vector<int> ages = {8, 9, 10, 1};
  EXPECT_EQ(6, solution.bestTeamScore(scores, ages));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BestTeamWithNoConflictsTest,
    ::testing::ValuesIn(BestTeamWithNoConflictsSolution().getStrategyNames()));

}  // namespace problem_1626
}  // namespace leetcode