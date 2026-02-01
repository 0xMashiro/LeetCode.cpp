#include "leetcode/problems/divide-array-in-sets-of-k-consecutive-numbers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1296 {

class DivideArrayInSetsOfKConsecutiveNumbersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DivideArrayInSetsOfKConsecutiveNumbersSolution solution;
};

// Example 1: nums = [1,2,3,3,4,4,5,6], k = 4
// Expected: true
// Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
TEST_P(DivideArrayInSetsOfKConsecutiveNumbersTest, Example1) {
  vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 6};
  int k = 4;
  EXPECT_TRUE(solution.isPossibleDivide(nums, k));
}

// Example 2: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
// Expected: true
// Explanation: Array can be divided into [1,2,3], [2,3,4], [3,4,5] and [9,10,11].
TEST_P(DivideArrayInSetsOfKConsecutiveNumbersTest, Example2) {
  vector<int> nums = {3, 2, 1, 2, 3, 4, 3, 4, 5, 9, 10, 11};
  int k = 3;
  EXPECT_TRUE(solution.isPossibleDivide(nums, k));
}

// Example 3: nums = [1,2,3,4], k = 3
// Expected: false
// Explanation: Each array should be divided in subarrays of size 3.
TEST_P(DivideArrayInSetsOfKConsecutiveNumbersTest, Example3) {
  vector<int> nums = {1, 2, 3, 4};
  int k = 3;
  EXPECT_FALSE(solution.isPossibleDivide(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DivideArrayInSetsOfKConsecutiveNumbersTest,
    ::testing::ValuesIn(DivideArrayInSetsOfKConsecutiveNumbersSolution().getStrategyNames()));

}  // namespace problem_1296
}  // namespace leetcode
