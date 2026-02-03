#include "leetcode/problems/neither-minimum-nor-maximum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2733 {

class NeitherMinimumNorMaximumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NeitherMinimumNorMaximumSolution solution;
};

TEST_P(NeitherMinimumNorMaximumTest, Example1) {
  vector<int> nums = {3, 2, 1, 4};
  int result = solution.findNonMinOrMax(nums);
  // 结果应该是2或3（既不是1也不是4）
  EXPECT_TRUE(result == 2 || result == 3);
}

TEST_P(NeitherMinimumNorMaximumTest, Example2) {
  vector<int> nums = {1, 2};
  int expected = -1;
  EXPECT_EQ(expected, solution.findNonMinOrMax(nums));
}

TEST_P(NeitherMinimumNorMaximumTest, Example3) {
  vector<int> nums = {2, 1, 3};
  int expected = 2;
  EXPECT_EQ(expected, solution.findNonMinOrMax(nums));
}

TEST_P(NeitherMinimumNorMaximumTest, SingleElement) {
  vector<int> nums = {5};
  int expected = -1;
  EXPECT_EQ(expected, solution.findNonMinOrMax(nums));
}

TEST_P(NeitherMinimumNorMaximumTest, ThreeElementsUnordered) {
  vector<int> nums = {5, 1, 3};
  int expected = 3;
  EXPECT_EQ(expected, solution.findNonMinOrMax(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NeitherMinimumNorMaximumTest,
    ::testing::ValuesIn(NeitherMinimumNorMaximumSolution().getStrategyNames()));

}  // namespace problem_2733
}  // namespace leetcode
