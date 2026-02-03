#include "leetcode/problems/keys-and-rooms.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_841 {

class KeysAndRoomsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  KeysAndRoomsSolution solution;
};

TEST_P(KeysAndRoomsTest, Example1) {
  vector<vector<int>> rooms = {{1}, {2}, {3}, {}};
  EXPECT_TRUE(solution.canVisitAllRooms(rooms));
}

TEST_P(KeysAndRoomsTest, Example2) {
  vector<vector<int>> rooms = {{1, 3}, {3, 0, 1}, {2}, {0}};
  EXPECT_FALSE(solution.canVisitAllRooms(rooms));
}

TEST_P(KeysAndRoomsTest, SingleRoom) {
  // 只有一个房间（房间0），已经访问
  vector<vector<int>> rooms = {{}};
  EXPECT_TRUE(solution.canVisitAllRooms(rooms));
}

TEST_P(KeysAndRoomsTest, TwoRoomsConnected) {
  // 两个房间互相有钥匙
  vector<vector<int>> rooms = {{1}, {0}};
  EXPECT_TRUE(solution.canVisitAllRooms(rooms));
}

TEST_P(KeysAndRoomsTest, CannotAccessRoom) {
  // 房间1有钥匙，但房间1本身是锁着的且没有其他钥匙能打开它
  vector<vector<int>> rooms = {{}, {0}};
  EXPECT_FALSE(solution.canVisitAllRooms(rooms));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, KeysAndRoomsTest,
    ::testing::ValuesIn(KeysAndRoomsSolution().getStrategyNames()));

}  // namespace problem_841
}  // namespace leetcode
