#include "leetcode/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3405 {

class CountTheNumberOfArraysWithKMatchingAdjacentElementsTest 
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution solution;
};

// 示例 1：n = 3, m = 2, k = 1，答案 = 4
// 好数组：[1,1,2], [1,2,2], [2,1,1], [2,2,1]
TEST_P(CountTheNumberOfArraysWithKMatchingAdjacentElementsTest, Example1) {
  int n = 3, m = 2, k = 1;
  int expected = 4;
  EXPECT_EQ(expected, solution.countGoodArrays(n, m, k));
}

// 示例 2：n = 4, m = 2, k = 2，答案 = 6
// 好数组：[1,1,1,2], [1,1,2,2], [1,2,2,2], [2,1,1,1], [2,2,1,1], [2,2,2,1]
TEST_P(CountTheNumberOfArraysWithKMatchingAdjacentElementsTest, Example2) {
  int n = 4, m = 2, k = 2;
  int expected = 6;
  EXPECT_EQ(expected, solution.countGoodArrays(n, m, k));
}

// 示例 3：n = 5, m = 2, k = 0，答案 = 2
// 好数组：[1,2,1,2,1], [2,1,2,1,2]
TEST_P(CountTheNumberOfArraysWithKMatchingAdjacentElementsTest, Example3) {
  int n = 5, m = 2, k = 0;
  int expected = 2;
  EXPECT_EQ(expected, solution.countGoodArrays(n, m, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    CountTheNumberOfArraysWithKMatchingAdjacentElementsTest,
    ::testing::ValuesIn(
        CountTheNumberOfArraysWithKMatchingAdjacentElementsSolution()
            .getStrategyNames()));

}  // namespace problem_3405
}  // namespace leetcode