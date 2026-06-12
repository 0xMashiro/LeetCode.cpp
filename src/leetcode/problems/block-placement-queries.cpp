#include "leetcode/problems/block-placement-queries.h"

#include <algorithm>
#include <set>
#include <vector>

namespace leetcode {
namespace problem_3161 {

// ---------- 辅助：线段树（点更新 + 区间 max 查询） ----------
class SegTree {
  int n;
  vector<int> tree;

  void update(int idx, int val, int node, int l, int r) {
    if (l == r) {
      tree[node] = val;
      return;
    }
    int m = (l + r) / 2;
    if (idx <= m)
      update(idx, val, node * 2, l, m);
    else
      update(idx, val, node * 2 + 1, m + 1, r);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
  }

  int query(int ql, int qr, int node, int l, int r) const {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int m = (l + r) / 2;
    return max(query(ql, qr, node * 2, l, m),
               query(ql, qr, node * 2 + 1, m + 1, r));
  }

 public:
  explicit SegTree(int sz) : n(sz), tree(4 * sz, 0) {}

  void set(int idx, int val) { update(idx, val, 1, 0, n - 1); }

  int range_max(int l, int r) const {
    if (l > r) return 0;
    return query(l, r, 1, 0, n - 1);
  }
};

// ============================================================
// 解法 1：暴力枚举（教学用，可能 TLE）
// 每次 type-2 查询遍历所有 obstacles ≤ x，O(N²)
// ============================================================
static vector<bool> solution1(vector<vector<int>>& queries) {
  set<int> obs;
  vector<bool> ans;
  for (auto& q : queries) {
    if (q[0] == 1) {
      obs.insert(q[1]);
    } else {
      int x = q[1], sz = q[2];
      int prev_pos = 0;
      int max_gap = 0;
      for (int p : obs) {
        if (p > x) break;
        max_gap = max(max_gap, p - prev_pos);
        prev_pos = p;
      }
      max_gap = max(max_gap, x - prev_pos);
      ans.push_back(max_gap >= sz);
    }
  }
  return ans;
}

// ============================================================
// 解法 2：线段树（最优解）
// 维护障碍物集合，用线段树记录每个障碍物到前一个障碍物的 gap
// 每次添加障碍物时分裂旧的 gap、创建新的 gap
// 查询时：gap_to_x = x - last_obstacle_before_x，或 x（若没有障碍物）
//         线段树查询 [0, x] 内的最大 gap
// 两者取最大，与 sz 比较
// 时间复杂度 O(Q log M)，M = 50000
// ============================================================
static vector<bool> solution2(vector<vector<int>>& queries) {
  const int MAX_COORD = 50000;
  set<int> obs;
  SegTree seg(MAX_COORD + 1);  // 下标 0..MAX_COORD

  vector<bool> ans;
  ans.reserve(queries.size());

  for (auto& q : queries) {
    if (q[0] == 1) {
      // type 1: place obstacle at position x
      int x = q[1];
      auto it = obs.lower_bound(x);

      int left = -1, right = -1;
      if (it != obs.begin()) left = *std::prev(it);
      if (it != obs.end()) right = *it;

      // Remove the old gap that spanned across x
      if (left != -1 && right != -1) {
        seg.set(right, 0);
      }

      // Add new gaps
      if (left != -1) {
        seg.set(x, x - left);
      } else {
        // first obstacle, gap from origin
        seg.set(x, x);
      }
      if (right != -1) {
        seg.set(right, right - x);
      }

      obs.insert(x);
    } else {
      // type 2: query
      int x = q[1], sz = q[2];

      // Find the rightmost obstacle <= x
      auto it = obs.upper_bound(x);
      int last_obs = -1;
      if (it != obs.begin()) last_obs = *std::prev(it);

      // Gap from last obstacle (or origin) to x
      int gap_to_x = (last_obs != -1) ? (x - last_obs) : x;

      bool ok = (gap_to_x >= sz);
      if (!ok) {
        // Query max gap among stored gaps (between obstacles) within [0, x]
        int max_gap = seg.range_max(0, x);
        ok = (max_gap >= sz);
      }

      ans.push_back(ok);
    }
  }

  return ans;
}

// ============================================================
// 构造函数：注册元数据和策略
// ============================================================
BlockPlacementQueriesSolution::BlockPlacementQueriesSolution() {
  setMetaInfo({.id = 3161,
               .title = "Block Placement Queries",
               .url = "https://leetcode.com/problems/block-placement-queries/"});
  registerStrategy({.name = "Brute Force", .expected = "TLE"}, solution1);
  registerStrategy({.name = "Segment Tree"}, solution2);
}

vector<bool> BlockPlacementQueriesSolution::getResults(
    vector<vector<int>>& queries) {
  return getSolution()(queries);
}

}  // namespace problem_3161
}  // namespace leetcode
