#include "leetcode/problems/subarrays-with-k-different-integers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_992 {

class SubarraysWithKDifferentIntegersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SubarraysWithKDifferentIntegersSolution solution;
};

// 示例 1：nums = [1,2,1,2,3], k = 2，输出 7
TEST_P(SubarraysWithKDifferentIntegersTest, Example1) {
  vector<int> nums = {1, 2, 1, 2, 3};
  int k = 2;
  int expected = 7;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

// 示例 2：nums = [1,2,1,3,4], k = 3，输出 3
TEST_P(SubarraysWithKDifferentIntegersTest, Example2) {
  vector<int> nums = {1, 2, 1, 3, 4};
  int k = 3;
  int expected = 3;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

// 边界测试：k = 1，所有子数组都只有 1 个不同整数
TEST_P(SubarraysWithKDifferentIntegersTest, KEquals1) {
  vector<int> nums = {1, 1, 1, 1};
  int k = 1;
  // 子数组：[1], [1], [1], [1], [1,1], [1,1], [1,1], [1,1,1], [1,1,1], [1,1,1,1] = 10
  int expected = 10;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

// 边界测试：k 等于数组中不同数字的个数
TEST_P(SubarraysWithKDifferentIntegersTest, KEqualsDistinctCount) {
  vector<int> nums = {1, 2, 3, 4};
  int k = 4;
  // 只有整个数组满足：[1,2,3,4]
  int expected = 1;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

// 边界测试：单元素数组
TEST_P(SubarraysWithKDifferentIntegersTest, SingleElement) {
  vector<int> nums = {1};
  int k = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

// 边界测试：k 大于不同数字的个数，结果应为 0
TEST_P(SubarraysWithKDifferentIntegersTest, KGreaterThanDistinctCount) {
  vector<int> nums = {1, 2, 1, 2};
  int k = 3;
  int expected = 0;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

// 边界测试：两个不同数字交替
TEST_P(SubarraysWithKDifferentIntegersTest, TwoDistinctAlternating) {
  vector<int> nums = {1, 2, 1, 2, 1};
  int k = 2;
  // 所有长度 >= 2 的子数组都包含 2 个不同整数
  // 长度为 2 的：[1,2], [2,1], [1,2], [2,1] = 4
  // 长度为 3 的：[1,2,1], [2,1,2], [1,2,1] = 3
  // 长度为 4 的：[1,2,1,2], [2,1,2,1] = 2
  // 长度为 5 的：[1,2,1,2,1] = 1
  // 总计：4 + 3 + 2 + 1 = 10
  int expected = 10;
  EXPECT_EQ(expected, solution.subarraysWithKDistinct(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SubarraysWithKDifferentIntegersTest,
    ::testing::ValuesIn(SubarraysWithKDifferentIntegersSolution().getStrategyNames()));

}  // namespace problem_992
}  // namespace leetcode
