#include "leetcode/problems/find-the-first-player-to-win-k-games-in-a-row.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3175 {

class FindTheFirstPlayerToWinKGamesInARowTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheFirstPlayerToWinKGamesInARowSolution solution;
};

TEST_P(FindTheFirstPlayerToWinKGamesInARowTest, Example1) {
  vector<int> skills = {4, 2, 6, 3, 9};
  int k = 2;
  EXPECT_EQ(2, solution.findWinningPlayer(skills, k));
}

TEST_P(FindTheFirstPlayerToWinKGamesInARowTest, Example2) {
  vector<int> skills = {2, 5, 4};
  int k = 3;
  EXPECT_EQ(1, solution.findWinningPlayer(skills, k));
}

TEST_P(FindTheFirstPlayerToWinKGamesInARowTest, SelfAuthoredKEqualsOne) {
  vector<int> skills = {4, 2, 6, 3, 9};
  int k = 1;
  // Game: 0 vs 1, skill[0]=4 > skill[1]=2, player 0 wins immediately
  EXPECT_EQ(0, solution.findWinningPlayer(skills, k));
}

TEST_P(FindTheFirstPlayerToWinKGamesInARowTest, SelfAuthoredChampionNeverLoses) {
  vector<int> skills = {5, 3, 4, 2, 1};
  int k = 2;
  // 0 beats 1 (5>3), win=1; 0 beats 2 (5>4), win=2 == k
  EXPECT_EQ(0, solution.findWinningPlayer(skills, k));
}

TEST_P(FindTheFirstPlayerToWinKGamesInARowTest, SelfAuthoredMaxSkillAtEnd) {
  vector<int> skills = {1, 2, 3, 10};
  int k = 3;
  // 0 vs 1: 1<2, champion=1 win=1
  // 1 vs 2: 2<3, champion=2 win=1
  // 2 vs 3: 3<10, champion=3 win=1
  // loop ends, champion=3 is max, return 3
  EXPECT_EQ(3, solution.findWinningPlayer(skills, k));
}

TEST_P(FindTheFirstPlayerToWinKGamesInARowTest, SelfAuthoredKVeryLarge) {
  vector<int> skills = {2, 5, 4};
  int k = 100;
  // Player 1 (skill=5) is max, will keep winning indefinitely
  EXPECT_EQ(1, solution.findWinningPlayer(skills, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindTheFirstPlayerToWinKGamesInARowTest,
    ::testing::ValuesIn(FindTheFirstPlayerToWinKGamesInARowSolution().getStrategyNames()));

}  // namespace problem_3175
}  // namespace leetcode
