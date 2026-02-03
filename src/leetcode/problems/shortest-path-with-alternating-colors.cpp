
#include "leetcode/problems/shortest-path-with-alternating-colors.h"

namespace leetcode {
namespace problem_1129 {

// BFS 解法：状态为 (当前节点, 最后经过的边颜色)
// dist[node][0] 表示通过红色边到达该节点的最短距离
// dist[node][1] 表示通过蓝色边到达该节点的最短距离
static vector<int> solution1(int n, vector<vector<int>>& redEdges, 
                              vector<vector<int>>& blueEdges) {
  // 构建邻接表：adj[0] 表示红色边的邻接表，adj[1] 表示蓝色边的邻接表
  vector<vector<vector<int>>> adj(2, vector<vector<int>>(n));
  for (auto& edge : redEdges) {
    adj[0][edge[0]].push_back(edge[1]);
  }
  for (auto& edge : blueEdges) {
    adj[1][edge[0]].push_back(edge[1]);
  }
  
  const int INF = 1e9;
  // dist[node][0] 通过红边到达该节点的距离，dist[node][1] 通过蓝边到达
  vector<vector<int>> dist(n, vector<int>(2, INF));
  
  // BFS 队列：存储 (节点, 最后边的颜色)
  // 起始状态：可以从节点 0 出发，使用任意颜色，所以初始化为 0
  queue<pair<int, int>> q;
  dist[0][0] = 0;
  dist[0][1] = 0;
  q.push({0, 0});  // 通过红边到达节点 0（虚拟）
  q.push({0, 1});  // 通过蓝边到达节点 0（虚拟）
  
  while (!q.empty()) {
    auto [u, lastColor] = q.front();
    q.pop();
    int nextColor = 1 - lastColor;  // 下一个必须是相反颜色
    
    for (int v : adj[nextColor][u]) {
      if (dist[v][nextColor] == INF) {
        dist[v][nextColor] = dist[u][lastColor] + 1;
        q.push({v, nextColor});
      }
    }
  }
  
  vector<int> answer(n);
  for (int i = 0; i < n; ++i) {
    int minDist = min(dist[i][0], dist[i][1]);
    answer[i] = (minDist == INF) ? -1 : minDist;
  }
  
  return answer;
}

ShortestPathWithAlternatingColorsSolution::ShortestPathWithAlternatingColorsSolution() {
  setMetaInfo({.id = 1129,
               .title = "Shortest Path with Alternating Colors",
               .url = "https://leetcode.com/problems/shortest-path-with-alternating-colors/"});
  registerStrategy("BFS", solution1);
}

vector<int> ShortestPathWithAlternatingColorsSolution::shortestAlternatingPaths(
    int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
  return getSolution()(n, redEdges, blueEdges);
}

}  // namespace problem_1129
}  // namespace leetcode
