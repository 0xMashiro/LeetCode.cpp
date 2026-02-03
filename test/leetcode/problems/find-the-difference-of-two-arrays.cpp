
#include "leetcode/problems/find-the-difference-of-two-arrays.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2215 {

class FindTheDifferenceOfTwoArraysTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindTheDifferenceOfTwoArraysSolution solution;
};

TEST_P(FindTheDifferenceOfTwoArraysTest, Example1) {
  vector<int> nums1 = {1, 2, 3};
  vector<int> nums2 = {2, 4, 6};
  vector<vector<int>> result = solution.findDifference(nums1, nums2);
  
  // 对结果排序以便比较（题目允许任意顺序）
  sort(result[0].begin(), result[0].end());
  sort(result[1].begin(), result[1].end());
  
  vector<int> expected0 = {1, 3};
  vector<int> expected1 = {4, 6};
  
  EXPECT_EQ(expected0, result[0]);
  EXPECT_EQ(expected1, result[1]);
}

TEST_P(FindTheDifferenceOfTwoArraysTest, Example2) {
  vector<int> nums1 = {1, 2, 3, 3};
  vector<int> nums2 = {1, 1, 2, 2};
  vector<vector<int>> result = solution.findDifference(nums1, nums2);
  
  // 对结果排序以便比较
  sort(result[0].begin(), result[0].end());
  sort(result[1].begin(), result[1].end());
  
  vector<int> expected0 = {3};
  vector<int> expected1 = {};
  
  EXPECT_EQ(expected0, result[0]);
  EXPECT_EQ(expected1, result[1]);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindTheDifferenceOfTwoArraysTest,
    ::testing::ValuesIn(FindTheDifferenceOfTwoArraysSolution().getStrategyNames()));

}  // namespace problem_2215
}  // namespace leetcode
