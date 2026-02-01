#include "leetcode/problems/kth-smallest-element-in-a-sorted-matrix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_378 {

class KthSmallestElementInASortedMatrixTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  KthSmallestElementInASortedMatrixSolution solution;
};

TEST_P(KthSmallestElementInASortedMatrixTest, Example1) {
  vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
  int k = 8;
  int expected = 13;
  EXPECT_EQ(expected, solution.kthSmallest(matrix, k));
}

TEST_P(KthSmallestElementInASortedMatrixTest, Example2) {
  vector<vector<int>> matrix = {{-5}};
  int k = 1;
  int expected = -5;
  EXPECT_EQ(expected, solution.kthSmallest(matrix, k));
}

TEST_P(KthSmallestElementInASortedMatrixTest, SingleElement) {
  vector<vector<int>> matrix = {{1}};
  int k = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.kthSmallest(matrix, k));
}

TEST_P(KthSmallestElementInASortedMatrixTest, KEquals1) {
  vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
  int k = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.kthSmallest(matrix, k));
}

TEST_P(KthSmallestElementInASortedMatrixTest, KEqualsNSquared) {
  vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
  int k = 9;
  int expected = 15;
  EXPECT_EQ(expected, solution.kthSmallest(matrix, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, KthSmallestElementInASortedMatrixTest,
    ::testing::ValuesIn(KthSmallestElementInASortedMatrixSolution().getStrategyNames()));

}  // namespace problem_378
}  // namespace leetcode
