#include "leetcode/problems/three-consecutive-odds.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1550 {

class ThreeConsecutiveOddsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ThreeConsecutiveOddsSolution solution;
};

// 示例1：没有三个连续的奇数
TEST_P(ThreeConsecutiveOddsTest, Example1) {
  vector<int> arr = {2, 6, 4, 1};
  EXPECT_FALSE(solution.threeConsecutiveOdds(arr));
}

// 示例2：有[5,7,23]三个连续的奇数
TEST_P(ThreeConsecutiveOddsTest, Example2) {
  vector<int> arr = {1, 2, 34, 3, 4, 5, 7, 23, 12};
  EXPECT_TRUE(solution.threeConsecutiveOdds(arr));
}

// 边界：空数组
TEST_P(ThreeConsecutiveOddsTest, EmptyArray) {
  vector<int> arr = {};
  EXPECT_FALSE(solution.threeConsecutiveOdds(arr));
}

// 边界：只有一个元素（奇数）
TEST_P(ThreeConsecutiveOddsTest, SingleOdd) {
  vector<int> arr = {1};
  EXPECT_FALSE(solution.threeConsecutiveOdds(arr));
}

// 边界：只有一个元素（偶数）
TEST_P(ThreeConsecutiveOddsTest, SingleEven) {
  vector<int> arr = {2};
  EXPECT_FALSE(solution.threeConsecutiveOdds(arr));
}

// 边界：两个奇数
TEST_P(ThreeConsecutiveOddsTest, TwoConsecutiveOdds) {
  vector<int> arr = {1, 3};
  EXPECT_FALSE(solution.threeConsecutiveOdds(arr));
}

// 边界：三个奇数在开头
TEST_P(ThreeConsecutiveOddsTest, ThreeOddsAtBeginning) {
  vector<int> arr = {1, 3, 5, 2, 4};
  EXPECT_TRUE(solution.threeConsecutiveOdds(arr));
}

// 边界：三个奇数在结尾
TEST_P(ThreeConsecutiveOddsTest, ThreeOddsAtEnd) {
  vector<int> arr = {2, 4, 6, 1, 3, 5};
  EXPECT_TRUE(solution.threeConsecutiveOdds(arr));
}

// 边界：正好三个元素，都是奇数
TEST_P(ThreeConsecutiveOddsTest, ExactlyThreeOdds) {
  vector<int> arr = {1, 3, 5};
  EXPECT_TRUE(solution.threeConsecutiveOdds(arr));
}

// 边界：正好三个元素，都是偶数
TEST_P(ThreeConsecutiveOddsTest, ExactlyThreeEvens) {
  vector<int> arr = {2, 4, 6};
  EXPECT_FALSE(solution.threeConsecutiveOdds(arr));
}

// 边界：多个连续的奇数
TEST_P(ThreeConsecutiveOddsTest, MoreThanThreeConsecutiveOdds) {
  vector<int> arr = {1, 3, 5, 7, 9};
  EXPECT_TRUE(solution.threeConsecutiveOdds(arr));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ThreeConsecutiveOddsTest,
    ::testing::ValuesIn(ThreeConsecutiveOddsSolution().getStrategyNames()));

}  // namespace problem_1550
}  // namespace leetcode
