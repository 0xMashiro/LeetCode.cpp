
#include "leetcode/problems/count-the-number-of-complete-components.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2685 {

class CountTheNumberOfCompleteComponentsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheNumberOfCompleteComponentsSolution solution;
};

// Example 1: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// 三个连通分量: {0,1,2} 完全连通, {3,4} 完全连通, {5} 完全连通
// 输出: 3
TEST_P(CountTheNumberOfCompleteComponentsTest, Example1) {
  int n = 6;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};
  EXPECT_EQ(3, solution.countCompleteComponents(n, edges));
}

// Example 2: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
// 两个连通分量: {0,1,2} 完全连通, {3,4,5} 不是完全连通(缺少4-5边)
// 输出: 1
TEST_P(CountTheNumberOfCompleteComponentsTest, Example2) {
  int n = 6;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}};
  EXPECT_EQ(1, solution.countCompleteComponents(n, edges));
}

// 边界情况: n = 1, 没有边
TEST_P(CountTheNumberOfCompleteComponentsTest, SingleVertex) {
  int n = 1;
  vector<vector<int>> edges = {};
  EXPECT_EQ(1, solution.countCompleteComponents(n, edges));
}

// 边界情况: 没有边，所有顶点都是孤立的，每个都是完全连通分量
TEST_P(CountTheNumberOfCompleteComponentsTest, NoEdges) {
  int n = 5;
  vector<vector<int>> edges = {};
  EXPECT_EQ(5, solution.countCompleteComponents(n, edges));
}

// 完全图: 所有顶点都相互连接
TEST_P(CountTheNumberOfCompleteComponentsTest, CompleteGraph) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
  EXPECT_EQ(1, solution.countCompleteComponents(n, edges));
}

// 两个完全连通分量
TEST_P(CountTheNumberOfCompleteComponentsTest, TwoCompleteComponents) {
  int n = 5;
  vector<vector<int>> edges = {{0, 1}, {2, 3}, {2, 4}, {3, 4}};
  // {0,1} 是完全连通, {2,3,4} 是完全连通
  EXPECT_EQ(2, solution.countCompleteComponents(n, edges));
}

// 链状图: 不是完全连通
TEST_P(CountTheNumberOfCompleteComponentsTest, ChainGraph) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}};
  // 一个连通分量但不是完全连通
  EXPECT_EQ(0, solution.countCompleteComponents(n, edges));
}

// 星型图: 不是完全连通
TEST_P(CountTheNumberOfCompleteComponentsTest, StarGraph) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}};
  // 一个连通分量但不是完全连通
  EXPECT_EQ(0, solution.countCompleteComponents(n, edges));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountTheNumberOfCompleteComponentsTest,
    ::testing::ValuesIn(CountTheNumberOfCompleteComponentsSolution().getStrategyNames()));

}  // namespace problem_2685
}  // namespace leetcode
