#include "leetcode/problems/minimum-cost-to-make-all-characters-equal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2712 {

class MinimumCostToMakeAllCharactersEqualTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostToMakeAllCharactersEqualSolution solution;
};

TEST_P(MinimumCostToMakeAllCharactersEqualTest, Example1) {
  string s = "0011";
  long long expected = 2;
  EXPECT_EQ(expected, solution.minimumCost(s));
}

TEST_P(MinimumCostToMakeAllCharactersEqualTest, Example2) {
  string s = "010101";
  long long expected = 9;
  EXPECT_EQ(expected, solution.minimumCost(s));
}

TEST_P(MinimumCostToMakeAllCharactersEqualTest, SingleCharacter) {
  string s = "0";
  long long expected = 0;
  EXPECT_EQ(expected, solution.minimumCost(s));
  
  string s2 = "1";
  EXPECT_EQ(expected, solution.minimumCost(s2));
}

TEST_P(MinimumCostToMakeAllCharactersEqualTest, AllSame) {
  string s = "00000";
  long long expected = 0;
  EXPECT_EQ(expected, solution.minimumCost(s));
  
  string s2 = "11111";
  EXPECT_EQ(expected, solution.minimumCost(s2));
}

TEST_P(MinimumCostToMakeAllCharactersEqualTest, Alternating) {
  string s = "01";
  long long expected = 1;  // min(1, 1) = 1
  EXPECT_EQ(expected, solution.minimumCost(s));
  
  string s2 = "10";
  EXPECT_EQ(expected, solution.minimumCost(s2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostToMakeAllCharactersEqualTest,
    ::testing::ValuesIn(MinimumCostToMakeAllCharactersEqualSolution().getStrategyNames()));

}  // namespace problem_2712
}  // namespace leetcode
