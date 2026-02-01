#include "leetcode/problems/most-beautiful-item-for-each-query.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2070 {

class MostBeautifulItemForEachQueryTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MostBeautifulItemForEachQuerySolution solution;
};

// 示例 1
TEST_P(MostBeautifulItemForEachQueryTest, Example1) {
  vector<vector<int>> items = {{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}};
  vector<int> queries = {1, 2, 3, 4, 5, 6};
  vector<int> expected = {2, 4, 5, 5, 6, 6};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 示例 2：多个相同价格的商品
TEST_P(MostBeautifulItemForEachQueryTest, Example2) {
  vector<vector<int>> items = {{1, 2}, {1, 2}, {1, 3}, {1, 4}};
  vector<int> queries = {1};
  vector<int> expected = {4};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 示例 3：没有符合条件的商品
TEST_P(MostBeautifulItemForEachQueryTest, Example3) {
  vector<vector<int>> items = {{10, 1000}};
  vector<int> queries = {5};
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：空查询
TEST_P(MostBeautifulItemForEachQueryTest, EmptyQueries) {
  vector<vector<int>> items = {{1, 2}, {3, 4}};
  vector<int> queries = {};
  vector<int> expected = {};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：单个商品，单个查询，恰好匹配
TEST_P(MostBeautifulItemForEachQueryTest, SingleItemExactMatch) {
  vector<vector<int>> items = {{5, 10}};
  vector<int> queries = {5};
  vector<int> expected = {10};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：单个商品，查询值小于价格
TEST_P(MostBeautifulItemForEachQueryTest, SingleItemNoMatch) {
  vector<vector<int>> items = {{5, 10}};
  vector<int> queries = {4};
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：查询值非常大
TEST_P(MostBeautifulItemForEachQueryTest, LargeQuery) {
  vector<vector<int>> items = {{1, 1}, {2, 2}, {3, 3}};
  vector<int> queries = {1000000000};
  vector<int> expected = {3};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：价格递增，美丽值递减
TEST_P(MostBeautifulItemForEachQueryTest, IncreasingPriceDecreasingBeauty) {
  vector<vector<int>> items = {{1, 100}, {2, 50}, {3, 10}};
  vector<int> queries = {1, 2, 3};
  vector<int> expected = {100, 100, 100};  // 前缀最大值
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：价格和美丽值都递增
TEST_P(MostBeautifulItemForEachQueryTest, BothIncreasing) {
  vector<vector<int>> items = {{1, 1}, {2, 2}, {3, 3}};
  vector<int> queries = {1, 2, 3};
  vector<int> expected = {1, 2, 3};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：所有查询都小于最小价格
TEST_P(MostBeautifulItemForEachQueryTest, AllQueriesTooSmall) {
  vector<vector<int>> items = {{10, 5}, {20, 10}, {30, 15}};
  vector<int> queries = {1, 2, 5, 9};
  vector<int> expected = {0, 0, 0, 0};
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：所有查询都大于等于最大价格
TEST_P(MostBeautifulItemForEachQueryTest, AllQueriesLargeEnough) {
  vector<vector<int>> items = {{1, 5}, {2, 10}, {3, 3}};
  vector<int> queries = {3, 10, 100};
  vector<int> expected = {10, 10, 10};  // 所有商品都可选，最大美丽值是 10
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

// 边界：大量相同价格的商品
TEST_P(MostBeautifulItemForEachQueryTest, ManySamePrice) {
  vector<vector<int>> items;
  for (int i = 1; i <= 100; ++i) {
    items.push_back({5, i});  // 相同价格，不同美丽值
  }
  vector<int> queries = {5};
  vector<int> expected = {100};  // 最大美丽值
  EXPECT_EQ(expected, solution.maximumBeauty(items, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MostBeautifulItemForEachQueryTest,
    ::testing::ValuesIn(MostBeautifulItemForEachQuerySolution().getStrategyNames()));

}  // namespace problem_2070
}  // namespace leetcode
