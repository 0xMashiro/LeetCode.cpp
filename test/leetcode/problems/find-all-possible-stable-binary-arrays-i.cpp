#include "leetcode/problems/find-all-possible-stable-binary-arrays-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3129 {

class FindAllPossibleStableBinaryArraysITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindAllPossibleStableBinaryArraysISolution solution;
};

TEST_P(FindAllPossibleStableBinaryArraysITest, Example1) {
  EXPECT_EQ(2, solution.numberOfStableArrays(1, 1, 2));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, Example2) {
  EXPECT_EQ(1, solution.numberOfStableArrays(1, 2, 1));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, Example3) {
  EXPECT_EQ(14, solution.numberOfStableArrays(3, 3, 2));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, SelfAuthoredSingleZero) {
  EXPECT_EQ(1, solution.numberOfStableArrays(1, 0, 1));
  EXPECT_EQ(1, solution.numberOfStableArrays(1, 0, 5));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, SelfAuthoredSingleOne) {
  EXPECT_EQ(1, solution.numberOfStableArrays(0, 1, 1));
  EXPECT_EQ(1, solution.numberOfStableArrays(0, 1, 5));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, SelfAuthoredBothOne) {
  // zero=1, one=1, limit=1: [0,1] 和 [1,0]
  EXPECT_EQ(2, solution.numberOfStableArrays(1, 1, 1));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, SelfAuthoredLimitSmall) {
  // zero=2, one=2, limit=1: 必须交替，0101 和 1010
  EXPECT_EQ(2, solution.numberOfStableArrays(2, 2, 1));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, SelfAuthoredAllZero) {
  EXPECT_EQ(1, solution.numberOfStableArrays(5, 0, 10));
  EXPECT_EQ(0, solution.numberOfStableArrays(5, 0, 3));
  EXPECT_EQ(1, solution.numberOfStableArrays(5, 0, 5));
}

TEST_P(FindAllPossibleStableBinaryArraysITest, SelfAuthoredAllOne) {
  EXPECT_EQ(1, solution.numberOfStableArrays(0, 5, 10));
  EXPECT_EQ(0, solution.numberOfStableArrays(0, 5, 3));
  EXPECT_EQ(1, solution.numberOfStableArrays(0, 5, 5));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindAllPossibleStableBinaryArraysITest,
    ::testing::ValuesIn(FindAllPossibleStableBinaryArraysISolution().getStrategyNames()));

}  // namespace problem_3129
}  // namespace leetcode
