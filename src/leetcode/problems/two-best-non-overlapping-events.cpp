#include "leetcode/problems/two-best-non-overlapping-events.h"

namespace leetcode {
namespace problem_2054 {

// 暴力枚举：检查所有事件对
// 时间复杂度: O(n²), 空间复杂度: O(1)
static int bruteForce(vector<vector<int>>& events) {
  int n = events.size();
  int ans = 0;
  // 单个事件最大值
  for (int i = 0; i < n; ++i) {
    ans = max(ans, events[i][2]);
  }
  // 两个事件
  for (int i = 0; i < n; ++i) {
    int s1 = events[i][0], e1 = events[i][1], v1 = events[i][2];
    for (int j = i + 1; j < n; ++j) {
      int s2 = events[j][0], e2 = events[j][1], v2 = events[j][2];
      // 两个事件不重叠的条件：一个的结束时间 < 另一个的开始时间
      if (e1 < s2 || e2 < s1) {
        ans = max(ans, v1 + v2);
      }
    }
  }
  return ans;
}

// 优化方法：排序 + 后缀最大值 + 二分查找
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static int optimized(vector<vector<int>>& events) {
  int n = events.size();
  // 转换为数组并按照开始时间排序
  vector<array<int, 3>> arr(n);
  for (int i = 0; i < n; ++i) {
    arr[i] = {events[i][0], events[i][1], events[i][2]};
  }
  sort(arr.begin(), arr.end(),
       [](const array<int, 3>& a, const array<int, 3>& b) {
         return a[0] < b[0];
       });

  // 提取开始时间用于二分查找
  vector<int> starts(n);
  for (int i = 0; i < n; ++i) {
    starts[i] = arr[i][0];
  }

  // 后缀最大值：suffix_max[i] 表示从索引 i 开始往后的单个事件最大价值
  vector<int> suffix_max(n + 1, 0);
  for (int i = n - 1; i >= 0; --i) {
    suffix_max[i] = max(arr[i][2], suffix_max[i + 1]);
  }

  int ans = 0;
  // 单个事件最大值
  for (int i = 0; i < n; ++i) {
    ans = max(ans, arr[i][2]);
  }

  // 考虑两个事件的情况
  for (int i = 0; i < n; ++i) {
    int end = arr[i][1];
    int target = end + 1;  // 下一个事件必须在此时间或之后开始
    // 二分查找第一个开始时间 >= target 的事件
    auto it = lower_bound(starts.begin(), starts.end(), target);
    if (it != starts.end()) {
      int j = it - starts.begin();
      ans = max(ans, arr[i][2] + suffix_max[j]);
    }
    // 如果没有找到后续事件，当前事件只能单独选择（已在前面考虑）
  }
  return ans;
}

TwoBestNonOverlappingEventsSolution::TwoBestNonOverlappingEventsSolution() {
  setMetaInfo({.id = 2054,
               .title = "Two Best Non-Overlapping Events",
               .url = "https://leetcode.com/problems/two-best-non-overlapping-events/"});
  registerStrategy("Brute Force", bruteForce);
  registerStrategy("Sorting + Suffix Max + Binary Search", optimized);
}

int TwoBestNonOverlappingEventsSolution::maxTwoEvents(vector<vector<int>>& events) {
  return getSolution()(events);
}

}  // namespace problem_2054
}  // namespace leetcode