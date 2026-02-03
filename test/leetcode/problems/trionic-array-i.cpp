#include "leetcode/problems/trionic-array-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3637 {

class TrionicArrayITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TrionicArrayISolution solution;
};

// 示例 1: [1,3,5,4,2,6] -> true
TEST_P(TrionicArrayITest, Example1) {
  vector<int> nums = {1, 3, 5, 4, 2, 6};
  EXPECT_TRUE(solution.isTrionic(nums));
}

// 示例 2: [2,1,3] -> false
TEST_P(TrionicArrayITest, Example2) {
  vector<int> nums = {2, 1, 3};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界：全递增 [1,2,3,4,5] -> false
TEST_P(TrionicArrayITest, AllIncreasing) {
  vector<int> nums = {1, 2, 3, 4, 5};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界：全递减 [5,4,3,2,1] -> false
TEST_P(TrionicArrayITest, AllDecreasing) {
  vector<int> nums = {5, 4, 3, 2, 1};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界：只有递增和递减，没有第三段递增 [1,3,2] -> false
TEST_P(TrionicArrayITest, NoThirdSegment) {
  vector<int> nums = {1, 3, 2};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界：最小长度 n=3，但需要 0<p<q<n-1 即 p=1,q=... 不可能满足 -> false
TEST_P(TrionicArrayITest, MinLength) {
  vector<int> nums = {1, 2, 3};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 特殊情况：峰值在中间，谷底在末尾前 [1,2,5,4,3,6] -> true
TEST_P(TrionicArrayITest, ValidTrionic) {
  vector<int> nums = {1, 2, 5, 4, 3, 6};
  EXPECT_TRUE(solution.isTrionic(nums));
}

// 特殊情况：多个峰谷 [1,3,2,4,3,5] -> false（不是 trionic）
TEST_P(TrionicArrayITest, MultiplePeaks) {
  vector<int> nums = {1, 3, 2, 4, 3, 5};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界：相等元素 [1,2,2,1,2] -> false（要求严格递增/递减）
TEST_P(TrionicArrayITest, EqualElements) {
  vector<int> nums = {1, 2, 2, 1, 2};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界：负数 [ -5, -3, -1, -4, -2] -> true
TEST_P(TrionicArrayITest, NegativeNumbers) {
  vector<int> nums = {-5, -3, -1, -4, -2};
  EXPECT_TRUE(solution.isTrionic(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TrionicArrayITest,
    ::testing::ValuesIn(TrionicArrayISolution().getStrategyNames()));

}  // namespace problem_3637
}  // namespace leetcode
