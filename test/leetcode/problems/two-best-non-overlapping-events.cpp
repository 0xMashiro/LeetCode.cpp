#include "leetcode/problems/two-best-non-overlapping-events.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2054 {

class TwoBestNonOverlappingEventsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TwoBestNonOverlappingEventsSolution solution;
};

TEST_P(TwoBestNonOverlappingEventsTest, Example1) {
  vector<vector<int>> events = {{1, 3, 2}, {4, 5, 2}, {2, 4, 3}};
  int expected = 4;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, Example2) {
  vector<vector<int>> events = {{1, 3, 2}, {4, 5, 2}, {1, 5, 5}};
  int expected = 5;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, Example3) {
  vector<vector<int>> events = {{1, 5, 3}, {1, 5, 1}, {6, 6, 5}};
  int expected = 8;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

// 自定义测试用例
TEST_P(TwoBestNonOverlappingEventsTest, TwoNonOverlappingEvents) {
  vector<vector<int>> events = {{1, 2, 10}, {3, 4, 20}};
  int expected = 30;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, TwoOverlappingEvents) {
  vector<vector<int>> events = {{1, 3, 10}, {2, 4, 20}};
  // 只能选一个事件，最大价值为20
  int expected = 20;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, AllOverlapping) {
  vector<vector<int>> events = {{1, 5, 1}, {1, 5, 2}, {1, 5, 3}};
  // 所有事件重叠，只能选一个，最大价值为3
  int expected = 3;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, SingleEvent) {
  // 虽然约束说至少两个事件，但测试单个事件的情况
  vector<vector<int>> events = {{1, 3, 100}};
  int expected = 100;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, ThreeEventsChooseTwo) {
  vector<vector<int>> events = {{1, 2, 5}, {3, 4, 7}, {5, 6, 3}};
  // 可以选择事件0和1，或者1和2，最大值5+7=12
  int expected = 12;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

TEST_P(TwoBestNonOverlappingEventsTest, LargeValues) {
  vector<vector<int>> events = {{1, 1, 1000000}, {2, 2, 1000000}};
  // 两个事件不重叠，总和为2000000
  int expected = 2000000;
  EXPECT_EQ(expected, solution.maxTwoEvents(events));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TwoBestNonOverlappingEventsTest,
    ::testing::ValuesIn(TwoBestNonOverlappingEventsSolution().getStrategyNames()));

}  // namespace problem_2054
}  // namespace leetcode