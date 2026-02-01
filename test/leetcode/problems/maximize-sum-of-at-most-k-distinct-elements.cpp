#include "leetcode/problems/maximize-sum-of-at-most-k-distinct-elements.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3684 {

class MaximizeSumOfAtMostKDistinctElementsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximizeSumOfAtMostKDistinctElementsSolution solution;
};

// 示例1: nums = [84,93,100,77,90], k = 3 → 输出 [100,93,90]
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, Example1) {
  vector<int> nums = {84, 93, 100, 77, 90};
  int k = 3;
  vector<int> expected = {100, 93, 90};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 示例2: nums = [84,93,100,77,93], k = 3 → 输出 [100,93,84]
// 93重复了，只能选一个
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, Example2) {
  vector<int> nums = {84, 93, 100, 77, 93};
  int k = 3;
  vector<int> expected = {100, 93, 84};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 示例3: nums = [1,1,1,2,2,2], k = 6 → 输出 [2,1]
// 只有两个不同的数
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, Example3) {
  vector<int> nums = {1, 1, 1, 2, 2, 2};
  int k = 6;
  vector<int> expected = {2, 1};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 边界测试: k = 1，只选最大的
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, KEqualsOne) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int k = 1;
  vector<int> expected = {5};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 边界测试: 所有元素相同
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, AllSameElements) {
  vector<int> nums = {5, 5, 5, 5, 5};
  int k = 3;
  vector<int> expected = {5};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 边界测试: 单元素
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, SingleElement) {
  vector<int> nums = {42};
  int k = 1;
  vector<int> expected = {42};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 边界测试: k大于不同元素的数量
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, KGreaterThanDistinct) {
  vector<int> nums = {1, 2, 3};
  int k = 10;
  vector<int> expected = {3, 2, 1};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 边界测试: 降序数组
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, DescendingArray) {
  vector<int> nums = {5, 4, 3, 2, 1};
  int k = 3;
  vector<int> expected = {5, 4, 3};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 边界测试: 升序数组
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, AscendingArray) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int k = 3;
  vector<int> expected = {5, 4, 3};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

// 大数测试
TEST_P(MaximizeSumOfAtMostKDistinctElementsTest, LargeNumbers) {
  vector<int> nums = {1000000000, 999999999, 1000000000};
  int k = 2;
  vector<int> expected = {1000000000, 999999999};
  vector<int> result = solution.maxKDistinct(nums, k);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximizeSumOfAtMostKDistinctElementsTest,
    ::testing::ValuesIn(MaximizeSumOfAtMostKDistinctElementsSolution().getStrategyNames()));

}  // namespace problem_3684
}  // namespace leetcode
