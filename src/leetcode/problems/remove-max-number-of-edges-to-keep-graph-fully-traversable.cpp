#include "leetcode/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable.h"

namespace leetcode {
namespace problem_1579 {

static int solution1(int n, vector<vector<int>>& edges) {
  // 并查集（Union-Find）数据结构定义在函数内部
  class UnionFind {
   public:
    UnionFind(int n) {
      parent_.resize(n + 1);  // 节点编号从1开始
      rank_.resize(n + 1, 0);
      for (int i = 0; i <= n; ++i) {
        parent_[i] = i;
      }
      components_ = n;  // 初始时有n个连通分量
    }

    // 查找根节点，带路径压缩
    int find(int x) {
      if (parent_[x] != x) {
        parent_[x] = find(parent_[x]);
      }
      return parent_[x];
    }

    // 合并两个集合，带按秩合并
    // 返回true表示合并成功，false表示已在同一集合
    bool unite(int x, int y) {
      int px = find(x), py = find(y);
      if (px == py) return false;
      
      if (rank_[px] < rank_[py]) {
        swap(px, py);
      }
      parent_[py] = px;
      if (rank_[px] == rank_[py]) {
        rank_[px]++;
      }
      components_--;
      return true;
    }

    // 获取连通分量数量
    int getComponents() const {
      return components_;
    }

   private:
    vector<int> parent_;
    vector<int> rank_;
    int components_;
  };

  int totalEdges = edges.size();
  int usedEdges = 0;

  // 第一步：处理类型3的边（Alice和Bob都能走的公共边）
  // 同时应用到Alice和Bob的并查集
  UnionFind ufAlice(n);
  UnionFind ufBob(n);

  for (const auto& edge : edges) {
    if (edge[0] == 3) {
      bool aliceUnited = ufAlice.unite(edge[1], edge[2]);
      bool bobUnited = ufBob.unite(edge[1], edge[2]);
      // 类型3的边如果被任一方使用就算使用了这条边
      if (aliceUnited || bobUnited) {
        usedEdges++;
      }
    }
  }

  // 第二步：处理Alice的专属边（类型1）
  for (const auto& edge : edges) {
    if (edge[0] == 1) {
      if (ufAlice.unite(edge[1], edge[2])) {
        usedEdges++;
      }
    }
  }

  // 第三步：处理Bob的专属边（类型2）
  for (const auto& edge : edges) {
    if (edge[0] == 2) {
      if (ufBob.unite(edge[1], edge[2])) {
        usedEdges++;
      }
    }
  }

  // 检查Alice和Bob是否都能完全遍历图
  // 完全遍历意味着只有一个连通分量
  if (ufAlice.getComponents() != 1 || ufBob.getComponents() != 1) {
    return -1;
  }

  // 最多可移除的边数 = 总边数 - 必须保留的边数
  return totalEdges - usedEdges;
}

RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution::RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution() {
  setMetaInfo({.id = 1579,
               .title = "Remove Max Number of Edges to Keep Graph Fully Traversable",
               .url = "https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/"});
  registerStrategy("Union-Find", solution1);
}

int RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution::maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
  return getSolution()(n, edges);
}

}  // namespace problem_1579
}  // namespace leetcode
