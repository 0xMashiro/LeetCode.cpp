#include "leetcode/problems/path-existence-queries-in-a-graph-ii.h"

#include <algorithm>
#include <numeric>
#include <vector>

namespace leetcode {
namespace problem_3534 {

// 排序 + 倍增法
// 时间复杂度: O((n + q) log n)
// 空间复杂度: O(n log n)
static std::vector<int> solution1(int n, std::vector<int>& nums, int maxDiff,
                                  std::vector<std::vector<int>>& queries) {
  // 按 nums 排序
  std::vector<int> order(n);
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(),
            [&](int a, int b) { return nums[a] < nums[b]; });

  // 原节点 -> 排序位置
  std::vector<int> pos(n);
  for (int i = 0; i < n; ++i) pos[order[i]] = i;

  // 双指针计算 left / right（一跳可达的最左/最右排序下标）
  std::vector<int> L(n), R(n);
  int r = 0;
  for (int i = 0; i < n; ++i) {
    while (r < n && nums[order[r]] - nums[order[i]] <= maxDiff) ++r;
    R[i] = r - 1;
  }
  int l = 0;
  for (int i = 0; i < n; ++i) {
    while (nums[order[i]] - nums[order[l]] > maxDiff) ++l;
    L[i] = l;
  }

  // 连通分量（相邻差值 > maxDiff 处断开）
  std::vector<int> comp(n);
  comp[0] = 0;
  for (int i = 1; i < n; ++i) {
    if (nums[order[i]] - nums[order[i - 1]] <= maxDiff)
      comp[i] = comp[i - 1];
    else
      comp[i] = i;  // 新分量根
  }

  // 倍增表
  const int K = 18;  // 2^18 = 262144 > 1e5
  std::vector<std::vector<int>> left_k(K, std::vector<int>(n));
  std::vector<std::vector<int>> right_k(K, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    left_k[0][i] = L[i];
    right_k[0][i] = R[i];
  }
  for (int k = 1; k < K; ++k) {
    for (int i = 0; i < n; ++i) {
      left_k[k][i] = left_k[k - 1][left_k[k - 1][i]];
      right_k[k][i] = right_k[k - 1][right_k[k - 1][i]];
    }
  }

  // 回答查询
  std::vector<int> ans;
  ans.reserve(queries.size());
  for (auto& q : queries) {
    int u = q[0], v = q[1];
    int pu = pos[u], pv = pos[v];

    if (comp[pu] != comp[pv]) {
      ans.push_back(-1);
      continue;
    }
    if (pu == pv) {
      ans.push_back(0);
      continue;
    }

    int dist = 0;
    if (pu < pv) {
      if (R[pu] >= pv) {
        dist = 1;
      } else {
        int cur = pu;
        for (int k = K - 1; k >= 0; --k) {
          if (right_k[k][cur] < pv) {
            cur = right_k[k][cur];
            dist += (1 << k);
          }
        }
        ++dist;  // 最后一步
      }
    } else {
      if (L[pu] <= pv) {
        dist = 1;
      } else {
        int cur = pu;
        for (int k = K - 1; k >= 0; --k) {
          if (left_k[k][cur] > pv) {
            cur = left_k[k][cur];
            dist += (1 << k);
          }
        }
        ++dist;
      }
    }
    ans.push_back(dist);
  }
  return ans;
}

PathExistenceQueriesInAGraphIiSolution::
    PathExistenceQueriesInAGraphIiSolution() {
  setMetaInfo({.id = 3534,
               .title = "Path Existence Queries in a Graph II",
               .url =
                   "https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/"});
  registerStrategy(
      {.name = "Sorting + Binary Lifting",
       .expected = "Accepted",
       .time_complexity = "O((n + q) log n)",
       .space_complexity = "O(n log n)",
       .tags = {"Array",    "Two Pointers",  "Binary Search",
                "Dynamic Programming", "Greedy", "Sorting",
                "Bit Manipulation",    "Graph Theory"}},
      solution1);
}

std::vector<int> PathExistenceQueriesInAGraphIiSolution::pathExistenceQueries(
    int n, std::vector<int>& nums, int maxDiff,
    std::vector<std::vector<int>>& queries) {
  return getSolution()(n, nums, maxDiff, queries);
}

}  // namespace problem_3534
}  // namespace leetcode
