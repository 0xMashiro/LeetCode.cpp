
#include "leetcode/problems/distribute-candies.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_575 {

class DistributeCandiesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DistributeCandiesSolution solution;
};

TEST_P(DistributeCandiesTest, Example1) {
  vector<int> candyType = {1, 1, 2, 2, 3, 3};
  EXPECT_EQ(3, solution.distributeCandies(candyType));
}

TEST_P(DistributeCandiesTest, Example2) {
  vector<int> candyType = {1, 1, 2, 3};
  EXPECT_EQ(2, solution.distributeCandies(candyType));
}

TEST_P(DistributeCandiesTest, Example3) {
  vector<int> candyType = {6, 6, 6, 6};
  EXPECT_EQ(1, solution.distributeCandies(candyType));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DistributeCandiesTest,
    ::testing::ValuesIn(DistributeCandiesSolution().getStrategyNames()));

}  // namespace problem_575
}  // namespace leetcode
