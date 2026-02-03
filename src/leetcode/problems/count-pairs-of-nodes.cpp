#include "leetcode/problems/count-pairs-of-nodes.h"

namespace leetcode {
namespace problem_1782 {

// 双指针 + 哈希表处理重边
// 时间复杂度: O((n + m) log n + m * q), 空间复杂度: O(n + m)
// 其中 n 是节点数，m 是边数，q 是查询数
static vector<int> solution1(int n, vector<vector<int>>& edges, vector<int>& queries) {
  vector<int> degree(n + 1, 0);  // 节点编号 1~n
  unordered_map<long long, int> edgeCount;  // 记录重边数量
  
  // 计算每个节点的度数，同时统计重边
  for (const auto& e : edges) {
    int u = e[0], v = e[1];
    degree[u]++;
    degree[v]++;
    // 用编码表示边 (min, max) 确保唯一性
    long long key = (long long)min(u, v) * 20001 + max(u, v);
    edgeCount[key]++;
  }
  
  // 复制度数数组用于排序（只取 1~n）
  vector<int> sortedDegree(degree.begin() + 1, degree.end());
  sort(sortedDegree.begin(), sortedDegree.end());
  
  vector<int> ans;
  int qSize = queries.size();
  
  for (int q : queries) {
    long long count = 0;
    // 双指针统计满足 degree[a] + degree[b] > q 的节点对数量
    int left = 0, right = n - 1;
    while (left < right) {
      if (sortedDegree[left] + sortedDegree[right] > q) {
        // 如果 sortedDegree[left] + sortedDegree[right] > q
        // 那么对于固定的 right，所有 left 到 right-1 的节点都满足条件
        count += (right - left);
        right--;
      } else {
        left++;
      }
    }
    
    // 修正重边的影响
    // 对于每对有重边的节点 (u, v)，如果 degree[u] + degree[v] > q 但
    // degree[u] + degree[v] - common_edges(u,v) <= q，需要减 1
    for (const auto& [key, cnt] : edgeCount) {
      int u = key / 20001;
      int v = key % 20001;
      // 原来度数之和
      int sumDegree = degree[u] + degree[v];
      // 实际的 incident
      int actual = sumDegree - cnt;
      // 如果原来算进了答案但实际不该算进，需要减 1
      if (sumDegree > q && actual <= q) {
        count--;
      }
    }
    
    ans.push_back((int)count);
  }
  
  return ans;
}

CountPairsOfNodesSolution::CountPairsOfNodesSolution() {
  setMetaInfo({.id = 1782,
               .title = "Count Pairs Of Nodes",
               .url = "https://leetcode.com/problems/count-pairs-of-nodes/"});
  registerStrategy("Two Pointers + Hash Map", solution1);
}

vector<int> CountPairsOfNodesSolution::countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
  return getSolution()(n, edges, queries);
}

}  // namespace problem_1782
}  // namespace leetcode
