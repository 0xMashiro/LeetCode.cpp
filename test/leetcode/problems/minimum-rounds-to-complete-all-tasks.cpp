
#include "leetcode/problems/minimum-rounds-to-complete-all-tasks.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2244 {

class MinimumRoundsToCompleteAllTasksTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumRoundsToCompleteAllTasksSolution solution;
};

TEST_P(MinimumRoundsToCompleteAllTasksTest, Example1) {
  vector<int> tasks = {2, 2, 3, 3, 2, 4, 4, 4, 4, 4};
  EXPECT_EQ(4, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, Example2) {
  vector<int> tasks = {2, 3, 3};
  EXPECT_EQ(-1, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, AllSameTwoTasks) {
  // 2 个相同难度的任务
  vector<int> tasks = {5, 5};
  EXPECT_EQ(1, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, AllSameThreeTasks) {
  // 3 个相同难度的任务
  vector<int> tasks = {5, 5, 5};
  EXPECT_EQ(1, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, AllSameFourTasks) {
  // 4 个相同难度的任务: 2 + 2
  vector<int> tasks = {5, 5, 5, 5};
  EXPECT_EQ(2, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, AllSameFiveTasks) {
  // 5 个相同难度的任务: 2 + 3
  vector<int> tasks = {5, 5, 5, 5, 5};
  EXPECT_EQ(2, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, AllSameSixTasks) {
  // 6 个相同难度的任务: 3 + 3
  vector<int> tasks = {5, 5, 5, 5, 5, 5};
  EXPECT_EQ(2, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, SingleTask) {
  // 只有一个任务，无法完成
  vector<int> tasks = {1};
  EXPECT_EQ(-1, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, MultipleSingleTasks) {
  // 多种难度，每种只有 1 个
  vector<int> tasks = {1, 2, 3, 4};
  EXPECT_EQ(-1, solution.minimumRounds(tasks));
}

TEST_P(MinimumRoundsToCompleteAllTasksTest, LargeInput) {
  // 大量相同任务，验证公式正确性
  vector<int> tasks(100000, 7);  // 100000 个相同任务
  // ceil(100000 / 3) = 33334
  EXPECT_EQ(33334, solution.minimumRounds(tasks));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumRoundsToCompleteAllTasksTest,
    ::testing::ValuesIn(MinimumRoundsToCompleteAllTasksSolution().getStrategyNames()));

}  // namespace problem_2244
}  // namespace leetcode
