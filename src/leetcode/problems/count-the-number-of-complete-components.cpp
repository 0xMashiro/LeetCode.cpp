
#include "leetcode/problems/count-the-number-of-complete-components.h"

namespace leetcode {
namespace problem_2685 {

// 并查集实现
class UnionFind {
 public:
  UnionFind(int n) : parent(n), size(n, 1) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
  }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      if (size[rootX] < size[rootY]) {
        swap(rootX, rootY);
      }
      parent[rootY] = rootX;
      size[rootX] += size[rootY];
    }
  }

  int getSize(int x) {
    return size[find(x)];
  }

 private:
  vector<int> parent;
  vector<int> size;
};

// 使用并查集找出连通分量，然后检查每个分量是否为完全连通
// 时间复杂度: O(n + edges.length * α(n))，空间复杂度: O(n)
static int solution1(int n, vector<vector<int>>& edges) {
  UnionFind uf(n);
  
  // 统计每个顶点的度数
  vector<int> degree(n, 0);
  
  // 合并连通分量
  for (const auto& edge : edges) {
    int u = edge[0];
    int v = edge[1];
    uf.unite(u, v);
    degree[u]++;
    degree[v]++;
  }
  
  // 按根节点分组，统计每个连通分量的顶点数和边数
  unordered_map<int, pair<int, int>> components;  // root -> {vertexCount, edgeCount}
  
  for (int i = 0; i < n; ++i) {
    int root = uf.find(i);
    if (components.find(root) == components.end()) {
      components[root] = {0, 0};
    }
    components[root].first++;  // 顶点数
  }
  
  // 统计边数（注意每条边被两个顶点各统计一次，所以要除以2）
  for (int i = 0; i < n; ++i) {
    int root = uf.find(i);
    components[root].second += degree[i];  // 累加度数
  }
  
  // 检查每个连通分量是否为完全连通
  int completeCount = 0;
  for (const auto& [root, info] : components) {
    int vertexCount = info.first;
    int edgeCount = info.second / 2;  // 度数之和 = 2 * 边数
    // 完全连通分量需要边数 = vertexCount * (vertexCount - 1) / 2
    if (edgeCount == vertexCount * (vertexCount - 1) / 2) {
      completeCount++;
    }
  }
  
  return completeCount;
}

// DFS/BFS 替代方案
// 时间复杂度: O(n + edges.length)，空间复杂度: O(n)
static int solution2(int n, vector<vector<int>>& edges) {
  // 构建邻接表
  vector<vector<int>> adj(n);
  for (const auto& edge : edges) {
    adj[edge[0]].push_back(edge[1]);
    adj[edge[1]].push_back(edge[0]);
  }
  
  vector<bool> visited(n, false);
  int completeCount = 0;
  
  function<pair<int, int>(int)> dfs = [&](int u) -> pair<int, int> {
    visited[u] = true;
    int vertices = 1;
    int edgeCount = adj[u].size();
    
    for (int v : adj[u]) {
      if (!visited[v]) {
        auto [subVertices, subEdges] = dfs(v);
        vertices += subVertices;
        edgeCount += subEdges;
      }
    }
    
    return {vertices, edgeCount};
  };
  
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      auto [vertexCount, edgeCount] = dfs(i);
      // edgeCount 是度数之和，需要除以2得到实际边数
      edgeCount /= 2;
      // 完全连通分量需要边数 = vertexCount * (vertexCount - 1) / 2
      if (edgeCount == vertexCount * (vertexCount - 1) / 2) {
        completeCount++;
      }
    }
  }
  
  return completeCount;
}

CountTheNumberOfCompleteComponentsSolution::CountTheNumberOfCompleteComponentsSolution() {
  setMetaInfo({.id = 2685,
               .title = "Count the Number of Complete Components",
               .url = "https://leetcode.com/problems/count-the-number-of-complete-components/"});
  registerStrategy("Union-Find", solution1);
  registerStrategy("DFS", solution2);
}

int CountTheNumberOfCompleteComponentsSolution::countCompleteComponents(int n, vector<vector<int>>& edges) {
  return getSolution()(n, edges);
}

}  // namespace problem_2685
}  // namespace leetcode
