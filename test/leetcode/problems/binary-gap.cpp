#include "leetcode/problems/binary-gap.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_868 {

class BinaryGapTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BinaryGapSolution solution;
};

TEST_P(BinaryGapTest, Example1) {
  // n = 22, binary = "10110"
  EXPECT_EQ(2, solution.binaryGap(22));
}

TEST_P(BinaryGapTest, Example2) {
  // n = 8, binary = "1000"
  EXPECT_EQ(0, solution.binaryGap(8));
}

TEST_P(BinaryGapTest, Example3) {
  // n = 5, binary = "101"
  EXPECT_EQ(2, solution.binaryGap(5));
}

TEST_P(BinaryGapTest, SingleBit) {
  // n = 1, binary = "1"
  EXPECT_EQ(0, solution.binaryGap(1));
}

TEST_P(BinaryGapTest, AllOnes) {
  // n = 15, binary = "1111", adjacent pairs: (0,1), (1,2), (2,3) all distance 1
  EXPECT_EQ(1, solution.binaryGap(15));
}

TEST_P(BinaryGapTest, LargeGap) {
  // n = 33, binary = "100001", gap = 5
  EXPECT_EQ(5, solution.binaryGap(33));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BinaryGapTest,
    ::testing::ValuesIn(BinaryGapSolution().getStrategyNames()));

}  // namespace problem_868
}  // namespace leetcode
