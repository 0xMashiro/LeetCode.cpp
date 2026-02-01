#include "leetcode/problems/maximum-multiplication-score.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3290 {

class MaximumMultiplicationScoreTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumMultiplicationScoreSolution solution;
};

TEST_P(MaximumMultiplicationScoreTest, Example1) {
  vector<int> a = {3, 2, 5, 6};
  vector<int> b = {2, -6, 4, -5, -3, 2, -7};
  long long expected = 26;
  EXPECT_EQ(expected, solution.maxScore(a, b));
}

TEST_P(MaximumMultiplicationScoreTest, Example2) {
  vector<int> a = {-1, 4, 5, -2};
  vector<int> b = {-5, -1, -3, -2, -4};
  long long expected = -1;
  EXPECT_EQ(expected, solution.maxScore(a, b));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumMultiplicationScoreTest,
    ::testing::ValuesIn(MaximumMultiplicationScoreSolution().getStrategyNames()));

}  // namespace problem_3290
}  // namespace leetcode
