#include "leetcode/problems/minimum-operations-to-make-elements-within-k-subarrays-equal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3505 {

class MinimumOperationsToMakeElementsWithinKSubarraysEqualTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution solution;
};

TEST_P(MinimumOperationsToMakeElementsWithinKSubarraysEqualTest, Example1) {
  vector<int> nums = {5, -2, 1, 3, 7, 3, 6, 4, -1};
  int x = 3;
  int k = 2;
  long long expected = 8;
  EXPECT_EQ(expected, solution.minOperations(nums, x, k));
}

TEST_P(MinimumOperationsToMakeElementsWithinKSubarraysEqualTest, Example2) {
  vector<int> nums = {9, -2, -2, -2, 1, 5};
  int x = 2;
  int k = 2;
  long long expected = 3;
  EXPECT_EQ(expected, solution.minOperations(nums, x, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumOperationsToMakeElementsWithinKSubarraysEqualTest,
    ::testing::ValuesIn(MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution().getStrategyNames()));

}  // namespace problem_3505
}  // namespace leetcode
