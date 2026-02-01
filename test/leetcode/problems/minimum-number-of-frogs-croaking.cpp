
#include "leetcode/problems/minimum-number-of-frogs-croaking.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1419 {

class MinimumNumberOfFrogsCroakingTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfFrogsCroakingSolution solution;
};

TEST_P(MinimumNumberOfFrogsCroakingTest, Example1) {
  // 一只青蛙叫了两声
  string croakOfFrogs = "croakcroak";
  EXPECT_EQ(1, solution.minNumberOfFrogs(croakOfFrogs));
}

TEST_P(MinimumNumberOfFrogsCroakingTest, Example2) {
  // 两只青蛙交错叫声
  string croakOfFrogs = "crcoakroak";
  EXPECT_EQ(2, solution.minNumberOfFrogs(croakOfFrogs));
}

TEST_P(MinimumNumberOfFrogsCroakingTest, Example3) {
  // 无效组合（少了一个 'a'）
  string croakOfFrogs = "croakcrook";
  EXPECT_EQ(-1, solution.minNumberOfFrogs(croakOfFrogs));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfFrogsCroakingTest,
    ::testing::ValuesIn(MinimumNumberOfFrogsCroakingSolution().getStrategyNames()));

}  // namespace problem_1419
}  // namespace leetcode
