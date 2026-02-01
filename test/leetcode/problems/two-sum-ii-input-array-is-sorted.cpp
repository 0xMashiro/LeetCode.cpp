
#include "leetcode/problems/two-sum-ii-input-array-is-sorted.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_167 {

class TwoSumIiInputArrayIsSortedTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TwoSumIiInputArrayIsSortedSolution solution;
};

// 示例 1：numbers = [2,7,11,15], target = 9，输出 [1,2]
TEST_P(TwoSumIiInputArrayIsSortedTest, Example1) {
  vector<int> numbers = {2, 7, 11, 15};
  int target = 9;
  vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 示例 2：numbers = [2,3,4], target = 6，输出 [1,3]
TEST_P(TwoSumIiInputArrayIsSortedTest, Example2) {
  vector<int> numbers = {2, 3, 4};
  int target = 6;
  vector<int> expected = {1, 3};
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 示例 3：numbers = [-1,0], target = -1，输出 [1,2]
TEST_P(TwoSumIiInputArrayIsSortedTest, Example3) {
  vector<int> numbers = {-1, 0};
  int target = -1;
  vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 边界情况：最小数组 [1,2]，target = 3
TEST_P(TwoSumIiInputArrayIsSortedTest, MinimumArray) {
  vector<int> numbers = {1, 2};
  int target = 3;
  vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 边界情况：包含负数（只有一个解）
TEST_P(TwoSumIiInputArrayIsSortedTest, WithNegatives) {
  vector<int> numbers = {-5, -3, 0, 2, 4, 6};
  int target = 1;
  vector<int> expected = {1, 6};  // -5 + 6 = 1
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 边界情况：两个相同的数
TEST_P(TwoSumIiInputArrayIsSortedTest, SameNumbers) {
  vector<int> numbers = {1, 1, 2, 3, 4};
  int target = 2;
  vector<int> expected = {1, 2};
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 边界情况：较大的数
TEST_P(TwoSumIiInputArrayIsSortedTest, LargeNumbers) {
  vector<int> numbers = {100, 200, 300, 400, 500};
  int target = 900;
  vector<int> expected = {4, 5};  // 400 + 500 = 900
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 边界情况：target 为负数
TEST_P(TwoSumIiInputArrayIsSortedTest, NegativeTarget) {
  vector<int> numbers = {-10, -5, -2, 0, 3, 8};
  int target = -12;
  vector<int> expected = {1, 3};  // -10 + (-2) = -12
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

// 边界情况：target 为 0
TEST_P(TwoSumIiInputArrayIsSortedTest, ZeroTarget) {
  vector<int> numbers = {-3, -1, 0, 1, 2, 4};
  int target = 0;
  vector<int> expected = {2, 4};  // -1 + 1 = 0
  EXPECT_EQ(expected, solution.twoSum(numbers, target));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TwoSumIiInputArrayIsSortedTest,
    ::testing::ValuesIn(TwoSumIiInputArrayIsSortedSolution().getStrategyNames()));

}  // namespace problem_167
}  // namespace leetcode
