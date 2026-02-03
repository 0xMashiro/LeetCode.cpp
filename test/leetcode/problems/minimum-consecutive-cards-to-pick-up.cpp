#include "leetcode/problems/minimum-consecutive-cards-to-pick-up.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2260 {

class MinimumConsecutiveCardsToPickUpTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumConsecutiveCardsToPickUpSolution solution;
};

TEST_P(MinimumConsecutiveCardsToPickUpTest, Example1) {
  vector<int> cards = {3, 4, 2, 3, 4, 7};
  int expected = 4;
  EXPECT_EQ(expected, solution.minimumCardPickup(cards));
}

TEST_P(MinimumConsecutiveCardsToPickUpTest, Example2) {
  vector<int> cards = {1, 0, 5, 3};
  int expected = -1;
  EXPECT_EQ(expected, solution.minimumCardPickup(cards));
}

TEST_P(MinimumConsecutiveCardsToPickUpTest, SingleElement) {
  vector<int> cards = {5};
  int expected = -1;
  EXPECT_EQ(expected, solution.minimumCardPickup(cards));
}

TEST_P(MinimumConsecutiveCardsToPickUpTest, AdjacentDuplicate) {
  vector<int> cards = {1, 1};
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumCardPickup(cards));
}

TEST_P(MinimumConsecutiveCardsToPickUpTest, SameValueMultipleTimes) {
  vector<int> cards = {1, 2, 1, 3, 1};
  // 最小的应该是 [1, 2, 1] 或 [1, 3, 1]，长度为 3
  int expected = 3;
  EXPECT_EQ(expected, solution.minimumCardPickup(cards));
}

TEST_P(MinimumConsecutiveCardsToPickUpTest, LargeGap) {
  vector<int> cards = {1, 2, 3, 4, 5, 6, 1};
  int expected = 7;
  EXPECT_EQ(expected, solution.minimumCardPickup(cards));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumConsecutiveCardsToPickUpTest,
    ::testing::ValuesIn(MinimumConsecutiveCardsToPickUpSolution().getStrategyNames()));

}  // namespace problem_2260
}  // namespace leetcode
