
#include "leetcode/problems/absolute-difference-between-maximum-and-minimum-k-elements.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3774 {

class AbsoluteDifferenceBetweenMaximumAndMinimumKElementsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution solution;
};

TEST_P(AbsoluteDifferenceBetweenMaximumAndMinimumKElementsTest, Example1) {
  vector<int> nums = {5, 2, 2, 4};
  int k = 2;
  int expected = 5;
  EXPECT_EQ(expected, solution.absDifference(nums, k));
}

TEST_P(AbsoluteDifferenceBetweenMaximumAndMinimumKElementsTest, Example2) {
  vector<int> nums = {100};
  int k = 1;
  int expected = 0;
  EXPECT_EQ(expected, solution.absDifference(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AbsoluteDifferenceBetweenMaximumAndMinimumKElementsTest,
    ::testing::ValuesIn(AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution().getStrategyNames()));

}  // namespace problem_3774
}  // namespace leetcode
