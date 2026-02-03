#include "leetcode/problems/neighboring-bitwise-xor.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2683 {

class NeighboringBitwiseXorTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NeighboringBitwiseXorSolution solution;
};

// Example 1: derived = [1,1,0], valid original exists [0,1,0]
TEST_P(NeighboringBitwiseXorTest, Example1) {
  vector<int> derived = {1, 1, 0};
  EXPECT_TRUE(solution.doesValidArrayExist(derived));
}

// Example 2: derived = [1,1], valid original exists [0,1]
TEST_P(NeighboringBitwiseXorTest, Example2) {
  vector<int> derived = {1, 1};
  EXPECT_TRUE(solution.doesValidArrayExist(derived));
}

// Example 3: derived = [1,0], no valid original exists
TEST_P(NeighboringBitwiseXorTest, Example3) {
  vector<int> derived = {1, 0};
  EXPECT_FALSE(solution.doesValidArrayExist(derived));
}

// Edge case: single element 0, valid (original = [0] or [1])
TEST_P(NeighboringBitwiseXorTest, SingleElementZero) {
  vector<int> derived = {0};
  EXPECT_TRUE(solution.doesValidArrayExist(derived));
}

// Edge case: single element 1, invalid (original XOR original = 0, never 1)
TEST_P(NeighboringBitwiseXorTest, SingleElementOne) {
  vector<int> derived = {1};
  EXPECT_FALSE(solution.doesValidArrayExist(derived));
}

// Edge case: all zeros, valid (original can be all same values)
TEST_P(NeighboringBitwiseXorTest, AllZeros) {
  vector<int> derived = {0, 0, 0, 0, 0};
  EXPECT_TRUE(solution.doesValidArrayExist(derived));
}

// Edge case: all ones with even count, valid
TEST_P(NeighboringBitwiseXorTest, AllOnesEvenCount) {
  vector<int> derived = {1, 1, 1, 1};
  EXPECT_TRUE(solution.doesValidArrayExist(derived));
}

// Edge case: all ones with odd count, invalid
TEST_P(NeighboringBitwiseXorTest, AllOnesOddCount) {
  vector<int> derived = {1, 1, 1};
  EXPECT_FALSE(solution.doesValidArrayExist(derived));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NeighboringBitwiseXorTest,
    ::testing::ValuesIn(NeighboringBitwiseXorSolution().getStrategyNames()));

}  // namespace problem_2683
}  // namespace leetcode
