
#include "leetcode/problems/find-the-power-of-k-size-subarrays-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3254 {

class FindThePowerOfKSizeSubarraysITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindThePowerOfKSizeSubarraysISolution solution;
};

TEST_P(FindThePowerOfKSizeSubarraysITest, Example1) {
  vector<int> nums = {1, 2, 3, 4, 3, 2, 5};
  int k = 3;
  vector<int> expected = {3, 4, -1, -1, -1};
  EXPECT_EQ(expected, solution.resultsArray(nums, k));
}

TEST_P(FindThePowerOfKSizeSubarraysITest, Example2) {
  vector<int> nums = {2, 2, 2, 2, 2};
  int k = 4;
  vector<int> expected = {-1, -1};
  EXPECT_EQ(expected, solution.resultsArray(nums, k));
}

TEST_P(FindThePowerOfKSizeSubarraysITest, Example3) {
  vector<int> nums = {3, 2, 3, 2, 3, 2};
  int k = 2;
  vector<int> expected = {-1, 3, -1, 3, -1};
  EXPECT_EQ(expected, solution.resultsArray(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindThePowerOfKSizeSubarraysITest,
    ::testing::ValuesIn(FindThePowerOfKSizeSubarraysISolution().getStrategyNames()));

}  // namespace problem_3254
}  // namespace leetcode
