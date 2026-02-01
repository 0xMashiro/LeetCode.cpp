#include "leetcode/problems/maximum-sum-of-subsequence-with-non-adjacent-elements.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3165 {

class MaximumSumOfSubsequenceWithNonAdjacentElementsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumSumOfSubsequenceWithNonAdjacentElementsSolution solution;
};

TEST_P(MaximumSumOfSubsequenceWithNonAdjacentElementsTest, Example1) {
  vector<int> nums = {3, 5, 9};
  vector<vector<int>> queries = {{1, -2}, {0, -3}};
  // 第一次查询后: [3, -2, 9]，最大不相邻子序列和 = 3 + 9 = 12
  // 第二次查询后: [-3, -2, 9]，最大不相邻子序列和 = 9
  // 总和 = 12 + 9 = 21
  EXPECT_EQ(solution.maximumSumSubsequence(nums, queries), 21);
}

TEST_P(MaximumSumOfSubsequenceWithNonAdjacentElementsTest, Example2) {
  vector<int> nums = {0, -1};
  vector<vector<int>> queries = {{0, -5}};
  // 查询后: [-5, -1]，最大不相邻子序列和 = 0 (选空子序列)
  EXPECT_EQ(solution.maximumSumSubsequence(nums, queries), 0);
}

// LeetCode 失败用例: WrongAnswerCase1
TEST_P(MaximumSumOfSubsequenceWithNonAdjacentElementsTest, WrongAnswerCase1) {
  // 输入: nums = [0,3,3,3,1,-2], queries = [[4,0],[1,0]]
  // 第一次查询后: [0,3,3,3,0,-2]，最大不相邻子序列和 = 3 + 3 = 6
  // 第二次查询后: [0,0,3,3,0,-2]，最大不相邻子序列和 = 3 + 3 = 6
  // 总和 = 6 + 3 = 9（第二次应该是 3，不是 6！）
  vector<int> nums = {0, 3, 3, 3, 1, -2};
  vector<vector<int>> queries = {{4, 0}, {1, 0}};
  EXPECT_EQ(solution.maximumSumSubsequence(nums, queries), 9);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumSumOfSubsequenceWithNonAdjacentElementsTest,
    ::testing::ValuesIn(MaximumSumOfSubsequenceWithNonAdjacentElementsSolution().getStrategyNames()));

}  // namespace problem_3165
}  // namespace leetcode
