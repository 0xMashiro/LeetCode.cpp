#include "leetcode/problems/build-a-matrix-with-conditions.h"

namespace leetcode {
namespace problem_2392 {

/**
 * 拓扑排序（Kahn 算法）
 * 返回排序后的节点顺序，如果存在环则返回空数组
 */
static vector<int> topologicalSort(int k, const vector<vector<int>>& conditions) {
  vector<vector<int>> graph(k + 1);  // 邻接表，节点编号 1~k
  vector<int> inDegree(k + 1, 0);    // 入度数组
  
  // 构建图
  for (const auto& cond : conditions) {
    int u = cond[0];
    int v = cond[1];
    graph[u].push_back(v);
    inDegree[v]++;
  }
  
  // BFS 拓扑排序
  queue<int> q;
  for (int i = 1; i <= k; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }
  
  vector<int> result;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);
    
    for (int v : graph[u]) {
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }
  
  // 如果结果节点数不足 k，说明存在环
  if (result.size() != k) {
    return {};
  }
  
  return result;
}

/**
 * 构建满足行列条件的矩阵
 * 思路：分别对行条件和列条件进行拓扑排序，确定每个数字的位置
 * 时间复杂度: O(k + n + m)，其中 n、m 分别为两个条件数组的长度
 * 空间复杂度: O(k)
 */
static vector<vector<int>> solution1(int k, vector<vector<int>>& rowConditions, 
                                      vector<vector<int>>& colConditions) {
  // 对行条件进行拓扑排序
  vector<int> rowOrder = topologicalSort(k, rowConditions);
  if (rowOrder.empty()) {
    return {};  // 行约束有环
  }
  
  // 对列条件进行拓扑排序
  vector<int> colOrder = topologicalSort(k, colConditions);
  if (colOrder.empty()) {
    return {};  // 列约束有环
  }
  
  // 构建位置映射：数字 -> (行号, 列号)
  vector<int> rowPos(k + 1);  // 每个数字所在的行
  vector<int> colPos(k + 1);  // 每个数字所在的列
  
  for (int i = 0; i < k; ++i) {
    rowPos[rowOrder[i]] = i;
    colPos[colOrder[i]] = i;
  }
  
  // 构建 k×k 矩阵
  vector<vector<int>> matrix(k, vector<int>(k, 0));
  for (int num = 1; num <= k; ++num) {
    matrix[rowPos[num]][colPos[num]] = num;
  }
  
  return matrix;
}

BuildAMatrixWithConditionsSolution::BuildAMatrixWithConditionsSolution() {
  setMetaInfo({.id = 2392,
               .title = "Build a Matrix With Conditions",
               .url = "https://leetcode.com/problems/build-a-matrix-with-conditions/"});
  registerStrategy("Topological Sort", solution1);
}

vector<vector<int>> BuildAMatrixWithConditionsSolution::buildMatrix(
    int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
  return getSolution()(k, rowConditions, colConditions);
}

}  // namespace problem_2392
}  // namespace leetcode
