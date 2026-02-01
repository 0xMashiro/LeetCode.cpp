
#include "leetcode/problems/permutations-iv.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3470 {

class PermutationsIvTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PermutationsIvSolution solution;
};

TEST_P(PermutationsIvTest, Example1) {
  // n = 4, k = 6, expected = [3,4,1,2]
  int n = 4;
  long long k = 6;
  vector<int> expected = {3, 4, 1, 2};
  EXPECT_EQ(expected, solution.permute(n, k));
}

TEST_P(PermutationsIvTest, Example2) {
  // n = 3, k = 2, expected = [3,2,1]
  int n = 3;
  long long k = 2;
  vector<int> expected = {3, 2, 1};
  EXPECT_EQ(expected, solution.permute(n, k));
}

TEST_P(PermutationsIvTest, Example3) {
  // n = 2, k = 3, expected = [] (out of range)
  int n = 2;
  long long k = 3;
  vector<int> expected = {};
  EXPECT_EQ(expected, solution.permute(n, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PermutationsIvTest,
    ::testing::ValuesIn(PermutationsIvSolution().getStrategyNames()));

}  // namespace problem_3470
}  // namespace leetcode
