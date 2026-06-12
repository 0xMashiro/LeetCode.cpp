#include "leetcode/problems/number-of-ways-to-assign-edge-weights-ii.h"

namespace leetcode {
namespace problem_3559 {

const int MOD = 1e9 + 7;

// 朴素 LCA：逐级向上爬，每查询 O(n)
// 时间复杂度 O(n * q)，n,q ≤ 1e5 时会 TLE
// 展示最直接思路：先建树，对每个查询爬到同深度再一起爬
static vector<int> solution1(vector<vector<int>>& edges,
                             vector<vector<int>>& queries) {
  int n = edges.size() + 1;
  vector<vector<int>> adj(n + 1);
  for (auto& e : edges) {
    adj[e[0]].push_back(e[1]);
    adj[e[1]].push_back(e[0]);
  }

  // DFS 求 parent 和 depth
  vector<int> parent(n + 1, 0), depth(n + 1, 0);
  function<void(int, int)> dfs = [&](int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
      if (v == p) continue;
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  };
  dfs(1, 0);

  // 预计算 2 的幂
  vector<long long> pow2(n + 1);
  pow2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow2[i] = (pow2[i - 1] * 2) % MOD;
  }

  // 朴素 LCA：沿 parent 逐级向上
  auto lca = [&](int u, int v) -> int {
    while (depth[u] > depth[v]) u = parent[u];
    while (depth[v] > depth[u]) v = parent[v];
    while (u != v) {
      u = parent[u];
      v = parent[v];
    }
    return u;
  };

  vector<int> ans;
  ans.reserve(queries.size());
  for (auto& q : queries) {
    int u = q[0], v = q[1];
    if (u == v) {
      ans.push_back(0);
      continue;
    }
    int l = lca(u, v);
    int L = depth[u] + depth[v] - 2 * depth[l];
    ans.push_back(static_cast<int>(pow2[L - 1]));
  }
  return ans;
}

// 二进制提升 LCA：最优解
// 预处理 O(n log n)，每次查询 O(log n)，总复杂度 O((n + q) log n)
// 利用数学结论：路径长度 L 时答案 = 2^(L-1) mod MOD
static vector<int> solution2(vector<vector<int>>& edges,
                             vector<vector<int>>& queries) {
  int n = edges.size() + 1;
  vector<vector<int>> adj(n + 1);
  for (auto& e : edges) {
    adj[e[0]].push_back(e[1]);
    adj[e[1]].push_back(e[0]);
  }

  const int LOG = 17;  // 2^17 = 131072 > 1e5
  vector<int> depth(n + 1, 0);
  vector<vector<int>> up(LOG, vector<int>(n + 1, 0));

  // DFS 构建二进制提升表
  function<void(int, int)> dfs = [&](int u, int p) {
    up[0][u] = p;
    for (int k = 1; k < LOG; ++k) {
      up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
      if (v == p) continue;
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  };
  dfs(1, 0);

  // 预计算 2 的幂
  vector<long long> pow2(n + 1);
  pow2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow2[i] = (pow2[i - 1] * 2) % MOD;
  }

  // 二进制提升求 LCA
  auto lca = [&](int u, int v) -> int {
    if (depth[u] < depth[v]) swap(u, v);
    // 将 u 提升到与 v 同深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; ++k) {
      if (diff & (1 << k)) u = up[k][u];
    }
    if (u == v) return u;
    // 从高到低一起提升
    for (int k = LOG - 1; k >= 0; --k) {
      if (up[k][u] != up[k][v]) {
        u = up[k][u];
        v = up[k][v];
      }
    }
    return up[0][u];
  };

  vector<int> ans;
  ans.reserve(queries.size());
  for (auto& q : queries) {
    int u = q[0], v = q[1];
    if (u == v) {
      ans.push_back(0);
      continue;
    }
    int l = lca(u, v);
    int L = depth[u] + depth[v] - 2 * depth[l];
    ans.push_back(static_cast<int>(pow2[L - 1]));
  }
  return ans;
}

NumberOfWaysToAssignEdgeWeightsIiSolution::
    NumberOfWaysToAssignEdgeWeightsIiSolution() {
  setMetaInfo({.id = 3559,
               .title = "Number of Ways to Assign Edge Weights II",
               .url = "https://leetcode.com/problems/"
                      "number-of-ways-to-assign-edge-weights-ii/"});
  registerStrategy(
      {.name = "Brute Force LCA",
       .expected = "Time Limit Exceeded",
       .time_complexity = "O(nq)",
       .space_complexity = "O(n)",
       .tags = {"tree", "lca", "oracle"},
       .notes = "Small-input oracle; expected to TLE on full constraints."},
      solution1);
  registerStrategy(
      {.name = "Binary Lifting LCA",
       .expected = "Accepted",
       .time_complexity = "O((n+q)logn)",
       .space_complexity = "O(nlogn)",
       .tags = {"tree", "lca", "binary-lifting", "combinatorics"},
       .notes = "Use distance(u,v) and 2^(dist-1) for non-empty paths."},
      solution2);
}

vector<int> NumberOfWaysToAssignEdgeWeightsIiSolution::assignEdgeWeights(
    vector<vector<int>>& edges, vector<vector<int>>& queries) {
  return getSolution()(edges, queries);
}

}  // namespace problem_3559
}  // namespace leetcode
