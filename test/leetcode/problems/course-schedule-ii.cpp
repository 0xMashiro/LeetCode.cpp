#include "leetcode/problems/course-schedule-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_210 {

class CourseScheduleIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CourseScheduleIiSolution solution;
};

// 验证结果是否是一个合法的拓扑排序
static bool isValidOrder(int numCourses, 
                         const vector<vector<int>>& prerequisites,
                         const vector<int>& order) {
  if (order.size() != static_cast<size_t>(numCourses)) return false;
  
  // 检查是否包含所有课程
  vector<bool> seen(numCourses, false);
  for (int c : order) {
    if (c < 0 || c >= numCourses || seen[c]) return false;
    seen[c] = true;
  }
  
  // 检查先修关系是否满足
  vector<int> pos(numCourses);
  for (int i = 0; i < numCourses; ++i) {
    pos[order[i]] = i;
  }
  
  for (const auto& pre : prerequisites) {
    if (pos[pre[1]] >= pos[pre[0]]) return false;  // b 应该在 a 之前
  }
  
  return true;
}

TEST_P(CourseScheduleIiTest, Example1) {
  int numCourses = 2;
  vector<vector<int>> prerequisites = {{1, 0}};
  vector<int> result = solution.findOrder(numCourses, prerequisites);
  EXPECT_TRUE(isValidOrder(numCourses, prerequisites, result));
  // 验证输出是 [0, 1]
  vector<int> expected = {0, 1};
  EXPECT_EQ(expected, result);
}

TEST_P(CourseScheduleIiTest, Example2) {
  int numCourses = 4;
  vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
  vector<int> result = solution.findOrder(numCourses, prerequisites);
  EXPECT_TRUE(isValidOrder(numCourses, prerequisites, result));
}

TEST_P(CourseScheduleIiTest, Example3) {
  int numCourses = 1;
  vector<vector<int>> prerequisites = {};
  vector<int> result = solution.findOrder(numCourses, prerequisites);
  vector<int> expected = {0};
  EXPECT_EQ(expected, result);
}

TEST_P(CourseScheduleIiTest, CycleDetection) {
  // 存在环: 0 -> 1 -> 2 -> 0
  int numCourses = 3;
  vector<vector<int>> prerequisites = {{1, 0}, {2, 1}, {0, 2}};
  vector<int> result = solution.findOrder(numCourses, prerequisites);
  EXPECT_TRUE(result.empty());
}

TEST_P(CourseScheduleIiTest, NoPrerequisites) {
  int numCourses = 3;
  vector<vector<int>> prerequisites = {};
  vector<int> result = solution.findOrder(numCourses, prerequisites);
  EXPECT_TRUE(isValidOrder(numCourses, prerequisites, result));
  EXPECT_EQ(3, result.size());
}

TEST_P(CourseScheduleIiTest, LinearChain) {
  // 线性依赖: 0 -> 1 -> 2 -> 3
  int numCourses = 4;
  vector<vector<int>> prerequisites = {{1, 0}, {2, 1}, {3, 2}};
  vector<int> result = solution.findOrder(numCourses, prerequisites);
  EXPECT_TRUE(isValidOrder(numCourses, prerequisites, result));
  vector<int> expected = {0, 1, 2, 3};
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CourseScheduleIiTest,
    ::testing::ValuesIn(CourseScheduleIiSolution().getStrategyNames()));

}  // namespace problem_210
}  // namespace leetcode
