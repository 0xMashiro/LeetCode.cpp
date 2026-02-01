#include "leetcode/problems/xor-after-range-multiplication-queries-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3653 {

class XorAfterRangeMultiplicationQueriesITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  XorAfterRangeMultiplicationQueriesISolution solution;
};

TEST_P(XorAfterRangeMultiplicationQueriesITest, Example1) {
  // 输入: nums = [1,1,1], queries = [[0,2,1,4]]
  // 输出: 4
  vector<int> nums = {1, 1, 1};
  vector<vector<int>> queries = {{0, 2, 1, 4}};
  EXPECT_EQ(4, solution.xorAfterQueries(nums, queries));
}

TEST_P(XorAfterRangeMultiplicationQueriesITest, Example2) {
  // 输入: nums = [2,3,1,5,4], queries = [[1,4,2,3],[0,2,1,2]]
  // 输出: 31
  vector<int> nums = {2, 3, 1, 5, 4};
  vector<vector<int>> queries = {{1, 4, 2, 3}, {0, 2, 1, 2}};
  EXPECT_EQ(31, solution.xorAfterQueries(nums, queries));
}

TEST_P(XorAfterRangeMultiplicationQueriesITest, SingleElement) {
  // 边界：单元素数组
  vector<int> nums = {5};
  vector<vector<int>> queries = {{0, 0, 1, 2}};
  // 5 * 2 = 10, 10 % MOD = 10
  EXPECT_EQ(10, solution.xorAfterQueries(nums, queries));
}

TEST_P(XorAfterRangeMultiplicationQueriesITest, NoQuery) {
  // 边界：空查询
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> queries = {};
  // 1 ^ 2 ^ 3 = 0
  EXPECT_EQ(0, solution.xorAfterQueries(nums, queries));
}

TEST_P(XorAfterRangeMultiplicationQueriesITest, MultipleQueriesSamePosition) {
  // 同一位置被多次更新
  vector<int> nums = {1, 2};
  vector<vector<int>> queries = {{0, 1, 1, 2}, {0, 0, 1, 3}};
  // 第一次: [2, 4]
  // 第二次: [6, 4]
  // 6 ^ 4 = 2
  EXPECT_EQ(2, solution.xorAfterQueries(nums, queries));
}

TEST_P(XorAfterRangeMultiplicationQueriesITest, LargeStep) {
  // 大步长 k
  vector<int> nums = {1, 1, 1, 1, 1};
  vector<vector<int>> queries = {{0, 4, 2, 3}};
  // 更新位置 0, 2, 4: [3, 1, 3, 1, 3]
  // 3 ^ 1 ^ 3 ^ 1 ^ 3 = 3
  EXPECT_EQ(3, solution.xorAfterQueries(nums, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, XorAfterRangeMultiplicationQueriesITest,
    ::testing::ValuesIn(XorAfterRangeMultiplicationQueriesISolution().getStrategyNames()));

}  // namespace problem_3653
}  // namespace leetcode
