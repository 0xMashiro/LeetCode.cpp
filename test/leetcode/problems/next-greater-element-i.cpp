#include "leetcode/problems/next-greater-element-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_496 {

class NextGreaterElementITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NextGreaterElementISolution solution;
};

// 示例 1
TEST_P(NextGreaterElementITest, Example1) {
  vector<int> nums1 = {4, 1, 2};
  vector<int> nums2 = {1, 3, 4, 2};
  vector<int> expected = {-1, 3, -1};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

// 示例 2
TEST_P(NextGreaterElementITest, Example2) {
  vector<int> nums1 = {2, 4};
  vector<int> nums2 = {1, 2, 3, 4};
  vector<int> expected = {3, -1};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

// 边界情况：nums1 只有一个元素，且在 nums2 末尾（无下一个更大元素）
TEST_P(NextGreaterElementITest, SingleElementNoGreater) {
  vector<int> nums1 = {5};
  vector<int> nums2 = {1, 2, 3, 4, 5};
  vector<int> expected = {-1};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

// 边界情况：nums1 只有一个元素，有下一个更大元素
TEST_P(NextGreaterElementITest, SingleElementWithGreater) {
  vector<int> nums1 = {3};
  vector<int> nums2 = {1, 2, 3, 4, 5};
  vector<int> expected = {4};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

// 边界情况：递减序列，所有元素都没有下一个更大元素
TEST_P(NextGreaterElementITest, DescendingSequence) {
  vector<int> nums1 = {5, 4, 3};
  vector<int> nums2 = {5, 4, 3, 2, 1};
  vector<int> expected = {-1, -1, -1};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

// 边界情况：递增序列，所有元素都有下一个更大元素
TEST_P(NextGreaterElementITest, AscendingSequence) {
  vector<int> nums1 = {1, 2, 3};
  vector<int> nums2 = {1, 2, 3, 4, 5};
  vector<int> expected = {2, 3, 4};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

// 边界情况：nums1 等于 nums2
TEST_P(NextGreaterElementITest, Nums1EqualsNums2) {
  vector<int> nums1 = {1, 2, 3};
  vector<int> nums2 = {1, 2, 3};
  vector<int> expected = {2, 3, -1};
  EXPECT_EQ(expected, solution.nextGreaterElement(nums1, nums2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NextGreaterElementITest,
    ::testing::ValuesIn(NextGreaterElementISolution().getStrategyNames()));

}  // namespace problem_496
}  // namespace leetcode
