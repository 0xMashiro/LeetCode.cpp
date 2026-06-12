#include "leetcode/problems/minimum-interval-to-include-each-query.h"

#include <queue>
#include <set>

namespace leetcode {
namespace problem_1851 {

// ============================================================
// 策略 1: 离线查询 + 扫描线 + 最小堆
// 将 intervals 按左端点排序，queries 按值排序后离线处理。
// 扫描线逐步将覆盖当前 query 的 interval 加入最小堆（按 size 排序），
// 懒惰删除 right < query 的过期 interval，堆顶即为答案。
// 时间复杂度: O((N+Q) log N), 空间复杂度: O(N+Q)
// ============================================================
static vector<int> solution1(vector<vector<int>>& intervals,
                             vector<int>& queries) {
  const int n = intervals.size();
  const int q = queries.size();

  // 按左端点升序排序
  sort(intervals.begin(), intervals.end(),
       [](const vector<int>& a, const vector<int>& b) {
         return a[0] < b[0];
       });

  // queries 带上原始索引后按值升序排序
  vector<pair<int, int>> sortedQueries(q);
  for (int i = 0; i < q; ++i) {
    sortedQueries[i] = {queries[i], i};
  }
  sort(sortedQueries.begin(), sortedQueries.end());

  vector<int> ans(q, -1);

  // 最小堆: {interval_size, right_endpoint}
  using HeapElement = pair<int, int>;
  priority_queue<HeapElement, vector<HeapElement>, greater<HeapElement>>
      minHeap;

  int intervalIdx = 0;

  for (const auto& [queryVal, originalIdx] : sortedQueries) {
    // 将所有 left <= queryVal 的 interval 加入堆
    while (intervalIdx < n && intervals[intervalIdx][0] <= queryVal) {
      int left = intervals[intervalIdx][0];
      int right = intervals[intervalIdx][1];
      int size = right - left + 1;
      minHeap.push({size, right});
      ++intervalIdx;
    }

    // 懒惰删除：弹出 right < queryVal 的过期 interval
    while (!minHeap.empty() && minHeap.top().second < queryVal) {
      minHeap.pop();
    }

    // 堆顶即为覆盖当前 query 的最小 interval
    if (!minHeap.empty()) {
      ans[originalIdx] = minHeap.top().first;
    }
  }

  return ans;
}

// ============================================================
// 策略 2: 按区间 size 排序 + 有序集合查询分配
// 将 intervals 按 size 升序排序（最小区间优先），用 std::set
// 维护尚未回答的 query（按值排序）。对每个 interval，在 set 中
// 二分定位到 [left, right] 范围内的 query，分配答案并删除。
// 每个 query 恰好被删除一次。
// 时间复杂度: O((N+Q) log Q), 空间复杂度: O(N+Q)
// ============================================================
static vector<int> solution2(vector<vector<int>>& intervals,
                             vector<int>& queries) {
  const int q = queries.size();

  // 按 interval size 升序排序
  sort(intervals.begin(), intervals.end(),
       [](const vector<int>& a, const vector<int>& b) {
         int sizeA = a[1] - a[0] + 1;
         int sizeB = b[1] - b[0] + 1;
         return sizeA < sizeB;
       });

  // 未回答的 query 集合: {query_val, original_index}
  set<pair<int, int>> active;
  for (int i = 0; i < q; ++i) {
    active.insert({queries[i], i});
  }

  vector<int> ans(q, -1);

  for (const auto& interval : intervals) {
    int left = interval[0];
    int right = interval[1];
    int size = right - left + 1;

    // 定位到第一个 >= left 的 query
    auto it = active.lower_bound({left, -1});
    // 范围内所有 query 的答案即为当前 interval 的 size（最小可用）
    while (it != active.end() && it->first <= right) {
      ans[it->second] = size;
      it = active.erase(it);
    }
  }

  return ans;
}

MinimumIntervalToIncludeEachQuerySolution::
    MinimumIntervalToIncludeEachQuerySolution() {
  setMetaInfo(
      {.id = 1851,
       .title = "Minimum Interval to Include Each Query",
       .url = "https://leetcode.com/problems/minimum-interval-to-include-each-query/"});
  registerStrategy(
      {.name = "Offline Query + Sweep Line + Min-Heap",
       .time_complexity = "O((N+Q) log N)",
       .space_complexity = "O(N+Q)",
       .tags = {"Array", "Binary Search", "Sweep Line", "Sorting",
                "Heap (Priority Queue)"}},
      solution1);
  registerStrategy(
      {.name = "Sort by Interval Size + Ordered Set Query Assignment",
       .time_complexity = "O((N+Q) log Q)",
       .space_complexity = "O(N+Q)",
       .tags = {"Array", "Binary Search", "Sorting", "Ordered Set"}},
      solution2);
}

vector<int> MinimumIntervalToIncludeEachQuerySolution::minInterval(
    vector<vector<int>>& intervals, vector<int>& queries) {
  return getSolution()(intervals, queries);
}

}  // namespace problem_1851
}  // namespace leetcode
