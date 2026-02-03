#include "leetcode/problems/replace-elements-in-an-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2295 {

class ReplaceElementsInAnArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ReplaceElementsInAnArraySolution solution;
};

TEST_P(ReplaceElementsInAnArrayTest, Example1) {
  vector<int> nums = {1, 2, 4, 6};
  vector<vector<int>> operations = {{1, 3}, {4, 7}, {6, 1}};
  vector<int> expected = {3, 2, 7, 1};
  EXPECT_EQ(expected, solution.arrayChange(nums, operations));
}

TEST_P(ReplaceElementsInAnArrayTest, Example2) {
  vector<int> nums = {1, 2};
  vector<vector<int>> operations = {{1, 3}, {2, 1}, {3, 2}};
  vector<int> expected = {2, 1};
  EXPECT_EQ(expected, solution.arrayChange(nums, operations));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ReplaceElementsInAnArrayTest,
    ::testing::ValuesIn(ReplaceElementsInAnArraySolution().getStrategyNames()));

}  // namespace problem_2295
}  // namespace leetcode
