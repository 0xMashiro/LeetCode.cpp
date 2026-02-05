
#include "leetcode/problems/transformed-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3379 {

class TransformedArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TransformedArraySolution solution;
};

TEST_P(TransformedArrayTest, Example1) {
  vector<int> nums = {3, -2, 1, 1};
  vector<int> expected = {1, 1, 1, 3};
  vector<int> result = solution.constructTransformedArray(nums);
  EXPECT_EQ(expected, result);
}

TEST_P(TransformedArrayTest, Example2) {
  vector<int> nums = {-1, 4, -1};
  vector<int> expected = {-1, -1, 4};
  vector<int> result = solution.constructTransformedArray(nums);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TransformedArrayTest,
    ::testing::ValuesIn(TransformedArraySolution().getStrategyNames()));

}  // namespace problem_3379
}  // namespace leetcode
