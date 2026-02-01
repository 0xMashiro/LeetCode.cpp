
#include "leetcode/problems/minimize-the-total-price-of-the-trips.h"

namespace leetcode {
namespace problem_2646 {

class Solution {
 public:
  int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
    // 构建邻接表
    vector<vector<int>> adj(n);
    for (auto& e : edges) {
      adj[e[0]].push_back(e[1]);
      adj[e[1]].push_back(e[0]);
    }
    
    // cnt[i] 表示节点 i 在所有 trips 中被经过的次数
    vector<int> cnt(n, 0);
    
    // 对于每个 trip，统计路径上每个节点被经过的次数
    for (auto& trip : trips) {
      int start = trip[0], end = trip[1];
      vector<int> path;
      vector<bool> visited(n, false);
      // DFS 找路径
      findPath(start, end, adj, visited, path);
      // 路径上的节点计数 +1
      for (int node : path) {
        cnt[node]++;
      }
    }
    
    // 树形 DP
    // dp[u][0]: 节点 u 不减半时的最小成本
    // dp[u][1]: 节点 u 减半时的最小成本
    vector<vector<int>> dp(n, vector<int>(2, 0));
    vector<bool> visited(n, false);
    
    // 以 0 为根进行 DFS
    dfs(0, adj, cnt, price, visited, dp);
    
    return min(dp[0][0], dp[0][1]);
  }
  
 private:
  // DFS 找从 start 到 end 的路径
  bool findPath(int u, int target, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& path) {
    visited[u] = true;
    path.push_back(u);
    
    if (u == target) {
      return true;
    }
    
    for (int v : adj[u]) {
      if (!visited[v]) {
        if (findPath(v, target, adj, visited, path)) {
          return true;
        }
      }
    }
    
    path.pop_back();
    return false;
  }
  
  // 树形 DP
  void dfs(int u, vector<vector<int>>& adj, vector<int>& cnt, vector<int>& price, 
           vector<bool>& visited, vector<vector<int>>& dp) {
    visited[u] = true;
    
    // 当前节点的成本贡献
    // 不减半: cnt[u] * price[u]
    // 减半: cnt[u] * price[u] / 2
    int fullCost = cnt[u] * price[u];
    int halfCost = cnt[u] * price[u] / 2;
    
    dp[u][0] = fullCost;
    dp[u][1] = halfCost;
    
    for (int v : adj[u]) {
      if (!visited[v]) {
        dfs(v, adj, cnt, price, visited, dp);
        // u 不减半，v 可以减半也可以不减半，取最小值
        dp[u][0] += min(dp[v][0], dp[v][1]);
        // u 减半，v 不能减半
        dp[u][1] += dp[v][0];
      }
    }
  }
};

static int solution1(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
  Solution sol;
  return sol.minimumTotalPrice(n, edges, price, trips);
}

MinimizeTheTotalPriceOfTheTripsSolution::MinimizeTheTotalPriceOfTheTripsSolution() {
  setMetaInfo({.id = 2646,
               .title = "Minimize the Total Price of the Trips",
               .url = "https://leetcode.com/problems/minimize-the-total-price-of-the-trips/"});
  registerStrategy("Tree DP", solution1);
}

int MinimizeTheTotalPriceOfTheTripsSolution::minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
  return getSolution()(n, edges, price, trips);
}

}  // namespace problem_2646
}  // namespace leetcode
