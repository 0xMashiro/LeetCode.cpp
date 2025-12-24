
#include "leetcode/problems/apple-redistribution-into-boxes.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3074 {

class AppleRedistributionIntoBoxesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AppleRedistributionIntoBoxesSolution solution;
};

TEST_P(AppleRedistributionIntoBoxesTest, Example1) {
  vector<int> apple = {1, 3, 2};
  vector<int> capacity = {4, 3, 1, 5, 2};
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

TEST_P(AppleRedistributionIntoBoxesTest, Example2) {
  vector<int> apple = {5, 5, 5};
  vector<int> capacity = {2, 4, 2, 7};
  int expected = 4;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

// Additional test cases
TEST_P(AppleRedistributionIntoBoxesTest, SinglePackSingleBox) {
  vector<int> apple = {10};
  vector<int> capacity = {10};
  int expected = 1;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

TEST_P(AppleRedistributionIntoBoxesTest, SinglePackMultipleBoxes) {
  vector<int> apple = {10};
  vector<int> capacity = {3, 3, 4, 5};
  // Need boxes with capacities 5 and 4 (or 5 and 3+3, but we take largest first: 5+4=9<10, need 5+4+3=12)
  // Sorting greedy picks 5, then 4, then 3 -> 3 boxes
  // Actually total apples=10, capacities sorted: 5,4,3,3 -> 5+4=9<10, add 3 ->12>=10, so 3 boxes
  int expected = 3;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

TEST_P(AppleRedistributionIntoBoxesTest, MultiplePacksExactMatch) {
  vector<int> apple = {2, 3, 5};
  vector<int> capacity = {1, 2, 3, 4, 5};
  // total apples = 10
  // capacities sorted: 5,4,3,2,1 -> 5+4=9<10, add 3 ->12>=10, so 3 boxes
  int expected = 3;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

TEST_P(AppleRedistributionIntoBoxesTest, AllBoxesNeeded) {
  vector<int> apple = {50, 50, 50};  // total 150
  vector<int> capacity = {30, 30, 30, 30, 30};  // each 30, need all 5 boxes (150)
  int expected = 5;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

TEST_P(AppleRedistributionIntoBoxesTest, LargeCapacityCoversAll) {
  vector<int> apple = {1, 2, 3, 4, 5};  // total 15
  vector<int> capacity = {20, 1, 1};
  // Only need the box with capacity 20
  int expected = 1;
  EXPECT_EQ(expected, solution.minimumBoxes(apple, capacity));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AppleRedistributionIntoBoxesTest,
    ::testing::ValuesIn(AppleRedistributionIntoBoxesSolution().getStrategyNames()));

}  // namespace problem_3074
}  // namespace leetcode