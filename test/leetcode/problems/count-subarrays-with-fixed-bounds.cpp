#include "leetcode/problems/count-subarrays-with-fixed-bounds.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2444 {

class CountSubarraysWithFixedBoundsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountSubarraysWithFixedBoundsSolution solution;
};

TEST_P(CountSubarraysWithFixedBoundsTest, Example1) {
  vector<int> nums = {1, 3, 5, 2, 7, 5};
  int minK = 1, maxK = 5;
  EXPECT_EQ(2, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, Example2) {
  vector<int> nums = {1, 1, 1, 1};
  int minK = 1, maxK = 1;
  EXPECT_EQ(10, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredMinEqualsMax) {
  // All elements equal to minK=maxK, every subarray qualifies
  vector<int> nums = {2, 2, 2};
  int minK = 2, maxK = 2;
  EXPECT_EQ(6, solution.countSubarrays(nums, minK, maxK));  // 3*4/2 = 6
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredMaxKMissing) {
  // maxK not present in array, no subarray qualifies
  vector<int> nums = {1, 2, 3};
  int minK = 1, maxK = 5;
  EXPECT_EQ(0, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredMinKMissing) {
  // minK not present in array, no subarray qualifies
  vector<int> nums = {6, 7, 8};
  int minK = 1, maxK = 8;
  EXPECT_EQ(0, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredWithBadElements) {
  // nums[1]=6 and nums[4]=6 are >5, splitting into segments with no valid subarray
  vector<int> nums = {1, 6, 5, 2, 6, 1};
  int minK = 1, maxK = 5;
  EXPECT_EQ(0, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredMultipleSegments) {
  // 0 is a bad element (<1), splitting into two segments each containing [1,5]
  vector<int> nums = {1, 5, 0, 1, 5};
  int minK = 1, maxK = 5;
  EXPECT_EQ(2, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredSingleValidSubarray) {
  // Only the full array contains both 1 and 5
  vector<int> nums = {1, 2, 3, 4, 5};
  int minK = 1, maxK = 5;
  EXPECT_EQ(1, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredMinEqualsMaxMultiple) {
  // minK == maxK, every element equals that value
  vector<int> nums = {5, 5, 5, 5, 5};
  int minK = 5, maxK = 5;
  EXPECT_EQ(15, solution.countSubarrays(nums, minK, maxK));  // 5*6/2 = 15
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredLargeRange) {
  // All elements valid, need both ends
  vector<int> nums = {1, 1, 5, 5};
  int minK = 1, maxK = 5;
  // Trace:
  // i=0(1): last_bad=-1, last_min=0, last_max=-1 => left=-1, skip
  // i=1(1): last_bad=-1, last_min=1, last_max=-1 => left=-1, skip
  // i=2(5): last_bad=-1, last_min=1, last_max=2 => left=1, ans+=1-(-1)=2
  // i=3(5): last_bad=-1, last_min=1, last_max=3 => left=1, ans+=1-(-1)=2 (ans=4)
  // Total: 4
  // Valid subarrays: [1,1,5], [1,1,5,5], [1,5], [1,5,5] -> 4
  EXPECT_EQ(4, solution.countSubarrays(nums, minK, maxK));
}

TEST_P(CountSubarraysWithFixedBoundsTest, SelfAuthoredAtStartAndEnd) {
  // minK and maxK at boundaries only
  vector<int> nums = {5, 2, 2, 1};
  int minK = 1, maxK = 5;
  // i=0(5): last_bad=-1, last_min=-1, last_max=0 => left=-1, skip
  // i=1(2): last_bad=-1, last_min=-1, last_max=0 => left=-1, skip
  // i=2(2): same => skip
  // i=3(1): last_bad=-1, last_min=3, last_max=0 => left=0, ans+=0-(-1)=1
  // Total: 1 ([5,2,2,1])
  EXPECT_EQ(1, solution.countSubarrays(nums, minK, maxK));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountSubarraysWithFixedBoundsTest,
    ::testing::ValuesIn(CountSubarraysWithFixedBoundsSolution().getStrategyNames()));

}  // namespace problem_2444
}  // namespace leetcode
