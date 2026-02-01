#include "leetcode/problems/kth-smallest-product-of-two-sorted-arrays.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2040 {

class KthSmallestProductOfTwoSortedArraysTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  KthSmallestProductOfTwoSortedArraysSolution solution;
};

// Example 1: nums1 = [2,5], nums2 = [3,4], k = 2, Output: 8
TEST_P(KthSmallestProductOfTwoSortedArraysTest, Example1) {
  vector<int> nums1 = {2, 5};
  vector<int> nums2 = {3, 4};
  long long k = 2;
  long long expected = 8;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// Example 2: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6, Output: 0
TEST_P(KthSmallestProductOfTwoSortedArraysTest, Example2) {
  vector<int> nums1 = {-4, -2, 0, 3};
  vector<int> nums2 = {2, 4};
  long long k = 6;
  long long expected = 0;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// Example 3: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3, Output: -6
TEST_P(KthSmallestProductOfTwoSortedArraysTest, Example3) {
  vector<int> nums1 = {-2, -1, 0, 1, 2};
  vector<int> nums2 = {-3, -1, 2, 4, 5};
  long long k = 3;
  long long expected = -6;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// 测试：单个元素
TEST_P(KthSmallestProductOfTwoSortedArraysTest, SingleElement) {
  vector<int> nums1 = {5};
  vector<int> nums2 = {3};
  long long k = 1;
  long long expected = 15;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// 测试：两个正数数组
TEST_P(KthSmallestProductOfTwoSortedArraysTest, TwoPositiveArrays) {
  vector<int> nums1 = {1, 2, 3};
  vector<int> nums2 = {1, 2, 3};
  // 乘积: 1, 2, 3, 2, 4, 6, 3, 6, 9
  // 排序: 1, 2, 2, 3, 3, 4, 6, 6, 9
  long long k = 5;
  long long expected = 3;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// 测试：两个负数数组
TEST_P(KthSmallestProductOfTwoSortedArraysTest, TwoNegativeArrays) {
  vector<int> nums1 = {-3, -2, -1};
  vector<int> nums2 = {-3, -2, -1};
  // 乘积: 9, 6, 3, 6, 4, 2, 3, 2, 1
  // 排序: 1, 2, 2, 3, 3, 4, 6, 6, 9
  long long k = 1;
  long long expected = 1;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
  k = 5;
  expected = 3;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// 测试：包含零的情况
TEST_P(KthSmallestProductOfTwoSortedArraysTest, WithZero) {
  vector<int> nums1 = {-1, 0, 1};
  vector<int> nums2 = {-1, 0, 1};
  // 乘积: 1, 0, -1, 0, 0, 0, -1, 0, 1
  // 排序: -1, -1, 0, 0, 0, 0, 0, 1, 1
  long long k = 1;
  long long expected = -1;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
  k = 3;
  expected = 0;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
  k = 9;
  expected = 1;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// 测试：k = 1（最小值）
TEST_P(KthSmallestProductOfTwoSortedArraysTest, KIsOne) {
  vector<int> nums1 = {-5, -3, 1, 2};
  vector<int> nums2 = {-4, -2, 3};
  // 最小乘积应该是 -5 * 3 = -15 或 2 * -4 = -8
  // 实际最小是 -5 * 3 = -15
  long long k = 1;
  long long expected = -15;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

// 测试：k = n*m（最大值）
TEST_P(KthSmallestProductOfTwoSortedArraysTest, KIsMax) {
  vector<int> nums1 = {-5, -3, 1, 2};
  vector<int> nums2 = {-4, -2, 3};
  // 最大乘积应该是 -5 * -4 = 20 或 2 * 3 = 6
  // 实际最大是 -5 * -4 = 20
  long long k = 12;  // 4 * 3
  long long expected = 20;
  EXPECT_EQ(expected, solution.kthSmallestProduct(nums1, nums2, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, KthSmallestProductOfTwoSortedArraysTest,
    ::testing::ValuesIn(
        KthSmallestProductOfTwoSortedArraysSolution().getStrategyNames()));

}  // namespace problem_2040
}  // namespace leetcode
