#include "leetcode/problems/can-you-eat-your-favorite-candy-on-your-favorite-day.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1744 {

class CanYouEatYourFavoriteCandyOnYourFavoriteDayTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution solution;
};

TEST_P(CanYouEatYourFavoriteCandyOnYourFavoriteDayTest, Example1) {
  vector<int> candiesCount = {7, 4, 5, 3, 8};
  vector<vector<int>> queries = {{0, 2, 2}, {4, 2, 4}, {2, 13, 1000000000}};
  vector<bool> expected = {true, false, true};
  vector<bool> result = solution.canEat(candiesCount, queries);
  EXPECT_EQ(expected, result);
}

TEST_P(CanYouEatYourFavoriteCandyOnYourFavoriteDayTest, Example2) {
  vector<int> candiesCount = {5, 2, 6, 4, 1};
  vector<vector<int>> queries = {{3, 1, 2}, {4, 10, 3}, {3, 10, 100}, {4, 100, 30}, {1, 3, 1}};
  vector<bool> expected = {false, true, true, false, false};
  vector<bool> result = solution.canEat(candiesCount, queries);
  EXPECT_EQ(expected, result);
}

TEST_P(CanYouEatYourFavoriteCandyOnYourFavoriteDayTest, SingleCandyType) {
  vector<int> candiesCount = {10};
  vector<vector<int>> queries = {{0, 0, 1}, {0, 5, 2}, {0, 9, 1}};
  vector<bool> expected = {true, true, true};
  vector<bool> result = solution.canEat(candiesCount, queries);
  EXPECT_EQ(expected, result);
}

TEST_P(CanYouEatYourFavoriteCandyOnYourFavoriteDayTest, BoundaryCase) {
  vector<int> candiesCount = {1, 1, 1};
  vector<vector<int>> queries = {{0, 0, 1}, {1, 1, 1}, {2, 2, 1}};
  vector<bool> expected = {true, true, true};
  vector<bool> result = solution.canEat(candiesCount, queries);
  EXPECT_EQ(expected, result);
}

TEST_P(CanYouEatYourFavoriteCandyOnYourFavoriteDayTest, CannotEatTooEarly) {
  vector<int> candiesCount = {100, 1};
  vector<vector<int>> queries = {{1, 0, 1}};
  vector<bool> expected = {false};
  vector<bool> result = solution.canEat(candiesCount, queries);
  EXPECT_EQ(expected, result);
}

TEST_P(CanYouEatYourFavoriteCandyOnYourFavoriteDayTest, LargeDailyCap) {
  vector<int> candiesCount = {1, 1, 1};
  vector<vector<int>> queries = {{2, 0, 1000000000}};
  vector<bool> expected = {true};
  vector<bool> result = solution.canEat(candiesCount, queries);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CanYouEatYourFavoriteCandyOnYourFavoriteDayTest,
    ::testing::ValuesIn(CanYouEatYourFavoriteCandyOnYourFavoriteDaySolution().getStrategyNames()));

}  // namespace problem_1744
}  // namespace leetcode
