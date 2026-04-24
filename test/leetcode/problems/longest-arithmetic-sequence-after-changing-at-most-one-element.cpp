#include "leetcode/problems/longest-arithmetic-sequence-after-changing-at-most-one-element.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3872 {

class LongestArithmeticSequenceAfterChangingAtMostOneElementTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestArithmeticSequenceAfterChangingAtMostOneElementSolution solution;
};

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, Example1) {
  vector<int> nums = {9, 7, 5, 10, 1};
  EXPECT_EQ(5, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, Example2) {
  vector<int> nums = {1, 2, 6, 7};
  EXPECT_EQ(3, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredAllSame) {
  // 所有元素相同，本来就是等差
  vector<int> nums = {5, 5, 5, 5, 5};
  EXPECT_EQ(5, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredNoChangeNeeded) {
  // 已经是等差，不需要修改
  vector<int> nums = {1, 3, 5, 7, 9};
  EXPECT_EQ(5, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredSingleBad) {
  // 中间一个坏元素，修改后整个数组等差
  vector<int> nums = {1, 2, 3, 4, 100, 6, 7, 8};
  // 修改 100 -> 5，得到 [1,2,3,4,5,6,7,8] 长度 8
  EXPECT_EQ(8, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredFirstBad) {
  // 第一个元素需要修改
  vector<int> nums = {10, 2, 6, 7};
  // 修改 10 -> -2，得到 [-2,2,6,7]，子数组 [-2,2,6] 等差 4，长度 3
  EXPECT_EQ(3, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredLastBad) {
  // 修改第一个元素连接右边段
  // nums = [1, 2, 6, 10]
  // 修改 nums[0]=1 -> -2，得到 [-2,2,6,10]，等差 4，整数组长度 4
  vector<int> nums = {1, 2, 6, 10};
  EXPECT_EQ(4, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredMinimumN) {
  // 最小 n=4
  vector<int> nums = {1, 2, 3, 5};
  // 修改 5 -> 4，[1,2,3,4] 等差 1，长度 4
  EXPECT_EQ(4, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredBridgeTwoSegments) {
  // 左右两段差相同，通过修改中间元素桥接
  vector<int> nums = {1, 2, 3, 4, 10, 6, 7, 8, 9, 10, 11};
  // left[3]=4 (1,2,3,4, diff=1), right[5]=6 (6,7,8,9,10,11, diff=1)
  // nums[5]-nums[3]=6-4=2=2*1 ✓，修改 10->5，桥接后长度 11
  EXPECT_EQ(11, solution.longestArithmetic(nums));
}

TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, SelfAuthoredDifferentDiffs) {
  // 左右等差不同，只能取一边延伸，另一边也贡献
  // nums = [1, 3, 5, 7, 10, 13, 16, 19, 22]
  // 修改 nums[2]=5 -> 4，得到子数组 [4,7,10,13,16,19,22] (indices 2-8)，等差 3，长度 7
  vector<int> nums = {1, 3, 5, 7, 10, 13, 16, 19, 22};
  EXPECT_EQ(7, solution.longestArithmetic(nums));
}


// LeetCode 失败用例: WrongAnswerCase1
TEST_P(LongestArithmeticSequenceAfterChangingAtMostOneElementTest, WrongAnswerCase1) {
  // LeetCode WA: output=3, expected=4
    vector<int> nums = {79734, 13414, 52866, 11223, 46264, 42963};
    EXPECT_EQ(4, solution.longestArithmetic(nums));
}
INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestArithmeticSequenceAfterChangingAtMostOneElementTest,
    ::testing::ValuesIn(LongestArithmeticSequenceAfterChangingAtMostOneElementSolution().getStrategyNames()));

}  // namespace problem_3872
}  // namespace leetcode
