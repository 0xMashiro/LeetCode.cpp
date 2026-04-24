#include "leetcode/problems/profitable-schemes.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_879 {

class ProfitableSchemesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ProfitableSchemesSolution solution;
};

TEST_P(ProfitableSchemesTest, Example1) {
  int n = 5;
  int minProfit = 3;
  vector<int> group = {2, 2};
  vector<int> profit = {2, 3};
  int expected = 2;
  EXPECT_EQ(expected, solution.profitableSchemes(n, minProfit, group, profit));
}

TEST_P(ProfitableSchemesTest, Example2) {
  int n = 10;
  int minProfit = 5;
  vector<int> group = {2, 3, 5};
  vector<int> profit = {6, 7, 8};
  int expected = 7;
  EXPECT_EQ(expected, solution.profitableSchemes(n, minProfit, group, profit));
}

TEST_P(ProfitableSchemesTest, Example3) {
  int n = 1;
  int minProfit = 1;
  vector<int> group = {2, 2, 2};
  vector<int> profit = {2, 3, 5};
  int expected = 0;
  EXPECT_EQ(expected, solution.profitableSchemes(n, minProfit, group, profit));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ProfitableSchemesTest,
    ::testing::ValuesIn(ProfitableSchemesSolution().getStrategyNames()));

}  // namespace problem_879
}  // namespace leetcode
