#include "leetcode/problems/trionic-array-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3637 {

class TrionicArrayITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TrionicArrayISolution solution;
};

// Example 1: nums = [1,3,5,4,2,6], expected = true
// p = 2, q = 4
// nums[0...2] = [1,3,5] 严格递增
// nums[2...4] = [5,4,2] 严格递减
// nums[4...5] = [2,6] 严格递增
TEST_P(TrionicArrayITest, Example1) {
  vector<int> nums = {1, 3, 5, 4, 2, 6};
  EXPECT_TRUE(solution.isTrionic(nums));
}

// Example 2: nums = [2,1,3], expected = false
// 无法找到满足条件的 p 和 q
TEST_P(TrionicArrayITest, Example2) {
  vector<int> nums = {2, 1, 3};
  EXPECT_FALSE(solution.isTrionic(nums));
}

// 边界测试：最小长度 n = 3，无法构成 trionic（需要 0 < p < q < n-1，即至少 n >= 5）
// 实际上 n = 3 时，p 的范围是 1 到 0，不可能，所以应该返回 false
TEST_P(TrionicArrayITest, MinimumLength) {
  vector<int> nums1 = {1, 2, 3};  // 严格递增，无递减段
  EXPECT_FALSE(solution.isTrionic(nums1));
  
  vector<int> nums2 = {3, 2, 1};  // 严格递减
  EXPECT_FALSE(solution.isTrionic(nums2));
  
  vector<int> nums3 = {1, 3, 2};  // 递增后递减，无第三段递增
  EXPECT_FALSE(solution.isTrionic(nums3));
}

// 边界测试：n = 5，刚好满足条件的最小情况
TEST_P(TrionicArrayITest, SmallValidCase) {
  // [1, 3, 2, 4, 5]: p=1, q=2
  // [1,3] 递增, [3,2] 递减, [2,4,5] 递增
  vector<int> nums = {1, 3, 2, 4, 5};
  EXPECT_TRUE(solution.isTrionic(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TrionicArrayITest,
    ::testing::ValuesIn(TrionicArrayISolution().getStrategyNames()));

}  // namespace problem_3637
}  // namespace leetcode