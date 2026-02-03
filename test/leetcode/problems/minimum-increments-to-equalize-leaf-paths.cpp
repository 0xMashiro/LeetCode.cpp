#include "leetcode/problems/minimum-increments-to-equalize-leaf-paths.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3593 {

class MinimumIncrementsToEqualizeLeafPathsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumIncrementsToEqualizeLeafPathsSolution solution;
};

// Example 1: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
// Path 0->1: 2+1=3, Path 0->2: 2+3=5
// Increase node 1 by 2 to make path 0->1 = 5
// Output: 1
TEST_P(MinimumIncrementsToEqualizeLeafPathsTest, Example1) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {0, 2}};
  vector<int> cost = {2, 1, 3};
  EXPECT_EQ(1, solution.minIncrease(n, edges, cost));
}

// Example 2: n = 3, edges = [[0,1],[1,2]], cost = [5,1,4]
// Only one root-to-leaf path: 0->1->2, score = 5+1+4=10
// Output: 0
TEST_P(MinimumIncrementsToEqualizeLeafPathsTest, Example2) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}};
  vector<int> cost = {5, 1, 4};
  EXPECT_EQ(0, solution.minIncrease(n, edges, cost));
}

// Example 3: n = 5, edges = [[0,4],[0,1],[1,2],[1,3]], cost = [3,4,1,1,7]
// Path 0->4: 3+7=10
// Path 0->1->2: 3+4+1=8
// Path 0->1->3: 3+4+1=8
// Increase node 1 by 2 to make paths equal to 10
// Output: 1
TEST_P(MinimumIncrementsToEqualizeLeafPathsTest, Example3) {
  int n = 5;
  vector<vector<int>> edges = {{0, 4}, {0, 1}, {1, 2}, {1, 3}};
  vector<int> cost = {3, 4, 1, 1, 7};
  EXPECT_EQ(1, solution.minIncrease(n, edges, cost));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumIncrementsToEqualizeLeafPathsTest,
    ::testing::ValuesIn(MinimumIncrementsToEqualizeLeafPathsSolution().getStrategyNames()));

}  // namespace problem_3593
}  // namespace leetcode