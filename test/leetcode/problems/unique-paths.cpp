#include "leetcode/problems/unique-paths.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_62 {

class UniquePathsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  UniquePathsSolution solution;
};

TEST_P(UniquePathsTest, Example1) {
  // m = 3, n = 7, expected = 28
  int m = 3;
  int n = 7;
  int expected = 28;
  EXPECT_EQ(expected, solution.uniquePaths(m, n));
}

TEST_P(UniquePathsTest, Example2) {
  // m = 3, n = 2, expected = 3
  int m = 3;
  int n = 2;
  int expected = 3;
  EXPECT_EQ(expected, solution.uniquePaths(m, n));
}

TEST_P(UniquePathsTest, MinimumGrid) {
  // 最小网格 1x1
  int m = 1;
  int n = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.uniquePaths(m, n));
}

TEST_P(UniquePathsTest, SingleRow) {
  // 单行网格，只有一条路径
  int m = 1;
  int n = 7;
  int expected = 1;
  EXPECT_EQ(expected, solution.uniquePaths(m, n));
}

TEST_P(UniquePathsTest, SingleColumn) {
  // 单列网格，只有一条路径
  int m = 5;
  int n = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.uniquePaths(m, n));
}

TEST_P(UniquePathsTest, SmallGrid) {
  // 2x2 网格，2 条路径
  int m = 2;
  int n = 2;
  int expected = 2;
  EXPECT_EQ(expected, solution.uniquePaths(m, n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, UniquePathsTest,
    ::testing::ValuesIn(UniquePathsSolution().getStrategyNames()));

}  // namespace problem_62
}  // namespace leetcode
