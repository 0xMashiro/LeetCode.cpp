#include "leetcode/problems/divide-an-array-into-subarrays-with-minimum-cost-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3010 {

class DivideAnArrayIntoSubarraysWithMinimumCostITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DivideAnArrayIntoSubarraysWithMinimumCostISolution solution;
};

TEST_P(DivideAnArrayIntoSubarraysWithMinimumCostITest, Example1) {
  vector<int> nums = {1, 2, 3, 12};
  int expected = 6;
  EXPECT_EQ(expected, solution.minimumCost(nums));
}

TEST_P(DivideAnArrayIntoSubarraysWithMinimumCostITest, Example2) {
  vector<int> nums = {5, 4, 3};
  int expected = 12;
  EXPECT_EQ(expected, solution.minimumCost(nums));
}

TEST_P(DivideAnArrayIntoSubarraysWithMinimumCostITest, Example3) {
  vector<int> nums = {10, 3, 1, 1};
  int expected = 12;
  EXPECT_EQ(expected, solution.minimumCost(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DivideAnArrayIntoSubarraysWithMinimumCostITest,
    ::testing::ValuesIn(DivideAnArrayIntoSubarraysWithMinimumCostISolution().getStrategyNames()));

}  // namespace problem_3010
}  // namespace leetcode
