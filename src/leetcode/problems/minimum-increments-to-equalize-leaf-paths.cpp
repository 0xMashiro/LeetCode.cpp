#include "leetcode/problems/minimum-increments-to-equalize-leaf-paths.h"

namespace leetcode {
namespace problem_3593 {

class Solution {
 public:
  int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
    // 构建邻接表
    vector<vector<int>> adj(n);
    for (const auto& edge : edges) {
      int u = edge[0], v = edge[1];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    
    this->cost = cost;
    // DFS 从根节点 0 开始，父节点设为 -1
    auto result = dfs(0, -1, adj);
    return result.second;  // 返回最小修改次数
  }

 private:
  vector<int> cost;
  
  // 返回 pair<从当前节点到叶子的最大路径和, 最小修改次数>
  pair<long long, int> dfs(int u, int parent, const vector<vector<int>>& adj) {
    // 如果是叶子节点（没有子节点，除了父节点）
    bool isLeaf = true;
    for (int v : adj[u]) {
      if (v != parent) {
        isLeaf = false;
        break;
      }
    }
    
    if (isLeaf) {
      return {cost[u], 0};
    }
    
    // 收集所有子节点的结果
    vector<long long> childPathSums;
    int totalIncrements = 0;
    
    for (int v : adj[u]) {
      if (v != parent) {
        auto [pathSum, increments] = dfs(v, u, adj);
        childPathSums.push_back(pathSum);
        totalIncrements += increments;
      }
    }
    
    // 找到子节点中的最大路径和
    long long maxVal = *max_element(childPathSums.begin(), childPathSums.end());
    
    // 统计需要修改的子树数量（路径和小于最大值的子树）
    int needsIncrement = 0;
    for (long long sum : childPathSums) {
      if (sum < maxVal) {
        needsIncrement++;
      }
    }
    
    // 从当前节点到叶子的最大路径和 = cost[u] + 子节点中的最大路径和
    long long maxPathSum = cost[u] + maxVal;
    // 总修改次数 = 所有子树的修改次数之和 + 需要额外修改的子树数量
    totalIncrements += needsIncrement;
    
    return {maxPathSum, totalIncrements};
  }
};

static int solution1(int n, vector<vector<int>>& edges, vector<int>& cost) {
  Solution sol;
  return sol.minIncrease(n, edges, cost);
}

MinimumIncrementsToEqualizeLeafPathsSolution::MinimumIncrementsToEqualizeLeafPathsSolution() {
  setMetaInfo({.id = 3593,
               .title = "Minimum Increments to Equalize Leaf Paths",
               .url = "https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/"});
  registerStrategy("DFS Bottom-up", solution1);
}

int MinimumIncrementsToEqualizeLeafPathsSolution::minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
  return getSolution()(n, edges, cost);
}

}  // namespace problem_3593
}  // namespace leetcode