#include "leetcode/problems/minimum-processing-time.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2895 {

class MinimumProcessingTimeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumProcessingTimeSolution solution;
};

// 示例 1
TEST_P(MinimumProcessingTimeTest, Example1) {
  vector<int> processorTime = {8, 10};
  vector<int> tasks = {2, 2, 3, 1, 8, 7, 4, 5};
  EXPECT_EQ(16, solution.minProcessingTime(processorTime, tasks));
}

// 示例 2
TEST_P(MinimumProcessingTimeTest, Example2) {
  vector<int> processorTime = {10, 20};
  vector<int> tasks = {2, 3, 1, 2, 5, 8, 4, 3};
  EXPECT_EQ(23, solution.minProcessingTime(processorTime, tasks));
}

// 边界：单个处理器
TEST_P(MinimumProcessingTimeTest, SingleProcessor) {
  vector<int> processorTime = {5};
  vector<int> tasks = {1, 2, 3, 4};
  EXPECT_EQ(9, solution.minProcessingTime(processorTime, tasks));  // 5 + 4
}

// 边界：所有处理器同时可用
TEST_P(MinimumProcessingTimeTest, SameProcessorTime) {
  vector<int> processorTime = {0, 0};
  vector<int> tasks = {5, 4, 3, 2, 1, 2, 3, 4};
  EXPECT_EQ(5, solution.minProcessingTime(processorTime, tasks));  // 0 + 5
}

// 边界：处理器可用时间为 0
TEST_P(MinimumProcessingTimeTest, ZeroProcessorTime) {
  vector<int> processorTime = {0};
  vector<int> tasks = {1, 2, 3, 10};
  EXPECT_EQ(10, solution.minProcessingTime(processorTime, tasks));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumProcessingTimeTest,
    ::testing::ValuesIn(MinimumProcessingTimeSolution().getStrategyNames()));

}  // namespace problem_2895
}  // namespace leetcode
