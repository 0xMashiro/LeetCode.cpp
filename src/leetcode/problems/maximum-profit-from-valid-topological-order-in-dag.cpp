#include "leetcode/problems/maximum-profit-from-valid-topological-order-in-dag.h"

namespace leetcode {
namespace problem_3530 {

// 本题结构唯一合理解为 Bitmask DP（n ≤ 22，2^n ≈ 4M，可行）
// 贪心（每步选可用节点中最小score）在一般DAG上不最优，因节点出边不同会影响后续可用集合。
// 枚举所有已处理节点集合mask，dp[mask] = 处理mask中节点的最大收益
// 状态转移：对每个未处理节点v，若其所有前驱都在mask中，可加入
// dp[mask | (1<<v)] = max(dp[mask|(1<<v)], dp[mask] + score[v] * (popcount(mask)+1))
// 时间复杂度 O(n * 2^n)，空间复杂度 O(2^n)
static int solution1(int n, vector<vector<int>>& edges, vector<int>& score) {
  // prereq[v] = 节点 v 的前驱集合（bitmask）
  vector<int> prereq(n, 0);
  for (auto& e : edges) {
    int u = e[0], v = e[1];
    prereq[v] |= (1 << u);
  }

  int totalMasks = 1 << n;
  vector<int> dp(totalMasks, -1);
  dp[0] = 0;
  int ans = 0;

  for (int mask = 0; mask < totalMasks; ++mask) {
    if (dp[mask] < 0) continue;
    int pos = __builtin_popcount(mask) + 1;  // 1-based position for next node
    for (int v = 0; v < n; ++v) {
      if (mask & (1 << v)) continue;          // already processed
      if ((prereq[v] & ~mask) != 0) continue; // not all prerequisites processed
      int nxt = mask | (1 << v);
      int val = dp[mask] + score[v] * pos;
      if (val > dp[nxt]) dp[nxt] = val;
    }
    if (dp[mask] > ans) ans = dp[mask];
  }

  return ans;
}

MaximumProfitFromValidTopologicalOrderInDagSolution::MaximumProfitFromValidTopologicalOrderInDagSolution() {
  setMetaInfo({
      .id = 3530,
      .title = "Maximum Profit from Valid Topological Order in DAG",
      .url = "https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag"
  });
  // 仅有一个合理解：Bitmask DP。贪心（min-heap）在一般DAG上不最优，故不注册。
  registerStrategy({.name = "Bitmask DP"}, solution1);
}

int MaximumProfitFromValidTopologicalOrderInDagSolution::maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
  return getSolution()(n, edges, score);
}

}  // namespace problem_3530
}  // namespace leetcode
