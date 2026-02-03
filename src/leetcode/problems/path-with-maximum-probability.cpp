
#include "leetcode/problems/path-with-maximum-probability.h"

namespace leetcode {
namespace problem_1514 {

/**
 * 使用 Dijkstra 算法变体求解最大概率路径
 * 思路：将求"最短路径"改为求"最大概率路径"
 * - dist[i] 存储从起点到节点 i 的最大概率
 * - 使用最大堆（优先队列）每次扩展当前概率最大的节点
 * - 松弛操作：如果经过当前边能获得更大的概率，则更新
 * 时间复杂度: O((E + V) log V) = O(E log V)
 * 空间复杂度: O(V + E)
 */
static double solution1(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
  // 构建邻接表: graph[node] = list of {neighbor, probability}
  vector<vector<pair<int, double>>> graph(n);
  for (int i = 0; i < edges.size(); ++i) {
    int a = edges[i][0];
    int b = edges[i][1];
    double prob = succProb[i];
    graph[a].emplace_back(b, prob);
    graph[b].emplace_back(a, prob);  // 无向图
  }

  // dist[i] 表示从 start_node 到节点 i 的最大概率
  vector<double> dist(n, 0.0);
  dist[start_node] = 1.0;  // 起点到自身的概率为 1

  // 最大堆: {概率, 节点}，按概率从大到小排序
  priority_queue<pair<double, int>> pq;
  pq.push({1.0, start_node});

  while (!pq.empty()) {
    auto [currProb, u] = pq.top();
    pq.pop();

    // 如果当前概率小于记录的最大概率，跳过（已找到更优路径）
    if (currProb < dist[u]) continue;

    // 如果到达终点，可以直接返回（最大堆保证这是最大概率）
    if (u == end_node) return currProb;

    // 遍历邻居进行松弛
    for (auto& [v, edgeProb] : graph[u]) {
      double newProb = currProb * edgeProb;
      if (newProb > dist[v]) {
        dist[v] = newProb;
        pq.push({newProb, v});
      }
    }
  }

  // 如果没有到达 end_node，返回 0
  return 0.0;
}

PathWithMaximumProbabilitySolution::PathWithMaximumProbabilitySolution() {
  setMetaInfo({
    .id = 1514,
    .title = "Path with Maximum Probability",
    .url = "https://leetcode.com/problems/path-with-maximum-probability/"
  });
  registerStrategy("Dijkstra (Max Heap)", solution1);
}

double PathWithMaximumProbabilitySolution::maxProbability(
    int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
  return getSolution()(n, edges, succProb, start_node, end_node);
}

}  // namespace problem_1514
}  // namespace leetcode
