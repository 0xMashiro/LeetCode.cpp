#include "leetcode/problems/smallest-string-with-swaps.h"

namespace leetcode {
namespace problem_1202 {

// 并查集实现
class UnionFind {
 public:
  UnionFind(int n) : parent(n), rank(n, 0) {
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
    int px = find(x), py = find(y);
    if (px == py) return;
    // 按秩合并
    if (rank[px] < rank[py]) {
      parent[px] = py;
    } else if (rank[px] > rank[py]) {
      parent[py] = px;
    } else {
      parent[py] = px;
      rank[px]++;
    }
  }

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

// 并查集解法
// 时间复杂度: O(n log n + m α(n)), 空间复杂度: O(n)
static std::string solution(std::string s, std::vector<std::vector<int>>& pairs) {
  int n = s.size();
  UnionFind uf(n);
  
  // 构建连通分量
  for (const auto& pair : pairs) {
    uf.unite(pair[0], pair[1]);
  }
  
  // 按连通分量分组索引
  std::unordered_map<int, std::vector<int>> groups;
  for (int i = 0; i < n; ++i) {
    groups[uf.find(i)].push_back(i);
  }
  
  // 对每个连通分量的字符排序并放回
  for (auto& [root, indices] : groups) {
    std::string chars;
    chars.reserve(indices.size());
    for (int idx : indices) {
      chars.push_back(s[idx]);
    }
    std::sort(chars.begin(), chars.end());
    
    // 按索引顺序放回排序后的字符
    for (size_t i = 0; i < indices.size(); ++i) {
      s[indices[i]] = chars[i];
    }
  }
  
  return s;
}

SmallestStringWithSwapsSolution::SmallestStringWithSwapsSolution() {
  setMetaInfo({
    .id = 1202,
    .title = "Smallest String With Swaps",
    .url = "https://leetcode.com/problems/smallest-string-with-swaps/"
  });
  registerStrategy("Union Find", solution);
}

std::string SmallestStringWithSwapsSolution::smallestStringWithSwaps(
    std::string s, std::vector<std::vector<int>>& pairs) {
  return getSolution()(s, pairs);
}

}  // namespace problem_1202
}  // namespace leetcode
