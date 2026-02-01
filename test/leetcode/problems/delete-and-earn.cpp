#include "leetcode/problems/delete-and-earn.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_740 {

class DeleteAndEarnTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DeleteAndEarnSolution solution;
};

// 示例 1: nums = [3,4,2], 输出: 6
// 删除 4 获得 4 分，同时删除 3，剩下 [2]
// 删除 2 获得 2 分，总共 6 分
TEST_P(DeleteAndEarnTest, Example1) {
  vector<int> nums = {3, 4, 2};
  EXPECT_EQ(6, solution.deleteAndEarn(nums));
}

// 示例 2: nums = [2,2,3,3,3,4], 输出: 9
// 删除所有 3 获得 9 分（3 * 3 = 9），同时删除所有 2 和 4
TEST_P(DeleteAndEarnTest, Example2) {
  vector<int> nums = {2, 2, 3, 3, 3, 4};
  EXPECT_EQ(9, solution.deleteAndEarn(nums));
}

// 边界情况：空数组
TEST_P(DeleteAndEarnTest, EmptyArray) {
  vector<int> nums = {};
  EXPECT_EQ(0, solution.deleteAndEarn(nums));
}

// 边界情况：只有一个元素
TEST_P(DeleteAndEarnTest, SingleElement) {
  vector<int> nums = {5};
  EXPECT_EQ(5, solution.deleteAndEarn(nums));
}

// 边界情况：所有元素相同
TEST_P(DeleteAndEarnTest, AllSameElements) {
  vector<int> nums = {3, 3, 3, 3};
  EXPECT_EQ(12, solution.deleteAndEarn(nums));  // 3 * 4 = 12
}

// 边界情况：连续递增
TEST_P(DeleteAndEarnTest, ConsecutiveNumbers) {
  vector<int> nums = {1, 2, 3, 4, 5};
  // 可以选择 1 + 3 + 5 = 9 或 2 + 4 = 6
  EXPECT_EQ(9, solution.deleteAndEarn(nums));
}

// 边界情况：不连续的大间隔
TEST_P(DeleteAndEarnTest, LargeGap) {
  vector<int> nums = {1, 1, 1, 100, 100};
  // 可以选择 1*3 + 100*2 = 3 + 200 = 203
  EXPECT_EQ(203, solution.deleteAndEarn(nums));
}

// 边界情况：只有两个连续数字
TEST_P(DeleteAndEarnTest, TwoConsecutive) {
  vector<int> nums = {1, 2};
  // 选择较大的那个
  EXPECT_EQ(2, solution.deleteAndEarn(nums));
}

// 复杂情况：多种数字混合
TEST_P(DeleteAndEarnTest, MixedNumbers) {
  vector<int> nums = {8, 10, 4, 9, 1, 3, 5, 9, 4, 10};
  // 数字 1,3,5,9 可以一起选（因为不是连续的）
  // 但最优应该是选择 1 + 8 + 10*2 = 1 + 8 + 20 = 29 或类似的组合
  // 实际计算：
  // total[1]=1, total[3]=3, total[4]=8, total[5]=5, total[8]=8, total[9]=18, total[10]=20
  // 选择 1,3,5,8,10 = 1+3+5+8+20 = 37
  // 或 1,3,5,9 = 1+3+5+18 = 27
  // 或 4,10 = 8+20 = 28
  EXPECT_EQ(37, solution.deleteAndEarn(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DeleteAndEarnTest,
    ::testing::ValuesIn(DeleteAndEarnSolution().getStrategyNames()));

}  // namespace problem_740
}  // namespace leetcode
