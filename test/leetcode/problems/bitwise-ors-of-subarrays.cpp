#include "leetcode/problems/bitwise-ors-of-subarrays.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_898 {

class BitwiseOrsOfSubarraysTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BitwiseOrsOfSubarraysSolution solution;
};

TEST_P(BitwiseOrsOfSubarraysTest, Example1) {
  vector<int> arr = {0};
  int expected = 1;
  EXPECT_EQ(expected, solution.subarrayBitwiseORs(arr));
}

TEST_P(BitwiseOrsOfSubarraysTest, Example2) {
  vector<int> arr = {1, 1, 2};
  int expected = 3;
  EXPECT_EQ(expected, solution.subarrayBitwiseORs(arr));
}

TEST_P(BitwiseOrsOfSubarraysTest, Example3) {
  vector<int> arr = {1, 2, 4};
  int expected = 6;
  EXPECT_EQ(expected, solution.subarrayBitwiseORs(arr));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BitwiseOrsOfSubarraysTest,
    ::testing::ValuesIn(BitwiseOrsOfSubarraysSolution().getStrategyNames()));

}  // namespace problem_898
}  // namespace leetcode
