#include "leetcode/problems/create-maximum-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_321 {

class CreateMaximumNumberTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CreateMaximumNumberSolution solution;
};

TEST_P(CreateMaximumNumberTest, Example1) {
  vector<int> nums1 = {3, 4, 6, 5};
  vector<int> nums2 = {9, 1, 2, 5, 8, 3};
  int k = 5;
  vector<int> expected = {9, 8, 6, 5, 3};
  EXPECT_EQ(expected, solution.maxNumber(nums1, nums2, k));
}

TEST_P(CreateMaximumNumberTest, Example2) {
  vector<int> nums1 = {6, 7};
  vector<int> nums2 = {6, 0, 4};
  int k = 5;
  vector<int> expected = {6, 7, 6, 0, 4};
  EXPECT_EQ(expected, solution.maxNumber(nums1, nums2, k));
}

TEST_P(CreateMaximumNumberTest, Example3) {
  vector<int> nums1 = {3, 9};
  vector<int> nums2 = {8, 9};
  int k = 3;
  vector<int> expected = {9, 8, 9};
  EXPECT_EQ(expected, solution.maxNumber(nums1, nums2, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CreateMaximumNumberTest,
    ::testing::ValuesIn(CreateMaximumNumberSolution().getStrategyNames()));

}  // namespace problem_321
}  // namespace leetcode
