#include "leetcode/problems/kth-smallest-instructions.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1643 {

class KthSmallestInstructionsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  KthSmallestInstructionsSolution solution;
};

TEST_P(KthSmallestInstructionsTest, Example1) {
  vector<int> destination = {2, 3};
  int k = 1;
  string expected = "HHHVV";
  EXPECT_EQ(expected, solution.kthSmallestPath(destination, k));
}

TEST_P(KthSmallestInstructionsTest, Example2) {
  vector<int> destination = {2, 3};
  int k = 2;
  string expected = "HHVHV";
  EXPECT_EQ(expected, solution.kthSmallestPath(destination, k));
}

TEST_P(KthSmallestInstructionsTest, Example3) {
  vector<int> destination = {2, 3};
  int k = 3;
  string expected = "HHVVH";
  EXPECT_EQ(expected, solution.kthSmallestPath(destination, k));
}

// 边界测试：最小规模
TEST_P(KthSmallestInstructionsTest, MinSize) {
  vector<int> destination = {1, 1};
  int k = 1;
  string expected = "HV";
  EXPECT_EQ(expected, solution.kthSmallestPath(destination, k));
  
  k = 2;
  expected = "VH";
  EXPECT_EQ(expected, solution.kthSmallestPath(destination, k));
}

// 边界测试：最后一组
TEST_P(KthSmallestInstructionsTest, LastCase) {
  vector<int> destination = {2, 3};
  int k = 10;  // C(5,2) = 10，最后一组
  string expected = "VVHHH";
  EXPECT_EQ(expected, solution.kthSmallestPath(destination, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, KthSmallestInstructionsTest,
    ::testing::ValuesIn(KthSmallestInstructionsSolution().getStrategyNames()));

}  // namespace problem_1643
}  // namespace leetcode
