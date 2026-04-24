#include "leetcode/problems/parallel-courses-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1494 {

class ParallelCoursesIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ParallelCoursesIiSolution solution;
};

TEST_P(ParallelCoursesIiTest, Example1) {
  int n = 4;
  vector<vector<int>> relations = {{2, 1}, {3, 1}, {1, 4}};
  int k = 2;
  int expected = 3;
  EXPECT_EQ(expected, solution.minNumberOfSemesters(n, relations, k));
}

TEST_P(ParallelCoursesIiTest, Example2) {
  int n = 5;
  vector<vector<int>> relations = {{2, 1}, {3, 1}, {4, 1}, {1, 5}};
  int k = 2;
  int expected = 4;
  EXPECT_EQ(expected, solution.minNumberOfSemesters(n, relations, k));
}

TEST_P(ParallelCoursesIiTest, Example3) {
  int n = 11;
  vector<vector<int>> relations = {};
  int k = 2;
  int expected = 6;
  EXPECT_EQ(expected, solution.minNumberOfSemesters(n, relations, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ParallelCoursesIiTest,
    ::testing::ValuesIn(ParallelCoursesIiSolution().getStrategyNames()));

}  // namespace problem_1494
}  // namespace leetcode
