#include "leetcode/problems/maximum-balanced-shipments.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3638 {

class MaximumBalancedShipmentsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumBalancedShipmentsSolution solution;
};

TEST_P(MaximumBalancedShipmentsTest, Example1) {
  vector<int> weight = {2, 5, 1, 4, 3};
  int expected = 2;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, Example2) {
  vector<int> weight = {4, 4};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, EmptyArray) {
  vector<int> weight = {};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, SingleElement) {
  vector<int> weight = {5};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, TwoElementsBalanced) {
  vector<int> weight = {2, 1};
  int expected = 1;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, TwoElementsNotBalanced) {
  vector<int> weight = {1, 2};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, AllIncreasing) {
  vector<int> weight = {1, 2, 3, 4, 5};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, AllDecreasing) {
  // [5,4,3,2,1] 可以分成 [5,4] 和 [3,2]，最大 2 个
  vector<int> weight = {5, 4, 3, 2, 1};
  int expected = 2;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

TEST_P(MaximumBalancedShipmentsTest, AllSame) {
  vector<int> weight = {3, 3, 3, 3};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxBalancedShipments(weight));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumBalancedShipmentsTest,
    ::testing::ValuesIn(MaximumBalancedShipmentsSolution().getStrategyNames()));

}  // namespace problem_3638
}  // namespace leetcode
