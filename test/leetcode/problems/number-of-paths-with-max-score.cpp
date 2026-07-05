#include "leetcode/problems/number-of-paths-with-max-score.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1301 {

class NumberOfPathsWithMaxScoreTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfPathsWithMaxScoreSolution solution;
};

TEST_P(NumberOfPathsWithMaxScoreTest, Example1) {
  std::vector<std::string> board = {"E23", "2X2", "12S"};
  std::vector<int> expected = {7, 1};
  EXPECT_EQ(expected, solution.pathsWithMaxScore(board));
}

TEST_P(NumberOfPathsWithMaxScoreTest, Example2) {
  std::vector<std::string> board = {"E12", "1X1", "21S"};
  std::vector<int> expected = {4, 2};
  EXPECT_EQ(expected, solution.pathsWithMaxScore(board));
}

TEST_P(NumberOfPathsWithMaxScoreTest, Example3) {
  std::vector<std::string> board = {"E11", "XXX", "11S"};
  std::vector<int> expected = {0, 0};
  EXPECT_EQ(expected, solution.pathsWithMaxScore(board));
}

TEST_P(NumberOfPathsWithMaxScoreTest, SelfAuthored2x2AllDigits) {
  // 2x2 board with all digits, no obstacles.
  // E 1
  // 1 S
  // Paths from E(0,0) to S(1,1):
  //   right(0,1)=1 then down(1,1)=S  -> sum=1
  //   down(1,0)=1 then right(1,1)=S  -> sum=1
  //   diagonal (1,1)=S              -> sum=0
  // Max sum = 1, ways = 2.
  std::vector<std::string> board = {"E1", "1S"};
  std::vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.pathsWithMaxScore(board));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfPathsWithMaxScoreTest,
    ::testing::ValuesIn(NumberOfPathsWithMaxScoreSolution().getStrategyNames()));

}  // namespace problem_1301
}  // namespace leetcode
