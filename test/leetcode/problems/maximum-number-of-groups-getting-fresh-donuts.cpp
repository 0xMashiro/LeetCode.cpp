#include "leetcode/problems/maximum-number-of-groups-getting-fresh-donuts.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1815 {

class MaximumNumberOfGroupsGettingFreshDonutsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumNumberOfGroupsGettingFreshDonutsSolution solution;
};

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, Example1) {
  int batchSize = 3;
  vector<int> groups = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(4, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, Example2) {
  int batchSize = 4;
  vector<int> groups = {1, 3, 2, 5, 2, 2, 1, 6};
  EXPECT_EQ(4, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, SingleGroup) {
  int batchSize = 3;
  vector<int> groups = {5};
  // 5 % 3 = 2, 第一个组总是快乐的
  EXPECT_EQ(1, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, AllMultipleOfBatchSize) {
  int batchSize = 3;
  vector<int> groups = {3, 6, 9, 12};
  // 所有组余数都是0，都是快乐的
  EXPECT_EQ(4, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, SmallBatchSize) {
  int batchSize = 1;
  vector<int> groups = {1, 2, 3, 4, 5};
  // batchSize=1，所有余数都是0，都是快乐的
  EXPECT_EQ(5, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, ComplementaryPairs) {
  int batchSize = 5;
  vector<int> groups = {1, 4, 2, 3, 1, 4};
  // 1+4=5, 2+3=5, 1+4=5，可以配成3对，都是快乐的
  // 或者 [1,4], [2,3], [1,4] 这样排列，每组都是快乐的
  EXPECT_EQ(3, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, MaxConstraintBatchSize) {
  int batchSize = 9;
  vector<int> groups = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // 9 % 9 = 0，是快乐的
  // 其余需要找最优排列
  EXPECT_EQ(5, solution.maxHappyGroups(batchSize, groups));
}

TEST_P(MaximumNumberOfGroupsGettingFreshDonutsTest, SameRemainder) {
  int batchSize = 3;
  vector<int> groups = {1, 4, 7, 10};  // 都余1
  // [1,1,1,1] 排列，只有第一个是快乐的，或者 [3个1][1个1] 这样
  // 最优：[3个1] 组成一组快乐的，剩下[1个1]也是快乐的 = 2
  // 或者 1+1+1=3，刚好一批，1个快乐的组
  // 实际上每组是独立的，[4,7,10,1] = [1,1,1,1]，第一个是快乐的
  // 然后剩下3个1，1+1+1=3，最后一个组也是快乐的 = 2
  EXPECT_EQ(2, solution.maxHappyGroups(batchSize, groups));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumNumberOfGroupsGettingFreshDonutsTest,
    ::testing::ValuesIn(MaximumNumberOfGroupsGettingFreshDonutsSolution().getStrategyNames()));

}  // namespace problem_1815
}  // namespace leetcode
