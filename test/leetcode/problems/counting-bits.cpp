#include "leetcode/problems/counting-bits.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_338 {

class CountingBitsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountingBitsSolution solution;
};

// Example 1: n = 2, Output: [0,1,1]
TEST_P(CountingBitsTest, Example1) {
  int n = 2;
  vector<int> expected = {0, 1, 1};
  vector<int> result = solution.countBits(n);
  EXPECT_EQ(expected, result);
}

// Example 2: n = 5, Output: [0,1,1,2,1,2]
TEST_P(CountingBitsTest, Example2) {
  int n = 5;
  vector<int> expected = {0, 1, 1, 2, 1, 2};
  vector<int> result = solution.countBits(n);
  EXPECT_EQ(expected, result);
}

// Edge case: n = 0, Output: [0]
TEST_P(CountingBitsTest, EdgeCaseZero) {
  int n = 0;
  vector<int> expected = {0};
  vector<int> result = solution.countBits(n);
  EXPECT_EQ(expected, result);
}

// Edge case: n = 1, Output: [0,1]
TEST_P(CountingBitsTest, EdgeCaseOne) {
  int n = 1;
  vector<int> expected = {0, 1};
  vector<int> result = solution.countBits(n);
  EXPECT_EQ(expected, result);
}

// Larger case: verify some values
TEST_P(CountingBitsTest, LargerCase) {
  int n = 8;
  vector<int> result = solution.countBits(n);
  // 0:0, 1:1, 2:1, 3:2, 4:1, 5:2, 6:2, 7:3, 8:1
  EXPECT_EQ(result[7], 3);  // 7 = 0b111
  EXPECT_EQ(result[8], 1);  // 8 = 0b1000
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountingBitsTest,
    ::testing::ValuesIn(CountingBitsSolution().getStrategyNames()));

}  // namespace problem_338
}  // namespace leetcode
