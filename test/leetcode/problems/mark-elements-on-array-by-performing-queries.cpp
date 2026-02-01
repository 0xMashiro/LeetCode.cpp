#include "leetcode/problems/mark-elements-on-array-by-performing-queries.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3080 {

class MarkElementsOnArrayByPerformingQueriesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MarkElementsOnArrayByPerformingQueriesSolution solution;
};

TEST_P(MarkElementsOnArrayByPerformingQueriesTest, Example1) {
  vector<int> nums = {1, 2, 2, 1, 2, 3, 1};
  vector<vector<int>> queries = {{1, 2}, {3, 3}, {4, 2}};
  vector<long long> expected = {8, 3, 0};
  EXPECT_EQ(expected, solution.unmarkedSumArray(nums, queries));
}

TEST_P(MarkElementsOnArrayByPerformingQueriesTest, Example2) {
  vector<int> nums = {1, 4, 2, 3};
  vector<vector<int>> queries = {{0, 1}};
  vector<long long> expected = {7};
  EXPECT_EQ(expected, solution.unmarkedSumArray(nums, queries));
}

TEST_P(MarkElementsOnArrayByPerformingQueriesTest, SingleElement) {
  vector<int> nums = {5};
  vector<vector<int>> queries = {{0, 0}};
  vector<long long> expected = {0};  // 标记唯一元素后，未标记和为0
  EXPECT_EQ(expected, solution.unmarkedSumArray(nums, queries));
}

TEST_P(MarkElementsOnArrayByPerformingQueriesTest, AllSameValue) {
  vector<int> nums = {2, 2, 2, 2};
  vector<vector<int>> queries = {{0, 2}};
  // 标记 index 0，再标记两个最小的（索引 1 和 2）
  // 剩余未标记：index 3，值为 2
  vector<long long> expected = {2};
  EXPECT_EQ(expected, solution.unmarkedSumArray(nums, queries));
}

TEST_P(MarkElementsOnArrayByPerformingQueriesTest, SkipAlreadyMarked) {
  vector<int> nums = {1, 2, 3};
  // 第一个查询标记 index 0，再标记 k=1 个最小（index 1）
  // 第二个查询尝试标记 index 0（已标记），跳过，再标记 k=1 个最小（index 2）
  vector<vector<int>> queries = {{0, 1}, {0, 1}};
  vector<long long> expected = {3, 0};  // 第一次后剩3，第二次后剩0
  EXPECT_EQ(expected, solution.unmarkedSumArray(nums, queries));
}

TEST_P(MarkElementsOnArrayByPerformingQueriesTest, LargeK) {
  vector<int> nums = {1, 2, 3};
  // k=5 超过未标记元素数量，应该标记所有剩余未标记元素
  vector<vector<int>> queries = {{0, 5}};
  // 标记 index 0（值1），再尝试标记5个，但只有2个未标记（2和3），全部标记
  // 未标记和为0
  vector<long long> expected = {0};
  EXPECT_EQ(expected, solution.unmarkedSumArray(nums, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MarkElementsOnArrayByPerformingQueriesTest,
    ::testing::ValuesIn(MarkElementsOnArrayByPerformingQueriesSolution().getStrategyNames()));

}  // namespace problem_3080
}  // namespace leetcode
