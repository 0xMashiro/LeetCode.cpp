#include "leetcode/problems/meeting-rooms-iii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2402 {

class MeetingRoomsIiiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MeetingRoomsIiiSolution solution;
};

TEST_P(MeetingRoomsIiiTest, Example1) {
  int n = 2;
  vector<vector<int>> meetings = {{0, 10}, {1, 5}, {2, 7}, {3, 4}};
  int expected = 0;
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

TEST_P(MeetingRoomsIiiTest, Example2) {
  int n = 3;
  vector<vector<int>> meetings = {{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}};
  int expected = 1;
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

// 自定义测试用例1：只有一个房间
TEST_P(MeetingRoomsIiiTest, SingleRoom) {
  int n = 1;
  vector<vector<int>> meetings = {{0, 5}, {6, 10}, {11, 15}};
  int expected = 0;
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

// 自定义测试用例2：多个房间，会议没有重叠
TEST_P(MeetingRoomsIiiTest, NonOverlappingMeetings) {
  int n = 3;
  vector<vector<int>> meetings = {{0, 1}, {1, 2}, {2, 3}};
  int expected = 0;  // 房间0会举办第一个会议，其他房间也可能举办，但房间0编号最小
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

// 自定义测试用例3：所有会议时间相同，需要延迟
TEST_P(MeetingRoomsIiiTest, AllMeetingsSameTime) {
  int n = 2;
  vector<vector<int>> meetings = {{0, 5}, {0, 5}, {0, 5}, {0, 5}};
  // 房间0: 会议1 (0-5), 会议3 (5-10)
  // 房间1: 会议2 (5-10), 会议4 (10-15)
  // 房间0和1各举办2次会议，返回房间0
  int expected = 0;
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

// 自定义测试用例4：大n小会议数
TEST_P(MeetingRoomsIiiTest, ManyRoomsFewMeetings) {
  int n = 100;
  vector<vector<int>> meetings = {{0, 1}, {1, 2}};
  // 房间0举办会议1，房间1举办会议2，房间0和1各1次，返回0
  int expected = 0;
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

// 自定义测试用例5：会议需要长时间延迟
TEST_P(MeetingRoomsIiiTest, LongDelay) {
  int n = 2;
  vector<vector<int>> meetings = {{0, 100}, {10, 20}, {20, 30}, {30, 40}};
  // 房间0: 会议1 (0-100)
  // 房间1: 会议2 (10-20), 会议3 (20-30), 会议4 (30-40)
  // 房间1举办3次会议，房间0举办1次，返回1
  int expected = 1;
  int result = solution.mostBooked(n, meetings);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MeetingRoomsIiiTest,
    ::testing::ValuesIn(MeetingRoomsIiiSolution().getStrategyNames()));

}  // namespace problem_2402
}  // namespace leetcode