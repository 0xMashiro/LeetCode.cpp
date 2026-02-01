#include "leetcode/problems/sort-items-by-groups-respecting-dependencies.h"

namespace leetcode {
namespace problem_1203 {

/**
 * 拓扑排序解法
 * 
 * 核心思想：
 * 1. 给无组的项目分配独立组（从 m 开始递增）
 * 2. 构建组间和组内的依赖图
 * 3. 先对组进行拓扑排序
 * 4. 再对每个组内的项目进行拓扑排序
 * 5. 按组顺序合并结果
 * 
 * 时间复杂度: O(n + e)，其中 e 是依赖边的数量
 * 空间复杂度: O(n + e)
 */
static vector<int> topologicalSortSolution(int n, int m, vector<int>& groupInput, vector<vector<int>>& beforeItems) {
  // 复制 group 数组，避免修改输入
  vector<int> group = groupInput;
  
  // Step 1: 为没有组的项目分配独立组
  int newGroupId = m;
  for (int i = 0; i < n; ++i) {
    if (group[i] == -1) {
      group[i] = newGroupId++;
    }
  }
  int totalGroups = newGroupId;
  
  // Step 2: 构建图和入度数组
  // 项目图
  vector<vector<int>> itemGraph(n);
  vector<int> itemInDegree(n, 0);
  // 组图
  vector<vector<int>> groupGraph(totalGroups);
  vector<int> groupInDegree(totalGroups, 0);
  
  // Step 3: 构建依赖关系
  for (int i = 0; i < n; ++i) {
    for (int before : beforeItems[i]) {
      // 项目 before 应该在项目 i 之前
      itemGraph[before].push_back(i);
      itemInDegree[i]++;
      
      // 如果属于不同组，添加组间依赖
      int groupBefore = group[before];
      int groupAfter = group[i];
      if (groupBefore != groupAfter) {
        groupGraph[groupBefore].push_back(groupAfter);
        groupInDegree[groupAfter]++;
      }
    }
  }
  
  // Step 4: 对组进行拓扑排序
  auto topologicalSort = [](vector<vector<int>>& graph, vector<int>& inDegree) -> vector<int> {
    vector<int> result;
    queue<int> q;
    int n = inDegree.size();
    
    for (int i = 0; i < n; ++i) {
      if (inDegree[i] == 0) {
        q.push(i);
      }
    }
    
    while (!q.empty()) {
      int u = q.front(); q.pop();
      result.push_back(u);
      for (int v : graph[u]) {
        if (--inDegree[v] == 0) {
          q.push(v);
        }
      }
    }
    
    return result.size() == n ? result : vector<int>();
  };
  
  vector<int> groupOrder = topologicalSort(groupGraph, groupInDegree);
  if (groupOrder.empty()) {
    return {};  // 组间有环
  }
  
  // Step 5: 对每个组内的项目进行拓扑排序
  // 按组收集项目
  vector<vector<int>> itemsInGroup(totalGroups);
  for (int i = 0; i < n; ++i) {
    itemsInGroup[group[i]].push_back(i);
  }
  
  // 构建组内的子图（从原图中筛选）
  vector<vector<int>> sortedItemsInGroup(totalGroups);
  for (int g : groupOrder) {
    // 提取该组的子图
    vector<int>& items = itemsInGroup[g];
    if (items.empty()) continue;
    
    // 构建组内的邻接表和入度
    unordered_map<int, vector<int>> localGraph;
    unordered_map<int, int> localInDegree;
    for (int item : items) {
      localInDegree[item] = 0;
    }
    
    for (int u : items) {
      for (int v : itemGraph[u]) {
        if (group[v] == g) {  // 只考虑同组内的边
          localGraph[u].push_back(v);
          localInDegree[v]++;
        }
      }
    }
    
    // 对该组进行拓扑排序
    queue<int> q;
    for (int item : items) {
      if (localInDegree[item] == 0) {
        q.push(item);
      }
    }
    
    vector<int> sorted;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      sorted.push_back(u);
      for (int v : localGraph[u]) {
        if (--localInDegree[v] == 0) {
          q.push(v);
        }
      }
    }
    
    if (sorted.size() != items.size()) {
      return {};  // 组内有环
    }
    
    sortedItemsInGroup[g] = sorted;
  }
  
  // Step 6: 按组顺序合并结果
  vector<int> result;
  for (int g : groupOrder) {
    for (int item : sortedItemsInGroup[g]) {
      result.push_back(item);
    }
  }
  
  return result;
}

SortItemsByGroupsRespectingDependenciesSolution::SortItemsByGroupsRespectingDependenciesSolution() {
  setMetaInfo({
    .id = 1203,
    .title = "Sort Items by Groups Respecting Dependencies",
    .url = "https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/"
  });
  registerStrategy("Topological Sort", topologicalSortSolution);
}

vector<int> SortItemsByGroupsRespectingDependenciesSolution::sortItems(
    int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
  return getSolution()(n, m, group, beforeItems);
}

}  // namespace problem_1203
}  // namespace leetcode
