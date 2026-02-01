#include "leetcode/problems/adjacent-increasing-subarrays-detection-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3350 {

class AdjacentIncreasingSubarraysDetectionIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AdjacentIncreasingSubarraysDetectionIiSolution solution;
};

// 题目示例 1
TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, Example1) {
  // [7,8,9] (索引2-4) 和 [2,3,4] (索引5-7) 都严格递增，k=3
  vector<int> nums = {2, 5, 7, 8, 9, 2, 3, 4, 3, 1};
  int expected = 3;
  EXPECT_EQ(expected, solution.maxIncreasingSubarrays(nums));
}

// 题目示例 2
TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, Example2) {
  // [1,2] (索引0-1) 和 [3,4] (索引2-3) 都严格递增，k=2
  vector<int> nums = {1, 2, 3, 4, 4, 4, 4, 5, 6, 7};
  int expected = 2;
  EXPECT_EQ(expected, solution.maxIncreasingSubarrays(nums));
}

// 基础边界测试
TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, MinimumCase) {
  // 最小长度，递增
  vector<int> nums = {1, 2};
  EXPECT_EQ(1, solution.maxIncreasingSubarrays(nums));
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, AllIncreasingEven) {
  // 全部递增，偶数长度
  vector<int> nums = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(3, solution.maxIncreasingSubarrays(nums));  // [1,2,3] 和 [4,5,6]
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, AllIncreasingOdd) {
  // 全部递增，奇数长度
  vector<int> nums = {1, 2, 3, 4, 5};
  EXPECT_EQ(2, solution.maxIncreasingSubarrays(nums));  // [1,2] 和 [3,4] 或类似
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, TwoEqualSegments) {
  // 两个等长递增段
  vector<int> nums = {1, 2, 3, 1, 2, 3};
  EXPECT_EQ(3, solution.maxIncreasingSubarrays(nums));  // [1,2,3] 和 [1,2,3]
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, DifferentLengthSegments) {
  // 两个不同长度的递增段
  vector<int> nums = {1, 2, 3, 4, 5, 1, 2, 3};
  EXPECT_EQ(3, solution.maxIncreasingSubarrays(nums));  // [3,4,5] 和 [1,2,3]
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, LongIncreasingSegments) {
  // 两个长度为8的递增段，总共16个元素
  // [1..8] (索引0-7) 和 [1..8] (索引8-15) 是两个相邻的长度为8的递增子数组
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(8, solution.maxIncreasingSubarrays(nums));
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, NoAdjacentIncreasing) {
  // 递减数组，只能形成单元素递增子数组
  vector<int> nums = {5, 4, 3, 2, 1};
  // 单元素子数组严格递增，k=1 应该可行
  EXPECT_EQ(1, solution.maxIncreasingSubarrays(nums));
}

TEST_P(AdjacentIncreasingSubarraysDetectionIiTest, WithDuplicates) {
  // 包含重复元素 [1,2] (位置0-1) 和 [2,3] (位置2-3，注意不是[2,2])
  // 实际上 inc = [1,2,1,2,3], start = [1,1,3,2,1]
  // k=2: inc[1]=2>=2, start[2]=3>=2，满足条件
  vector<int> nums = {1, 2, 2, 3, 4};
  EXPECT_EQ(2, solution.maxIncreasingSubarrays(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AdjacentIncreasingSubarraysDetectionIiTest,
    ::testing::ValuesIn(AdjacentIncreasingSubarraysDetectionIiSolution().getStrategyNames()));

}  // namespace problem_3350
}  // namespace leetcode
