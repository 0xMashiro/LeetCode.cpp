#include "leetcode/problems/longest-balanced-subarray-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3721 {

class LongestBalancedSubarrayIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestBalancedSubarrayIiSolution solution;
};

TEST_P(LongestBalancedSubarrayIiTest, Example1) {
  vector<int> nums = {2, 5, 4, 3};
  EXPECT_EQ(4, solution.longestBalanced(nums));
}

TEST_P(LongestBalancedSubarrayIiTest, Example2) {
  vector<int> nums = {3, 2, 2, 5, 4};
  EXPECT_EQ(5, solution.longestBalanced(nums));
}

TEST_P(LongestBalancedSubarrayIiTest, Example3) {
  vector<int> nums = {1, 2, 3, 2};
  EXPECT_EQ(3, solution.longestBalanced(nums));
}

TEST_P(LongestBalancedSubarrayIiTest, SingleElement) {
  // 单个偶数：distinct_even=1, distinct_odd=0，不平衡
  vector<int> nums1 = {2};
  EXPECT_EQ(0, solution.longestBalanced(nums1));
  
  // 单个奇数：distinct_even=0, distinct_odd=1，不平衡
  vector<int> nums2 = {3};
  EXPECT_EQ(0, solution.longestBalanced(nums2));
}

TEST_P(LongestBalancedSubarrayIiTest, TwoElements) {
  // 偶+奇，平衡
  vector<int> nums1 = {2, 3};
  EXPECT_EQ(2, solution.longestBalanced(nums1));
  
  // 奇+偶，平衡
  vector<int> nums2 = {3, 2};
  EXPECT_EQ(2, solution.longestBalanced(nums2));
  
  // 两个偶数，不平衡
  vector<int> nums3 = {2, 4};
  EXPECT_EQ(0, solution.longestBalanced(nums3));
  
  // 两个奇数，不平衡
  vector<int> nums4 = {1, 3};
  EXPECT_EQ(0, solution.longestBalanced(nums4));
}

TEST_P(LongestBalancedSubarrayIiTest, AllSame) {
  // 全相同偶数
  vector<int> nums1 = {2, 2, 2, 2};
  EXPECT_EQ(0, solution.longestBalanced(nums1));
  
  // 全相同奇数
  vector<int> nums2 = {3, 3, 3, 3};
  EXPECT_EQ(0, solution.longestBalanced(nums2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestBalancedSubarrayIiTest,
    ::testing::ValuesIn(LongestBalancedSubarrayIiSolution().getStrategyNames()));

}  // namespace problem_3721
}  // namespace leetcode
