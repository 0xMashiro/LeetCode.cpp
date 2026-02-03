#include "leetcode/problems/next-greater-element-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_503 {

class NextGreaterElementIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NextGreaterElementIiSolution solution;
};

TEST_P(NextGreaterElementIiTest, Example1) {
  vector<int> nums = {1, 2, 1};
  vector<int> expected = {2, -1, 2};
  vector<int> result = solution.nextGreaterElements(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(NextGreaterElementIiTest, Example2) {
  vector<int> nums = {1, 2, 3, 4, 3};
  vector<int> expected = {2, 3, 4, -1, 4};
  vector<int> result = solution.nextGreaterElements(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(NextGreaterElementIiTest, SingleElement) {
  // 边界：单元素数组
  vector<int> nums = {5};
  vector<int> expected = {-1};
  vector<int> result = solution.nextGreaterElements(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(NextGreaterElementIiTest, AllSame) {
  // 边界：所有元素相同
  vector<int> nums = {3, 3, 3};
  vector<int> expected = {-1, -1, -1};
  vector<int> result = solution.nextGreaterElements(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(NextGreaterElementIiTest, Decreasing) {
  // 边界：递减序列
  vector<int> nums = {3, 2, 1};
  vector<int> expected = {-1, 3, 3};
  vector<int> result = solution.nextGreaterElements(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(NextGreaterElementIiTest, Increasing) {
  // 边界：递增序列
  vector<int> nums = {1, 2, 3};
  vector<int> expected = {2, 3, -1};
  vector<int> result = solution.nextGreaterElements(nums);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NextGreaterElementIiTest,
    ::testing::ValuesIn(NextGreaterElementIiSolution().getStrategyNames()));

}  // namespace problem_503
}  // namespace leetcode
