#include "leetcode/problems/maximum-number-of-balloons.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1189 {

class MaximumNumberOfBalloonsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  MaximumNumberOfBalloonsSolution solution;
};

TEST_P(MaximumNumberOfBalloonsTest, Example1) {
  std::string text = "nlaebolko";
  int expected = 1;
  EXPECT_EQ(expected, solution.maxNumberOfBalloons(text));
}

TEST_P(MaximumNumberOfBalloonsTest, Example2) {
  std::string text = "loonbalxballpoon";
  int expected = 2;
  EXPECT_EQ(expected, solution.maxNumberOfBalloons(text));
}

TEST_P(MaximumNumberOfBalloonsTest, Example3) {
  std::string text = "leetcode";
  int expected = 0;
  EXPECT_EQ(expected, solution.maxNumberOfBalloons(text));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumNumberOfBalloonsTest,
    ::testing::ValuesIn(MaximumNumberOfBalloonsSolution().getStrategyNames()));

}  // namespace problem_1189
}  // namespace leetcode
