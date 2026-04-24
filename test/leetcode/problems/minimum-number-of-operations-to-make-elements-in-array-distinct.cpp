#include "leetcode/problems/minimum-number-of-operations-to-make-elements-in-array-distinct.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3396 {

class MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution solution;
};

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, Example1) {
  vector<int> nums = {1, 2, 3, 4, 2, 3, 3, 5, 7};
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, Example2) {
  vector<int> nums = {4, 5, 6, 4, 4};
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, Example3) {
  vector<int> nums = {6, 7, 8, 9};
  int expected = 0;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, AllUnique) {
  vector<int> nums = {1, 2, 3};
  int expected = 0;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, SingleElement) {
  vector<int> nums = {5};
  int expected = 0;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, AllSame) {
  vector<int> nums = {1, 1, 1, 1, 1};
  // First duplicate from right is at index 3, need ceil(4/3) = 2 operations
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

TEST_P(MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest, DuplicateAtStart) {
  vector<int> nums = {1, 1};
  int expected = 1;
  EXPECT_EQ(expected, solution.minimumOperations(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfOperationsToMakeElementsInArrayDistinctTest,
    ::testing::ValuesIn(MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution().getStrategyNames()));

}  // namespace problem_3396
}  // namespace leetcode
