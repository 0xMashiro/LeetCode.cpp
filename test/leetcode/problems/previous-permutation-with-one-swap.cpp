#include "leetcode/problems/previous-permutation-with-one-swap.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1053 {

class PreviousPermutationWithOneSwapTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PreviousPermutationWithOneSwapSolution solution;
};

// 示例1: arr = [3,2,1] -> [3,1,2]
TEST_P(PreviousPermutationWithOneSwapTest, Example1) {
  vector<int> arr = {3, 2, 1};
  vector<int> expected = {3, 1, 2};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 示例2: arr = [1,1,5] -> [1,1,5]（已经是最小排列）
TEST_P(PreviousPermutationWithOneSwapTest, Example2) {
  vector<int> arr = {1, 1, 5};
  vector<int> expected = {1, 1, 5};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 示例3: arr = [1,9,4,6,7] -> [1,7,4,6,9]
TEST_P(PreviousPermutationWithOneSwapTest, Example3) {
  vector<int> arr = {1, 9, 4, 6, 7};
  vector<int> expected = {1, 7, 4, 6, 9};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 边界情况：单元素
TEST_P(PreviousPermutationWithOneSwapTest, SingleElement) {
  vector<int> arr = {5};
  vector<int> expected = {5};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 边界情况：两个元素，可以交换
TEST_P(PreviousPermutationWithOneSwapTest, TwoElementsSwap) {
  vector<int> arr = {2, 1};
  vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 边界情况：两个元素，不需要交换
TEST_P(PreviousPermutationWithOneSwapTest, TwoElementsNoSwap) {
  vector<int> arr = {1, 2};
  vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 边界情况：全部相同元素
TEST_P(PreviousPermutationWithOneSwapTest, AllSameElements) {
  vector<int> arr = {3, 3, 3, 3};
  vector<int> expected = {3, 3, 3, 3};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 边界情况：升序数组（已经是最小排列）
TEST_P(PreviousPermutationWithOneSwapTest, AscendingOrder) {
  vector<int> arr = {1, 2, 3, 4, 5};
  vector<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 边界情况：降序数组 [5,4,3,2,1]
// 下降点：i=0(5>4), i=1(4>3), i=2(3>2), i=3(2>1)
// 选择最右边的下降点 i=3，右侧小于2的最大值是1，交换得 [5,4,3,1,2]
TEST_P(PreviousPermutationWithOneSwapTest, DescendingOrder) {
  vector<int> arr = {5, 4, 3, 2, 1};
  vector<int> expected = {5, 4, 3, 1, 2};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 特殊情况：有重复元素 [3,1,2,2,2]
// 下降点：i=0(3>1)
// 右侧小于3的最大值是2，最左边的2在位置2，交换得 [2,1,3,2,2]
TEST_P(PreviousPermutationWithOneSwapTest, DuplicateElements) {
  vector<int> arr = {3, 1, 2, 2, 2};
  vector<int> expected = {2, 1, 3, 2, 2};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 特殊情况：重复元素2 [5,4,4,3,2,1]
// 下降点：i=0(5>4), i=1(4=4不算), i=2(4>3), i=3(3>2), i=4(2>1)
// 选择最右边的下降点 i=4，右侧小于2的最大值是1，交换得 [5,4,4,3,1,2]
TEST_P(PreviousPermutationWithOneSwapTest, DuplicateElements2) {
  vector<int> arr = {5, 4, 4, 3, 2, 1};
  vector<int> expected = {5, 4, 4, 3, 1, 2};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 特殊情况：多个下降点，验证选择最右边的 [1,5,3,4,2]
// 下降点：i=1(5>3), i=3(4>2)
// 选择最右边的 i=3，右侧小于4的最大值是2，交换得 [1,5,3,2,4]
TEST_P(PreviousPermutationWithOneSwapTest, MultipleDescents) {
  vector<int> arr = {1, 5, 3, 4, 2};
  vector<int> expected = {1, 5, 3, 2, 4};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

// 特殊情况：只有一个下降点但在中间 [1,3,2,4]
// 下降点：i=1(3>2)
// 右侧小于3的最大值是2，交换得 [1,2,3,4]
TEST_P(PreviousPermutationWithOneSwapTest, SingleDescentInMiddle) {
  vector<int> arr = {1, 3, 2, 4};
  vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(expected, solution.prevPermOpt1(arr));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PreviousPermutationWithOneSwapTest,
    ::testing::ValuesIn(PreviousPermutationWithOneSwapSolution().getStrategyNames()));

}  // namespace problem_1053
}  // namespace leetcode