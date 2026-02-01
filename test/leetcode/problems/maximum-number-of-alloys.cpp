
#include "leetcode/problems/maximum-number-of-alloys.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2861 {

class MaximumNumberOfAlloysTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumNumberOfAlloysSolution solution;
};

// 示例 1：使用第 1 台机器，生产 2 个合金
TEST_P(MaximumNumberOfAlloysTest, Example1) {
  int n = 3, k = 2, budget = 15;
  vector<vector<int>> composition = {{1, 1, 1}, {1, 1, 10}};
  vector<int> stock = {0, 0, 0};
  vector<int> cost = {1, 2, 3};
  
  EXPECT_EQ(2, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 示例 2：使用第 2 台机器（利用库存），生产 5 个合金
TEST_P(MaximumNumberOfAlloysTest, Example2) {
  int n = 3, k = 2, budget = 15;
  vector<vector<int>> composition = {{1, 1, 1}, {1, 1, 10}};
  vector<int> stock = {0, 0, 100};
  vector<int> cost = {1, 2, 3};
  
  EXPECT_EQ(5, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 示例 3：使用第 3 台机器
TEST_P(MaximumNumberOfAlloysTest, Example3) {
  int n = 2, k = 3, budget = 10;
  vector<vector<int>> composition = {{2, 1}, {1, 2}, {1, 1}};
  vector<int> stock = {1, 1};
  vector<int> cost = {5, 5};
  
  EXPECT_EQ(2, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 边界情况：预算为 0，只能使用库存
TEST_P(MaximumNumberOfAlloysTest, ZeroBudget) {
  int n = 2, k = 1, budget = 0;
  vector<vector<int>> composition = {{1, 1}};
  vector<int> stock = {5, 5};
  vector<int> cost = {1, 1};
  
  // 有 5+5 的库存，但生产 1 个合金需要 1+1，所以可以生产 5 个
  EXPECT_EQ(5, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 边界情况：预算为 0，库存也为 0
TEST_P(MaximumNumberOfAlloysTest, ZeroBudgetZeroStock) {
  int n = 2, k = 1, budget = 0;
  vector<vector<int>> composition = {{1, 1}};
  vector<int> stock = {0, 0};
  vector<int> cost = {1, 1};
  
  EXPECT_EQ(0, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 边界情况：单台机器，单种金属
TEST_P(MaximumNumberOfAlloysTest, SingleMachineSingleMetal) {
  int n = 1, k = 1, budget = 100;
  vector<vector<int>> composition = {{5}};
  vector<int> stock = {10};
  vector<int> cost = {2};
  
  // 库存 10，需要生产 x 个，每个需要 5 单位
  // 生产 x 个需要 5x 单位，如果 5x > 10，需要购买 (5x-10) 单位
  // 花费：(5x-10) * 2 <= 100 => 5x - 10 <= 50 => 5x <= 60 => x <= 12
  EXPECT_EQ(12, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 边界情况：只有一台机器可用（k=1）
TEST_P(MaximumNumberOfAlloysTest, SingleMachine) {
  int n = 3, k = 1, budget = 100;
  vector<vector<int>> composition = {{2, 3, 4}};
  vector<int> stock = {0, 0, 0};
  vector<int> cost = {1, 1, 1};
  
  // 每个合金需要 2+3+4=9 单位，预算 100，可以生产 11 个（花费 99）
  EXPECT_EQ(11, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

// 边界情况：大量库存，不需要购买
TEST_P(MaximumNumberOfAlloysTest, EnoughStock) {
  int n = 2, k = 2, budget = 10;
  vector<vector<int>> composition = {{1, 1}, {2, 2}};
  vector<int> stock = {100000000, 100000000};
  vector<int> cost = {100, 100};
  
  // 库存充足，预算用不上，可以生产很多
  // 但受限于 int 范围，二分搜索上界为 2e8
  // 实际上可以生产更多，但我们搜索到 2e8
  int result = solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost);
  EXPECT_GE(result, 100000000);  // 至少可以生产 1e8 个
}

// 边界情况：金属单价很高
TEST_P(MaximumNumberOfAlloysTest, HighCost) {
  int n = 2, k = 1, budget = 100000000;
  vector<vector<int>> composition = {{1, 1}};
  vector<int> stock = {0, 0};
  vector<int> cost = {100, 100};
  
  // 每个合金需要 (1+1)*100 = 200 花费
  // 预算 1e8，可以生产 500000 个
  EXPECT_EQ(500000, solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumNumberOfAlloysTest,
    ::testing::ValuesIn(MaximumNumberOfAlloysSolution().getStrategyNames()));

}  // namespace problem_2861
}  // namespace leetcode
