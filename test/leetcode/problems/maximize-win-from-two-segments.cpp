#include "leetcode/problems/maximize-win-from-two-segments.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2555 {

class MaximizeWinFromTwoSegmentsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximizeWinFromTwoSegmentsSolution solution;
};

TEST_P(MaximizeWinFromTwoSegmentsTest, Example1) {
  vector<int> prizePositions = {1, 1, 2, 2, 3, 3, 5};
  int k = 2;
  EXPECT_EQ(7, solution.maximizeWin(prizePositions, k));
}

TEST_P(MaximizeWinFromTwoSegmentsTest, Example2) {
  vector<int> prizePositions = {1, 2, 3, 4};
  int k = 0;
  EXPECT_EQ(2, solution.maximizeWin(prizePositions, k));
}

TEST_P(MaximizeWinFromTwoSegmentsTest, SingleElement) {
  vector<int> prizePositions = {1};
  int k = 0;
  EXPECT_EQ(1, solution.maximizeWin(prizePositions, k));
}

TEST_P(MaximizeWinFromTwoSegmentsTest, AllSamePosition) {
  vector<int> prizePositions = {5, 5, 5, 5, 5};
  int k = 0;
  EXPECT_EQ(5, solution.maximizeWin(prizePositions, k));
}

TEST_P(MaximizeWinFromTwoSegmentsTest, LargeK) {
  vector<int> prizePositions = {1, 2, 3, 4, 5};
  int k = 10;
  EXPECT_EQ(5, solution.maximizeWin(prizePositions, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximizeWinFromTwoSegmentsTest,
    ::testing::ValuesIn(MaximizeWinFromTwoSegmentsSolution().getStrategyNames()));

}  // namespace problem_2555
}  // namespace leetcode
