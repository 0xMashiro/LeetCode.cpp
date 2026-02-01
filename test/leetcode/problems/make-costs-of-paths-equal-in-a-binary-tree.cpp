#include "leetcode/problems/make-costs-of-paths-equal-in-a-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2673 {

class MakeCostsOfPathsEqualInABinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MakeCostsOfPathsEqualInABinaryTreeSolution solution;
};

// 示例 1：n = 7, cost = [1,5,2,2,3,3,1]
// 树的结构：
//        1(1)
//      /       \
//    2(5)      3(2)
//   /   \     /   \
//  4(2) 5(3) 6(3) 7(1)
// 
// 原始路径和：
// 1->2->4: 1+5+2 = 8
// 1->2->5: 1+5+3 = 9
// 1->3->6: 1+2+3 = 6
// 1->3->7: 1+2+1 = 4
// 
// 需要让所有路径和等于 9
// - 节点 4 增加 1 次（8->9）
// - 节点 6 增加 3 次（6->9）
// - 节点 7 增加 2 次（4->9，但这是通过增加节点 3 来实现的）
// 
// 实际上算法是：
// - 节点 2 的左右：max(2,3)=3，增加 1
// - 节点 3 的左右：max(3,1)=3，增加 2
// - 根节点 1 的左右：max(5+3, 2+3)=8，差值为 1，但左已经是 8，右是 5，增加 3
// 
// 等等，让我重新计算：
// cost[3] = 2, cost[4] = 3 -> max=3, inc=1, cost[1]=5+3=8
// cost[5] = 3, cost[6] = 1 -> max=3, inc=2, cost[2]=2+3=5
// cost[0] 的左右：8 和 5 -> max=8, inc=3
// 总增量 = 1+2+3 = 6
TEST_P(MakeCostsOfPathsEqualInABinaryTreeTest, Example1) {
  int n = 7;
  vector<int> cost = {1, 5, 2, 2, 3, 3, 1};
  EXPECT_EQ(6, solution.minIncrements(n, cost));
}

// 示例 2：n = 3, cost = [5,3,3]
// 树的结构：
//      1(5)
//     /    \
//   2(3)   3(3)
// 
// 路径和：5+3=8, 5+3=8，已经相等，不需要增加
TEST_P(MakeCostsOfPathsEqualInABinaryTreeTest, Example2) {
  int n = 3;
  vector<int> cost = {5, 3, 3};
  EXPECT_EQ(0, solution.minIncrements(n, cost));
}

// 边界情况：最小的树 n=3
TEST_P(MakeCostsOfPathsEqualInABinaryTreeTest, MinimumTree) {
  int n = 3;
  vector<int> cost = {1, 1, 1};
  EXPECT_EQ(0, solution.minIncrements(n, cost));
}

// 边界情况：较大的差异
TEST_P(MakeCostsOfPathsEqualInABinaryTreeTest, LargeDifference) {
  int n = 3;
  vector<int> cost = {1, 100, 1};
  // 左路径：1+100=101，右路径：1+1=2
  // 需要右路径增加 99
  EXPECT_EQ(99, solution.minIncrements(n, cost));
}

// 三层树，所有叶子相同
TEST_P(MakeCostsOfPathsEqualInABinaryTreeTest, ThreeLevelSameLeaves) {
  int n = 7;
  vector<int> cost = {1, 2, 2, 3, 3, 3, 3};
  // 路径：1+2+3=6, 1+2+3=6, 1+2+3=6, 1+2+3=6
  EXPECT_EQ(0, solution.minIncrements(n, cost));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MakeCostsOfPathsEqualInABinaryTreeTest,
    ::testing::ValuesIn(MakeCostsOfPathsEqualInABinaryTreeSolution().getStrategyNames()));

}  // namespace problem_2673
}  // namespace leetcode
