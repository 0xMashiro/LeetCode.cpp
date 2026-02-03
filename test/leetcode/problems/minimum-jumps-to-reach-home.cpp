
#include "leetcode/problems/minimum-jumps-to-reach-home.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1654 {

class MinimumJumpsToReachHomeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumJumpsToReachHomeSolution solution;
};

TEST_P(MinimumJumpsToReachHomeTest, Example1) {
  vector<int> forbidden = {14, 4, 18, 1, 15};
  int a = 3, b = 15, x = 9;
  EXPECT_EQ(3, solution.minimumJumps(forbidden, a, b, x));
}

TEST_P(MinimumJumpsToReachHomeTest, Example2) {
  vector<int> forbidden = {8, 3, 16, 6, 12, 20};
  int a = 15, b = 13, x = 11;
  EXPECT_EQ(-1, solution.minimumJumps(forbidden, a, b, x));
}

TEST_P(MinimumJumpsToReachHomeTest, Example3) {
  vector<int> forbidden = {1, 6, 2, 14, 5, 17, 4};
  int a = 16, b = 9, x = 7;
  EXPECT_EQ(2, solution.minimumJumps(forbidden, a, b, x));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumJumpsToReachHomeTest,
    ::testing::ValuesIn(MinimumJumpsToReachHomeSolution().getStrategyNames()));

}  // namespace problem_1654
}  // namespace leetcode
