#include "leetcode/problems/partition-array-into-disjoint-intervals.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_915 {

class PartitionArrayIntoDisjointIntervalsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PartitionArrayIntoDisjointIntervalsSolution solution;
};

TEST_P(PartitionArrayIntoDisjointIntervalsTest, Example1) {
  vector<int> nums = {5, 0, 3, 8, 6};
  int expected = 3;
  EXPECT_EQ(expected, solution.partitionDisjoint(nums));
}

TEST_P(PartitionArrayIntoDisjointIntervalsTest, Example2) {
  vector<int> nums = {1, 1, 1, 0, 6, 12};
  int expected = 4;
  EXPECT_EQ(expected, solution.partitionDisjoint(nums));
}

TEST_P(PartitionArrayIntoDisjointIntervalsTest, MinArrayCase) {
  // 最小数组，长度为2
  vector<int> nums = {1, 2};
  int expected = 1;
  EXPECT_EQ(expected, solution.partitionDisjoint(nums));
}

TEST_P(PartitionArrayIntoDisjointIntervalsTest, AllSameElements) {
  // 所有元素相同
  vector<int> nums = {5, 5, 5, 5, 5};
  int expected = 1;
  EXPECT_EQ(expected, solution.partitionDisjoint(nums));
}

TEST_P(PartitionArrayIntoDisjointIntervalsTest, IncreasingArray) {
  // 严格递增数组，left 只需要一个元素
  vector<int> nums = {1, 2, 3, 4, 5};
  int expected = 1;
  EXPECT_EQ(expected, solution.partitionDisjoint(nums));
}

TEST_P(PartitionArrayIntoDisjointIntervalsTest, SmallLeftCase) {
  // left 只有一个元素的边界情况
  vector<int> nums = {0, 10, 20, 30};
  int expected = 1;
  EXPECT_EQ(expected, solution.partitionDisjoint(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PartitionArrayIntoDisjointIntervalsTest,
    ::testing::ValuesIn(PartitionArrayIntoDisjointIntervalsSolution().getStrategyNames()));

}  // namespace problem_915
}  // namespace leetcode
