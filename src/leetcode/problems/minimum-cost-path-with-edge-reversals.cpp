#include "leetcode/problems/minimum-cost-path-with-edge-reversals.h"

namespace leetcode {
namespace problem_3650 {

// 策略1：状态图 + Dijkstra（支持最多多次开关使用）
// 思路：状态 (u, c) 表示当前在节点 u，已经使用了 c 次开关
// 从状态 (u, c) 可以：
//   1. 走正向边到 (v, c)，代价 w
//   2. 选择一条进入边 (v, u, w)，反转后立即走到 v，状态变为 (v, c+1)，代价 2*w
// 使用 Dijkstra 求 (0, 0) 到 (n-1, *) 的最小代价
// 限制最大使用开关次数为 MAX_SWITCH，因为边权为正，实际使用次数不会太多
// 时间复杂度：O((n + edges) * MAX_SWITCH * log n)，空间复杂度：O(n * MAX_SWITCH)
static int solution1(int n, vector<vector<int>>& edges) {
  // 最大允许使用开关次数，设为 100 应该足够（因为反转代价较高，且 n 最大 50000）
  const int MAX_SWITCH = 100;
  // 但为了安全，不能超过 n
  const int max_switch = min(MAX_SWITCH, n);
  
  // 构建正向邻接表和反向邻接表
  vector<vector<pair<int, int>>> adj(n);
  vector<vector<pair<int, int>>> rev(n);
  for (const auto& e : edges) {
    int u = e[0], v = e[1], w = e[2];
    adj[u].emplace_back(v, w);
    rev[v].emplace_back(u, w);  // 边 v->u 是进入边
  }

  const long long INF = 1e18;
  // dist[c][u]
  vector<vector<long long>> dist(max_switch + 1, vector<long long>(n, INF));
  dist[0][0] = 0;

  // 优先队列：(距离, 节点, 已使用开关次数)
  using State = tuple<long long, int, int>;
  priority_queue<State, vector<State>, greater<State>> pq;
  pq.emplace(0, 0, 0);

  while (!pq.empty()) {
    auto [d, u, c] = pq.top();
    pq.pop();
    if (d > dist[c][u]) continue;

    // 1. 走正向边，使用开关次数不变
    for (const auto& [v, w] : adj[u]) {
      long long nd = d + w;
      if (nd < dist[c][v]) {
        dist[c][v] = nd;
        pq.emplace(nd, v, c);
      }
    }
    // 2. 如果还可以使用开关，考虑反转操作
    if (c < max_switch) {
      for (const auto& [v, w] : rev[u]) {
        long long nd = d + 2 * w;
        if (nd < dist[c + 1][v]) {
          dist[c + 1][v] = nd;
          pq.emplace(nd, v, c + 1);
        }
      }
    }
  }

  long long ans = INF;
  for (int c = 0; c <= max_switch; ++c) {
    ans = min(ans, dist[c][n - 1]);
  }
  return ans == INF ? -1 : (int)ans;
}

MinimumCostPathWithEdgeReversalsSolution::MinimumCostPathWithEdgeReversalsSolution() {
  setMetaInfo({.id = 3650,
               .title = "Minimum Cost Path with Edge Reversals",
               .url = "https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/"});
  registerStrategy("State Graph + Dijkstra (up to 100 switches)", solution1);
}

int MinimumCostPathWithEdgeReversalsSolution::minCost(int n, vector<vector<int>>& edges) {
  return getSolution()(n, edges);
}

}  // namespace problem_3650
}  // namespace leetcode