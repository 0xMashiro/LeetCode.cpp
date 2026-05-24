#include "leetcode/problems/jump-game-v.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1340 {

class JumpGameVTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  JumpGameVSolution solution;
};

TEST_P(JumpGameVTest, Example1) {
  vector<int> arr = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
  int d = 2;
  EXPECT_EQ(4, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, Example2) {
  vector<int> arr = {3, 3, 3, 3, 3};
  int d = 3;
  EXPECT_EQ(1, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, Example3) {
  vector<int> arr = {7, 6, 5, 4, 3, 2, 1};
  int d = 1;
  EXPECT_EQ(7, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, SelfAuthoredSingleElement) {
  vector<int> arr = {5};
  int d = 5;
  EXPECT_EQ(1, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, SelfAuthoredTwoElements) {
  vector<int> arr = {10, 5};
  int d = 1;
  EXPECT_EQ(2, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, SelfAuthoredDescendingWithD2) {
  vector<int> arr = {10, 9, 8, 7, 6, 5};
  int d = 2;
  // 从 10 可以跳 9->8(跳2步)... 或 9->7(跳2步从9出发)
  // 10->9->8->7->6->5 总共6个
  EXPECT_EQ(6, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, SelfAuthoredCannotJumpOverHigher) {
  vector<int> arr = {1, 100, 2};
  int d = 2;
  // 从 100 可以跳 1（向左）或 2（向右），但中间不能有 >= arr[i]
  // 100 -> 1 或 100 -> 2，最多2
  // 从 1 或 2 出发不能再跳（左右都更高或不存在），所以最多 2
  EXPECT_EQ(2, solution.maxJumps(arr, d));
}

TEST_P(JumpGameVTest, SelfAuthoredAllSameValues) {
  vector<int> arr = {5, 5, 5, 5};
  int d = 2;
  // 所有值相等，不能跳（需要严格大于），每个位置只能访问自己
  EXPECT_EQ(1, solution.maxJumps(arr, d));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, JumpGameVTest,
    ::testing::ValuesIn(JumpGameVSolution().getStrategyNames()));

}  // namespace problem_1340
}  // namespace leetcode
