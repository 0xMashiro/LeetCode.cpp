
#include "leetcode/problems/k-th-smallest-in-lexicographical-order.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_440 {

class KThSmallestInLexicographicalOrderTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  KThSmallestInLexicographicalOrderSolution solution;
};

TEST_P(KThSmallestInLexicographicalOrderTest, Example1) {
  int n = 13;
  int k = 2;
  int expected = 10;
  EXPECT_EQ(expected, solution.findKthNumber(n, k));
}

TEST_P(KThSmallestInLexicographicalOrderTest, Example2) {
  int n = 1;
  int k = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.findKthNumber(n, k));
}

TEST_P(KThSmallestInLexicographicalOrderTest, SmallRange) {
  // 测试小范围，n=10 时字典序: [1, 10, 2, 3, 4, 5, 6, 7, 8, 9]
  int n = 10;
  EXPECT_EQ(1, solution.findKthNumber(n, 1));
  EXPECT_EQ(10, solution.findKthNumber(n, 2));
  EXPECT_EQ(2, solution.findKthNumber(n, 3));
  EXPECT_EQ(9, solution.findKthNumber(n, 10));
}

TEST_P(KThSmallestInLexicographicalOrderTest, EdgeCase) {
  // n = 2, k = 2, 字典序: [1, 2]
  EXPECT_EQ(2, solution.findKthNumber(2, 2));
  // n = 100, k = 10, 字典序前10个: [1, 10, 100, 11, 12, 13, 14, 15, 16, 17]
  EXPECT_EQ(17, solution.findKthNumber(100, 10));
  // n = 100, k = 3, 应该是 100
  EXPECT_EQ(100, solution.findKthNumber(100, 3));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, KThSmallestInLexicographicalOrderTest,
    ::testing::ValuesIn(KThSmallestInLexicographicalOrderSolution().getStrategyNames()));

}  // namespace problem_440
}  // namespace leetcode
