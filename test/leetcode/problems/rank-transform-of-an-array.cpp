#include "leetcode/problems/rank-transform-of-an-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1331 {

class RankTransformOfAnArrayTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RankTransformOfAnArraySolution solution;
};

TEST_P(RankTransformOfAnArrayTest, Example1) {
  vector<int> arr = {40, 10, 20, 30};
  vector<int> expected = {4, 1, 2, 3};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, Example2) {
  vector<int> arr = {100, 100, 100};
  vector<int> expected = {1, 1, 1};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, Example3) {
  vector<int> arr = {37, 12, 28, 9, 100, 56, 80, 5, 12};
  vector<int> expected = {5, 3, 4, 2, 8, 6, 7, 1, 3};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, EmptyArray) {
  vector<int> arr = {};
  vector<int> expected = {};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, SingleElement) {
  vector<int> arr = {42};
  vector<int> expected = {1};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, AlreadySorted) {
  vector<int> arr = {1, 2, 3, 4, 5};
  vector<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, ReverseSorted) {
  vector<int> arr = {5, 4, 3, 2, 1};
  vector<int> expected = {5, 4, 3, 2, 1};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

TEST_P(RankTransformOfAnArrayTest, NegativeNumbers) {
  vector<int> arr = {-10, -5, -20, 0, 5};
  vector<int> expected = {2, 3, 1, 4, 5};
  EXPECT_EQ(expected, solution.arrayRankTransform(arr));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RankTransformOfAnArrayTest,
    ::testing::ValuesIn(RankTransformOfAnArraySolution().getStrategyNames()));

}  // namespace problem_1331
}  // namespace leetcode