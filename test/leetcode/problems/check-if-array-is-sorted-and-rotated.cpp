#include "leetcode/problems/check-if-array-is-sorted-and-rotated.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1752 {

class CheckIfArrayIsSortedAndRotatedTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }
  CheckIfArrayIsSortedAndRotatedSolution solution;
};

TEST_P(CheckIfArrayIsSortedAndRotatedTest, Example1) {
  vector<int> nums = {3, 4, 5, 1, 2};
  EXPECT_TRUE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, Example2) {
  vector<int> nums = {2, 1, 3, 4};
  EXPECT_FALSE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, Example3) {
  vector<int> nums = {1, 2, 3};
  EXPECT_TRUE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, SelfAuthoredSingleElement) {
  vector<int> nums = {5};
  EXPECT_TRUE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, SelfAuthoredTwoElementsSorted) {
  vector<int> nums = {1, 2};
  EXPECT_TRUE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, SelfAuthoredTwoElementsRotated) {
  vector<int> nums = {2, 1};
  EXPECT_TRUE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, SelfAuthoredAllSame) {
  vector<int> nums = {1, 1, 1, 1};
  EXPECT_TRUE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, SelfAuthoredTwoDrops) {
  vector<int> nums = {3, 4, 1, 2, 5};
  EXPECT_FALSE(solution.check(nums));
}

TEST_P(CheckIfArrayIsSortedAndRotatedTest, SelfAuthoredMultipleDrops) {
  vector<int> nums = {5, 1, 4, 3, 2};
  EXPECT_FALSE(solution.check(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CheckIfArrayIsSortedAndRotatedTest,
    ::testing::ValuesIn(CheckIfArrayIsSortedAndRotatedSolution().getStrategyNames()));

}  // namespace problem_1752
}  // namespace leetcode
