#include "leetcode/problems/biggest-single-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_619 {

class BiggestSingleNumberTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BiggestSingleNumberSolution solution;
};

TEST_P(BiggestSingleNumberTest, Example1) {
  // 输入: [8, 8, 3, 3, 1, 4, 5, 6]
  // 单数字: 1, 4, 5, 6
  // 最大单数字: 6
  vector<int> nums = {8, 8, 3, 3, 1, 4, 5, 6};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 6);
}

TEST_P(BiggestSingleNumberTest, Example2) {
  // 输入: [8, 8, 7, 7, 3, 3, 3]
  // 没有单数字，返回 null
  vector<int> nums = {8, 8, 7, 7, 3, 3, 3};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_FALSE(result.has_value());
}

TEST_P(BiggestSingleNumberTest, EmptyInput) {
  // 空输入
  vector<int> nums = {};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_FALSE(result.has_value());
}

TEST_P(BiggestSingleNumberTest, SingleElement) {
  // 只有一个元素
  vector<int> nums = {42};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 42);
}

TEST_P(BiggestSingleNumberTest, AllDuplicates) {
  // 所有元素都重复
  vector<int> nums = {1, 1, 2, 2, 3, 3};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_FALSE(result.has_value());
}

TEST_P(BiggestSingleNumberTest, AllUnique) {
  // 所有元素都是唯一的
  vector<int> nums = {1, 2, 3, 4, 5};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 5);
}

TEST_P(BiggestSingleNumberTest, SingleAtBeginning) {
  // 单数字在开头
  vector<int> nums = {1, 2, 2, 3, 3};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 1);
}

TEST_P(BiggestSingleNumberTest, SingleAtEnd) {
  // 单数字在末尾
  vector<int> nums = {1, 1, 2, 2, 3};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 3);
}

TEST_P(BiggestSingleNumberTest, MultipleDuplicates) {
  // 多个数字重复多次
  vector<int> nums = {5, 5, 5, 3, 3, 7, 7, 7, 7, 9};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 9);
}

TEST_P(BiggestSingleNumberTest, NegativeNumbers) {
  // 包含负数
  vector<int> nums = {-1, -1, -5, -5, -3};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), -3);
}

TEST_P(BiggestSingleNumberTest, LargeNumbers) {
  // 大数值
  vector<int> nums = {1000000, 1000000, 999999};
  auto result = solution.biggestSingleNumber(nums);
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 999999);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BiggestSingleNumberTest,
    ::testing::ValuesIn(BiggestSingleNumberSolution().getStrategyNames()));

}  // namespace problem_619
}  // namespace leetcode
