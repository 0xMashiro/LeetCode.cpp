#include "leetcode/problems/count-mentions-per-user.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3433 {

class CountMentionsPerUserTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountMentionsPerUserSolution solution;
};

TEST_P(CountMentionsPerUserTest, Example1) {
  int numberOfUsers = 2;
  vector<vector<string>> events = {
      {"MESSAGE", "10", "id1 id0"},
      {"OFFLINE", "11", "0"},
      {"MESSAGE", "71", "HERE"}
  };
  vector<int> expected = {2, 2};
  EXPECT_EQ(expected, solution.countMentions(numberOfUsers, events));
}

TEST_P(CountMentionsPerUserTest, Example2) {
  int numberOfUsers = 2;
  vector<vector<string>> events = {
      {"MESSAGE", "10", "id1 id0"},
      {"OFFLINE", "11", "0"},
      {"MESSAGE", "12", "ALL"}
  };
  vector<int> expected = {2, 2};
  EXPECT_EQ(expected, solution.countMentions(numberOfUsers, events));
}

TEST_P(CountMentionsPerUserTest, Example3) {
  int numberOfUsers = 2;
  vector<vector<string>> events = {
      {"OFFLINE", "10", "0"},
      {"MESSAGE", "12", "HERE"}
  };
  vector<int> expected = {0, 1};
  EXPECT_EQ(expected, solution.countMentions(numberOfUsers, events));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountMentionsPerUserTest,
    ::testing::ValuesIn(CountMentionsPerUserSolution().getStrategyNames()));

}  // namespace problem_3433
}  // namespace leetcode
