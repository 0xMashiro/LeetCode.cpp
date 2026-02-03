#include "leetcode/problems/count-of-range-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_327 {

class CountOfRangeSumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountOfRangeSumSolution solution;
};

TEST_P(CountOfRangeSumTest, Example1) {
  vector<int> nums = {-2, 5, -1};
  int lower = -2;
  int upper = 2;
  int expected = 3;
  EXPECT_EQ(expected, solution.countRangeSum(nums, lower, upper));
}

TEST_P(CountOfRangeSumTest, Example2) {
  vector<int> nums = {0};
  int lower = 0;
  int upper = 0;
  int expected = 1;
  EXPECT_EQ(expected, solution.countRangeSum(nums, lower, upper));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountOfRangeSumTest,
    ::testing::ValuesIn(CountOfRangeSumSolution().getStrategyNames()));

}  // namespace problem_327
}  // namespace leetcode
