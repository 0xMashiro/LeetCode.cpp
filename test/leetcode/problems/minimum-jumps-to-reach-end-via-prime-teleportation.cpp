#include "leetcode/problems/minimum-jumps-to-reach-end-via-prime-teleportation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3629 {

class MinimumJumpsToReachEndViaPrimeTeleportationTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumJumpsToReachEndViaPrimeTeleportationSolution solution;
};

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, Example1) {
  vector<int> nums = {1, 2, 4, 6};
  EXPECT_EQ(2, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, Example2) {
  vector<int> nums = {2, 3, 4, 7, 9};
  EXPECT_EQ(2, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, Example3) {
  vector<int> nums = {4, 6, 5, 8};
  EXPECT_EQ(3, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, SelfAuthoredSingleElement) {
  vector<int> nums = {42};
  EXPECT_EQ(0, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, SelfAuthoredTwoElements) {
  vector<int> nums = {3, 6};
  // 0: nums[0]=3 (prime) → teleport to 1 (6%3==0) → answer = 1
  EXPECT_EQ(1, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, SelfAuthoredAllOnes) {
  vector<int> nums = {1, 1, 1, 1, 1};
  // No primes, only adjacent steps: 0→1→2→3→4
  EXPECT_EQ(4, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest, SelfAuthoredTeleportChain) {
  vector<int> nums = {2, 4, 3, 9};
  // 0: nums[0]=2 prime → teleport to 1 (4%2==0) dist=1
  // 1: nums[1]=4 not prime, adj to 2 dist=2
  // 2: nums[2]=3 prime → teleport to 3 (9%3==0) dist=3
  // Answer: 3 (0→1→2→3 with teleports at 0 and 2)
  // OR: 0→adj→1→adj→2→teleport→3 = 3
  EXPECT_EQ(3, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest,
       SelfAuthoredNoTeleport) {
  vector<int> nums = {4, 8, 10, 12};
  // No primes, adjacent steps only: answer = 3
  EXPECT_EQ(3, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest,
       SelfAuthoredBackwardThenTeleport) {
  vector<int> nums = {3, 1, 1, 1, 6};
  // 0: nums[0]=3 prime, can teleport to 4 (6%3==0) in 1 step
  // Answer: 1
  EXPECT_EQ(1, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest,
       SelfAuthoredLargeGap) {
  vector<int> nums = {2, 1, 1, 1, 1, 1, 1, 1, 8};
  // 0: nums[0]=2 prime → teleport to 8 (8%2==0) in 1 step
  EXPECT_EQ(1, solution.minJumps(nums));
}

TEST_P(MinimumJumpsToReachEndViaPrimeTeleportationTest,
       SelfAuthoredMultipleSamePrimes) {
  vector<int> nums = {7, 14, 7, 21};
  // 0: nums[0]=7 prime → teleport to 1 (14%7==0) dist=1
  // 1: nums[1]=14 not prime, adj to 2 dist=2
  // 2: nums[2]=7 prime but prime_to_indices[7] already cleared after first use
  //    So can only adj to 3 dist=3
  // Answer: 3 (0→1→2→3)
  // Alternative: 0→teleport→1→adj→2→adj→3 = 3
  // Or: 0→teleport→3 (21%7==0) in 1 step!
  // Wait, 21 % 7 == 0, so 0 can teleport directly to 3!
  EXPECT_EQ(1, solution.minJumps(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumJumpsToReachEndViaPrimeTeleportationTest,
    ::testing::ValuesIn(
        MinimumJumpsToReachEndViaPrimeTeleportationSolution()
            .getStrategyNames()));

}  // namespace problem_3629
}  // namespace leetcode
