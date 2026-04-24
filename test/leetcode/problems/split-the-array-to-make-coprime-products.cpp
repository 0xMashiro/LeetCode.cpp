#include "leetcode/problems/split-the-array-to-make-coprime-products.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2584 {

class SplitTheArrayToMakeCoprimeProductsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SplitTheArrayToMakeCoprimeProductsSolution solution;
};

TEST_P(SplitTheArrayToMakeCoprimeProductsTest, Example1) {
  vector<int> nums = {4, 7, 8, 15, 3, 5};
  int expected = 2;
  EXPECT_EQ(expected, solution.findValidSplit(nums));
}

TEST_P(SplitTheArrayToMakeCoprimeProductsTest, Example2) {
  vector<int> nums = {4, 7, 15, 8, 3, 5};
  int expected = -1;
  EXPECT_EQ(expected, solution.findValidSplit(nums));
}

TEST_P(SplitTheArrayToMakeCoprimeProductsTest, EdgeCaseSingleElement) {
  vector<int> nums = {1};
  int expected = -1;
  EXPECT_EQ(expected, solution.findValidSplit(nums));
}

TEST_P(SplitTheArrayToMakeCoprimeProductsTest, EdgeCaseTwoElements) {
  vector<int> nums = {2, 3};
  int expected = 0;
  EXPECT_EQ(expected, solution.findValidSplit(nums));
}

TEST_P(SplitTheArrayToMakeCoprimeProductsTest, EdgeCaseTwoElementsSamePrime) {
  vector<int> nums = {2, 2};
  int expected = -1;
  EXPECT_EQ(expected, solution.findValidSplit(nums));
}

TEST_P(SplitTheArrayToMakeCoprimeProductsTest, AllOnes) {
  vector<int> nums = {1, 1, 1};
  int expected = 0;
  EXPECT_EQ(expected, solution.findValidSplit(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SplitTheArrayToMakeCoprimeProductsTest,
    ::testing::ValuesIn(SplitTheArrayToMakeCoprimeProductsSolution().getStrategyNames()));

}  // namespace problem_2584
}  // namespace leetcode
