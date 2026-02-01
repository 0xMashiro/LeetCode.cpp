#include "leetcode/problems/minimum-number-of-operations-to-reinitialize-a-permutation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1806 {

class MinimumNumberOfOperationsToReinitializeAPermutationTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfOperationsToReinitializeAPermutationSolution solution;
};

TEST_P(MinimumNumberOfOperationsToReinitializeAPermutationTest, Example1) {
  // n = 2, expected = 1
  // perm = [0,1] -> [0,1]
  EXPECT_EQ(1, solution.reinitializePermutation(2));
}

TEST_P(MinimumNumberOfOperationsToReinitializeAPermutationTest, Example2) {
  // n = 4, expected = 2
  // perm = [0,1,2,3] -> [0,2,1,3] -> [0,1,2,3]
  EXPECT_EQ(2, solution.reinitializePermutation(4));
}

TEST_P(MinimumNumberOfOperationsToReinitializeAPermutationTest, Example3) {
  // n = 6, expected = 4
  EXPECT_EQ(4, solution.reinitializePermutation(6));
}

TEST_P(MinimumNumberOfOperationsToReinitializeAPermutationTest, SmallEvenNumbers) {
  // 测试其他小的偶数
  EXPECT_EQ(1, solution.reinitializePermutation(2));
  EXPECT_EQ(2, solution.reinitializePermutation(4));
  EXPECT_EQ(4, solution.reinitializePermutation(6));
  EXPECT_EQ(3, solution.reinitializePermutation(8));
  EXPECT_EQ(6, solution.reinitializePermutation(10));
}

TEST_P(MinimumNumberOfOperationsToReinitializeAPermutationTest, LargerValues) {
  // 测试较大的偶数
  EXPECT_EQ(10, solution.reinitializePermutation(12));
  EXPECT_EQ(12, solution.reinitializePermutation(14));
  EXPECT_EQ(4, solution.reinitializePermutation(16));
  EXPECT_EQ(8, solution.reinitializePermutation(18));
}

TEST_P(MinimumNumberOfOperationsToReinitializeAPermutationTest, PowerOfTwo) {
  // 测试 2 的幂次
  EXPECT_EQ(1, solution.reinitializePermutation(2));    // 2^1
  EXPECT_EQ(2, solution.reinitializePermutation(4));    // 2^2
  EXPECT_EQ(3, solution.reinitializePermutation(8));    // 2^3
  EXPECT_EQ(4, solution.reinitializePermutation(16));   // 2^4
  EXPECT_EQ(5, solution.reinitializePermutation(32));   // 2^5
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfOperationsToReinitializeAPermutationTest,
    ::testing::ValuesIn(MinimumNumberOfOperationsToReinitializeAPermutationSolution().getStrategyNames()));

}  // namespace problem_1806
}  // namespace leetcode
