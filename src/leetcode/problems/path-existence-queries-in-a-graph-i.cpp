#include "leetcode/problems/path-existence-queries-in-a-graph-i.h"

namespace leetcode {
namespace problem_3532 {

// 线性扫描 + 分量标记
// 由于 nums 已排序，连通分量必为连续区间。
// 只需检查相邻元素差值是否 <= maxDiff，将节点划分到不同分量。
// 时间复杂度: O(n + q)，空间复杂度: O(n)
static std::vector<bool> solution1(int n, std::vector<int>& nums, int maxDiff,
                                   std::vector<std::vector<int>>& queries) {
  // comp[i] = 节点 i 所属的连通分量 ID
  std::vector<int> comp(n);
  comp[0] = 0;
  int cur = 0;
  for (int i = 1; i < n; ++i) {
    if (nums[i] - nums[i - 1] <= maxDiff) {
      comp[i] = cur;
    } else {
      comp[i] = ++cur;
    }
  }

  const int q = static_cast<int>(queries.size());
  std::vector<bool> ans(q);
  for (int i = 0; i < q; ++i) {
    ans[i] = (comp[queries[i][0]] == comp[queries[i][1]]);
  }
  return ans;
}

PathExistenceQueriesInAGraphISolution::PathExistenceQueriesInAGraphISolution() {
  setMetaInfo({.id = 3532,
               .title = "Path Existence Queries in a Graph I",
               .url = "https://leetcode.com/problems/path-existence-queries-in-a-graph-i/"});
  registerStrategy({.name = "Linear Scan + Component ID",
                    .expected = "Accepted",
                    .time_complexity = "O(n + q)",
                    .space_complexity = "O(n)",
                    .tags = {"Array", "Union-Find", "Graph Theory"}},
                   solution1);
}

std::vector<bool> PathExistenceQueriesInAGraphISolution::pathExistenceQueries(
    int n, std::vector<int>& nums, int maxDiff, std::vector<std::vector<int>>& queries) {
  return getSolution()(n, nums, maxDiff, queries);
}

}  // namespace problem_3532
}  // namespace leetcode
