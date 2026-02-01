#include "leetcode/problems/minimum-number-of-chairs-in-a-waiting-room.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3168 {

class MinimumNumberOfChairsInAWaitingRoomTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfChairsInAWaitingRoomSolution solution;
};

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, Example1) {
  string s = "EEEEEEE";
  EXPECT_EQ(7, solution.minimumChairs(s));
}

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, Example2) {
  string s = "ELELEEL";
  EXPECT_EQ(2, solution.minimumChairs(s));
}

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, Example3) {
  string s = "ELEELEELLL";
  EXPECT_EQ(3, solution.minimumChairs(s));
}

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, SingleEnter) {
  string s = "E";
  EXPECT_EQ(1, solution.minimumChairs(s));
}

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, EnterLeave) {
  string s = "EL";
  EXPECT_EQ(1, solution.minimumChairs(s));
}

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, Alternating) {
  string s = "ELELELEL";
  EXPECT_EQ(1, solution.minimumChairs(s));
}

TEST_P(MinimumNumberOfChairsInAWaitingRoomTest, AllLeaveFirst) {
  // L 不会在没有 E 的情况下出现，但根据题目 s 是有效的
  string s = "EELLEE";
  EXPECT_EQ(2, solution.minimumChairs(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfChairsInAWaitingRoomTest,
    ::testing::ValuesIn(MinimumNumberOfChairsInAWaitingRoomSolution().getStrategyNames()));

}  // namespace problem_3168
}  // namespace leetcode
