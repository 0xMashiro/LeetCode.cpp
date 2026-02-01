#include "leetcode/problems/number-of-nodes-in-the-sub-tree-with-the-same-label.h"

namespace leetcode {
namespace problem_1519 {

// DFS + 计数数组合并
// 时间复杂度: O(26 * n) = O(n)
// 空间复杂度: O(26 * h) = O(h)，h 为树高
static vector<int> solution1(int n, vector<vector<int>>& edges, string labels) {
  // 构建邻接表
  vector<vector<int>> adj(n);
  for (auto& e : edges) {
    adj[e[0]].push_back(e[1]);
    adj[e[1]].push_back(e[0]);
  }

  vector<int> ans(n, 0);

  // DFS 返回以 u 为根的子树中各字母的出现次数
  function<array<int, 26>(int, int)> dfs = [&](int u, int parent) -> array<int, 26> {
    array<int, 26> cnt{};
    cnt.fill(0);

    // 递归处理所有子节点
    for (int v : adj[u]) {
      if (v != parent) {
        array<int, 26> child_cnt = dfs(v, u);
        for (int i = 0; i < 26; ++i) {
          cnt[i] += child_cnt[i];
        }
      }
    }

    // 当前节点标签计数 +1
    cnt[labels[u] - 'a']++;
    // 记录答案
    ans[u] = cnt[labels[u] - 'a'];

    return cnt;
  };

  dfs(0, -1);
  return ans;
}

NumberOfNodesInTheSubTreeWithTheSameLabelSolution::NumberOfNodesInTheSubTreeWithTheSameLabelSolution() {
  setMetaInfo({.id = 1519,
               .title = "Number of Nodes in the Sub-Tree With the Same Label",
               .url = "https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/"});
  registerStrategy("DFS + Count Array", solution1);
}

vector<int> NumberOfNodesInTheSubTreeWithTheSameLabelSolution::countSubTrees(
    int n, vector<vector<int>>& edges, string labels) {
  return getSolution()(n, edges, labels);
}

}  // namespace problem_1519
}  // namespace leetcode
