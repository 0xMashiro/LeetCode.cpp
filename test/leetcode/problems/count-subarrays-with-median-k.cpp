#include "leetcode/problems/count-subarrays-with-median-k.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2488 {

class CountSubarraysWithMedianKTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountSubarraysWithMedianKSolution solution;
};

TEST_P(CountSubarraysWithMedianKTest, Example1) {
  vector<int> nums = {3, 2, 1, 4, 5};
  int k = 4;
  int expected = 3;
  EXPECT_EQ(expected, solution.countSubarrays(nums, k));
}

TEST_P(CountSubarraysWithMedianKTest, Example2) {
  vector<int> nums = {2, 3, 1};
  int k = 3;
  int expected = 1;
  EXPECT_EQ(expected, solution.countSubarrays(nums, k));
}


// LeetCode 失败用例: WrongAnswerCase1
TEST_P(CountSubarraysWithMedianKTest, WrongAnswerCase1) {
  // 输入: nums = [2,5,1,4,3,6], k = 1
    // 期望: 3
    vector<int> nums = {2, 5, 1, 4, 3, 6};
    int k = 1;
    int expected = 3;
    EXPECT_EQ(expected, solution.countSubarrays(nums, k));
}
INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountSubarraysWithMedianKTest,
    ::testing::ValuesIn(CountSubarraysWithMedianKSolution().getStrategyNames()));

}  // namespace problem_2488
}  // namespace leetcode