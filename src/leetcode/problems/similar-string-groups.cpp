#include "leetcode/problems/similar-string-groups.h"

namespace leetcode {
namespace problem_839 {

/**
 * 并查集（Union-Find）数据结构
 * 支持路径压缩和按秩合并
 */
class UnionFind {
 public:
  UnionFind(int n) : parent(n), rank(n, 0), count(n) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  // 查找根节点（路径压缩）
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  // 合并两个集合
  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;

    // 按秩合并
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
    count--;
  }

  // 获取连通分量数量
  int getCount() const { return count; }

 private:
  vector<int> parent;
  vector<int> rank;
  int count;
};

/**
 * 判断两个字符串是否相似
 * 相似定义：相同或最多两个位置字符不同
 * 题目保证所有字符串互为字谜，所以不需要检查字符组成
 */
static bool isSimilar(const string& a, const string& b) {
  int diff = 0;
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) {
      diff++;
      if (diff > 2) return false;
    }
  }
  return true;
}

/**
 * 使用并查集求解
 * 时间复杂度：O(n² × m)，其中 n 是字符串数量，m 是字符串长度
 * 空间复杂度：O(n)
 */
static int solutionUnionFind(vector<string>& strs) {
  int n = strs.size();
  UnionFind uf(n);

  // 比较所有字符串对
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (isSimilar(strs[i], strs[j])) {
        uf.unite(i, j);
      }
    }
  }

  return uf.getCount();
}

/**
 * 使用 DFS/BFS 求解（备用方案）
 * 时间复杂度：O(n² × m)
 * 空间复杂度：O(n)
 */
static int solutionDFS(vector<string>& strs) {
  int n = strs.size();
  vector<bool> visited(n, false);
  int groups = 0;

  function<void(int)> dfs = [&](int index) {
    visited[index] = true;
    for (int i = 0; i < n; ++i) {
      if (!visited[i] && isSimilar(strs[index], strs[i])) {
        dfs(i);
      }
    }
  };

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(i);
      groups++;
    }
  }

  return groups;
}

SimilarStringGroupsSolution::SimilarStringGroupsSolution() {
  setMetaInfo({.id = 839,
               .title = "Similar String Groups",
               .url = "https://leetcode.com/problems/similar-string-groups/"});
  registerStrategy("Union-Find", solutionUnionFind);
  registerStrategy("DFS", solutionDFS);
}

int SimilarStringGroupsSolution::numSimilarGroups(vector<string>& strs) {
  return getSolution()(strs);
}

}  // namespace problem_839
}  // namespace leetcode
