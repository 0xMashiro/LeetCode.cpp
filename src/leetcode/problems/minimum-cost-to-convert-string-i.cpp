#include "leetcode/problems/minimum-cost-to-convert-string-i.h"

namespace leetcode {
namespace problem_2976 {

// 策略1：Floyd-Warshall 算法计算所有字符对之间的最小转换成本
// 时间复杂度：O(26^3 + n + m)，其中 n 是 source 长度，m 是转换规则数量
// 空间复杂度：O(26^2) = O(1)
static long long solution1(string source, string target,
                          vector<char>& original, vector<char>& changed,
                          vector<int>& cost) {
  const long long INF = 1e18;
  const int ALPHABET = 26;
  vector<vector<long long>> dist(ALPHABET, vector<long long>(ALPHABET, INF));
  
  // 初始化对角线为 0（相同字符转换成本为 0）
  for (int i = 0; i < ALPHABET; ++i) {
    dist[i][i] = 0;
  }
  
  // 根据给定的转换规则更新直接转换成本
  int m = original.size();
  for (int i = 0; i < m; ++i) {
    int u = original[i] - 'a';
    int v = changed[i] - 'a';
    long long w = cost[i];
    if (w < dist[u][v]) {
      dist[u][v] = w;
    }
  }
  
  // Floyd-Warshall 算法计算所有对最短路径
  for (int k = 0; k < ALPHABET; ++k) {
    for (int i = 0; i < ALPHABET; ++i) {
      if (dist[i][k] == INF) continue;
      for (int j = 0; j < ALPHABET; ++j) {
        if (dist[k][j] == INF) continue;
        long long newDist = dist[i][k] + dist[k][j];
        if (newDist < dist[i][j]) {
          dist[i][j] = newDist;
        }
      }
    }
  }
  
  // 计算将 source 转换为 target 的总成本
  long long totalCost = 0;
  int n = source.size();
  for (int i = 0; i < n; ++i) {
    if (source[i] == target[i]) {
      continue;
    }
    int u = source[i] - 'a';
    int v = target[i] - 'a';
    if (dist[u][v] == INF) {
      return -1;
    }
    totalCost += dist[u][v];
  }
  return totalCost;
}

// 策略2：对每个字符运行 Dijkstra 算法
// 时间复杂度：O(26 * (26 log 26 + m)) + O(n)
// 空间复杂度：O(26^2 + m)
static long long solution2(string source, string target,
                          vector<char>& original, vector<char>& changed,
                          vector<int>& cost) {
  const long long INF = 1e18;
  const int ALPHABET = 26;
  
  // 构建邻接表
  vector<vector<pair<int, long long>>> adj(ALPHABET);
  int m = original.size();
  for (int i = 0; i < m; ++i) {
    int u = original[i] - 'a';
    int v = changed[i] - 'a';
    long long w = cost[i];
    adj[u].emplace_back(v, w);
  }
  
  // 预计算所有字符对的最短距离
  vector<vector<long long>> dist(ALPHABET, vector<long long>(ALPHABET, INF));
  
  // 对每个字符运行 Dijkstra 算法
  for (int start = 0; start < ALPHABET; ++start) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[start][start] = 0;
    pq.emplace(0, start);
    
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      
      if (d != dist[start][u]) continue;
      
      for (auto& [v, w] : adj[u]) {
        long long newDist = d + w;
        if (newDist < dist[start][v]) {
          dist[start][v] = newDist;
          pq.emplace(newDist, v);
        }
      }
    }
  }
  
  // 计算总成本
  long long totalCost = 0;
  int n = source.size();
  for (int i = 0; i < n; ++i) {
    if (source[i] == target[i]) {
      continue;
    }
    int u = source[i] - 'a';
    int v = target[i] - 'a';
    if (dist[u][v] == INF) {
      return -1;
    }
    totalCost += dist[u][v];
  }
  return totalCost;
}

MinimumCostToConvertStringISolution::MinimumCostToConvertStringISolution() {
  setMetaInfo({.id = 2976,
               .title = "Minimum Cost to Convert String I",
               .url = "https://leetcode.com/problems/minimum-cost-to-convert-string-i/"});
  registerStrategy("Floyd-Warshall", solution1);
  registerStrategy("Dijkstra per character", solution2);
}

long long MinimumCostToConvertStringISolution::minimumCost(
    string source, string target,
    vector<char>& original, vector<char>& changed,
    vector<int>& cost) {
  return getSolution()(source, target, original, changed, cost);
}

}  // namespace problem_2976
}  // namespace leetcode