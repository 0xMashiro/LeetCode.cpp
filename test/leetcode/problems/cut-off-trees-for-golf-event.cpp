#include "leetcode/problems/cut-off-trees-for-golf-event.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_675 {

class CutOffTreesForGolfEventTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CutOffTreesForGolfEventSolution solution;
};

TEST_P(CutOffTreesForGolfEventTest, Example1) {
  vector<vector<int>> forest = {{1, 2, 3}, {0, 0, 4}, {7, 6, 5}};
  EXPECT_EQ(6, solution.cutOffTree(forest));
}

TEST_P(CutOffTreesForGolfEventTest, Example2) {
  vector<vector<int>> forest = {{1, 2, 3}, {0, 0, 0}, {7, 6, 5}};
  EXPECT_EQ(-1, solution.cutOffTree(forest));
}

TEST_P(CutOffTreesForGolfEventTest, Example3) {
  vector<vector<int>> forest = {{2, 3, 4}, {0, 0, 5}, {8, 7, 6}};
  EXPECT_EQ(6, solution.cutOffTree(forest));
}

TEST_P(CutOffTreesForGolfEventTest, SingleTree) {
  vector<vector<int>> forest = {{1, 1}, {1, 2}};
  EXPECT_EQ(2, solution.cutOffTree(forest));  // (0,0)->(0,1)->(1,1) 或 (0,0)->(1,0)->(1,1)
}

TEST_P(CutOffTreesForGolfEventTest, BlockedStart) {
  vector<vector<int>> forest = {{0, 1}, {1, 2}};
  EXPECT_EQ(-1, solution.cutOffTree(forest));
}

TEST_P(CutOffTreesForGolfEventTest, NoTrees) {
  vector<vector<int>> forest = {{1, 1}, {1, 1}};
  EXPECT_EQ(0, solution.cutOffTree(forest));  // 没有树需要砍
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CutOffTreesForGolfEventTest,
    ::testing::ValuesIn(CutOffTreesForGolfEventSolution().getStrategyNames()));

}  // namespace problem_675
}  // namespace leetcode
