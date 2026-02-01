#include "leetcode/problems/minimum-number-of-moves-to-seat-everyone.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2037 {

class MinimumNumberOfMovesToSeatEveryoneTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumNumberOfMovesToSeatEveryoneSolution solution;
};

// 示例 1: seats = [3,1,5], students = [2,7,4], 输出: 4
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, Example1) {
  vector<int> seats = {3, 1, 5};
  vector<int> students = {2, 7, 4};
  EXPECT_EQ(4, solution.minMovesToSeat(seats, students));
}

// 示例 2: seats = [4,1,5,9], students = [1,3,2,6], 输出: 7
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, Example2) {
  vector<int> seats = {4, 1, 5, 9};
  vector<int> students = {1, 3, 2, 6};
  EXPECT_EQ(7, solution.minMovesToSeat(seats, students));
}

// 示例 3: seats = [2,2,6,6], students = [1,3,2,6], 输出: 4
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, Example3) {
  vector<int> seats = {2, 2, 6, 6};
  vector<int> students = {1, 3, 2, 6};
  EXPECT_EQ(4, solution.minMovesToSeat(seats, students));
}

// 边界情况：只有一个座位和一个学生
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, SingleElement) {
  vector<int> seats = {5};
  vector<int> students = {3};
  EXPECT_EQ(2, solution.minMovesToSeat(seats, students));
}

// 边界情况：位置相同，不需要移动
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, NoMoveNeeded) {
  vector<int> seats = {1, 2, 3};
  vector<int> students = {1, 2, 3};
  EXPECT_EQ(0, solution.minMovesToSeat(seats, students));
}

// 边界情况：所有学生需要移动很远
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, LargeMoves) {
  vector<int> seats = {1, 2, 3};
  vector<int> students = {100, 99, 98};
  EXPECT_EQ(291, solution.minMovesToSeat(seats, students));
}

// 边界情况：重复位置
TEST_P(MinimumNumberOfMovesToSeatEveryoneTest, DuplicatePositions) {
  vector<int> seats = {5, 5, 5};
  vector<int> students = {5, 5, 5};
  EXPECT_EQ(0, solution.minMovesToSeat(seats, students));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumNumberOfMovesToSeatEveryoneTest,
    ::testing::ValuesIn(MinimumNumberOfMovesToSeatEveryoneSolution().getStrategyNames()));

}  // namespace problem_2037
}  // namespace leetcode
