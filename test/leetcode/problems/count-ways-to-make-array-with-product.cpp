#include "leetcode/problems/count-ways-to-make-array-with-product.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1735 {

class CountWaysToMakeArrayWithProductTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountWaysToMakeArrayWithProductSolution solution;
};

TEST_P(CountWaysToMakeArrayWithProductTest, Example1) {
  vector<vector<int>> queries = {{2, 6}, {5, 1}, {73, 660}};
  vector<int> expected = {4, 1, 50734910};
  vector<int> result = solution.waysToFillArray(queries);
  EXPECT_EQ(expected, result);
}

TEST_P(CountWaysToMakeArrayWithProductTest, Example2) {
  vector<vector<int>> queries = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  vector<int> expected = {1, 2, 3, 10, 5};
  vector<int> result = solution.waysToFillArray(queries);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountWaysToMakeArrayWithProductTest,
    ::testing::ValuesIn(CountWaysToMakeArrayWithProductSolution().getStrategyNames()));

}  // namespace problem_1735
}  // namespace leetcode
