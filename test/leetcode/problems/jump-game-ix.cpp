#include "leetcode/problems/jump-game-ix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3660 {

class JumpGameIxTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  JumpGameIxSolution solution;
};

TEST_P(JumpGameIxTest, Example1) {
  vector<int> nums = {2, 1, 3};
  vector<int> expected = {2, 2, 3};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

TEST_P(JumpGameIxTest, Example2) {
  vector<int> nums = {2, 3, 1};
  vector<int> expected = {3, 3, 3};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

TEST_P(JumpGameIxTest, SelfAuthoredSingleElement) {
  vector<int> nums = {5};
  vector<int> expected = {5};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

TEST_P(JumpGameIxTest, SelfAuthoredIncreasing) {
  // 严格递增：无逆序对，每个元素自成一个分量
  vector<int> nums = {1, 2, 3, 4, 5};
  vector<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

TEST_P(JumpGameIxTest, SelfAuthoredDecreasing) {
  // 严格递减：全是逆序对，所有元素在一个分量中
  vector<int> nums = {5, 4, 3, 2, 1};
  vector<int> expected = {5, 5, 5, 5, 5};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

TEST_P(JumpGameIxTest, SelfAuthoredMixed) {
  // [3,1,4,2]: 所有位置都能到达最大值 4
  vector<int> nums = {3, 1, 4, 2};
  vector<int> expected = {4, 4, 4, 4};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

TEST_P(JumpGameIxTest, SelfAuthoredTwoComponents) {
  // [4, 2, 5, 3]: 
  // 逆序: (0,1):4>2, (0,3):4>3, (2,3):5>3
  // 分量1: {0,1} max=4, 分量2: {2,3} max=5
  // 检查: max(分量1)=4, min(分量2)=3, 4>3 所以合并!
  // 应该是 {0,1,2,3} max=5
  vector<int> nums = {4, 2, 5, 3};
  vector<int> expected = {5, 5, 5, 5};
  EXPECT_EQ(expected, solution.maxValue(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, JumpGameIxTest,
    ::testing::ValuesIn(JumpGameIxSolution().getStrategyNames()));

}  // namespace problem_3660
}  // namespace leetcode
