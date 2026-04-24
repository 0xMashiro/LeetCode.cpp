#include "leetcode/problems/furthest-point-from-origin.h"
#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2833 {

class FurthestPointFromOriginTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  FurthestPointFromOriginSolution solution;
};

TEST_P(FurthestPointFromOriginTest, Example1) {
  string moves = "L_RL__R";
  int expected = 3;
  EXPECT_EQ(expected, solution.furthestDistanceFromOrigin(moves));
}

TEST_P(FurthestPointFromOriginTest, Example2) {
  string moves = "_R__LL_";
  int expected = 5;
  EXPECT_EQ(expected, solution.furthestDistanceFromOrigin(moves));
}

TEST_P(FurthestPointFromOriginTest, Example3) {
  string moves = "_______";
  int expected = 7;
  EXPECT_EQ(expected, solution.furthestDistanceFromOrigin(moves));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FurthestPointFromOriginTest,
    ::testing::ValuesIn(FurthestPointFromOriginSolution().getStrategyNames()));

}  // namespace problem_2833
}  // namespace leetcode
