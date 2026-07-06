#include "leetcode/problems/remove-covered-intervals.h"

#include <algorithm>

namespace leetcode {
namespace problem_1288 {

// 排序 + 贪心扫描
// 1. 按左端点升序，左端点相同时按右端点降序
// 2. 扫描区间，维护当前最大右端点 maxRight
// 3. 若当前 r <= maxRight，则该区间被覆盖
// 时间复杂度: O(n log n), 空间复杂度: O(1)
static int solution1(std::vector<std::vector<int>>& intervals) {
  const int n = intervals.size();
  std::sort(intervals.begin(), intervals.end(),
            [](const std::vector<int>& a, const std::vector<int>& b) {
              if (a[0] != b[0]) return a[0] < b[0];
              return a[1] > b[1];  // 右端点降序：大区间在前
            });

  int maxRight = 0;
  int covered = 0;
  for (const auto& interval : intervals) {
    int r = interval[1];
    if (r <= maxRight) {
      ++covered;
    } else {
      maxRight = r;
    }
  }
  return n - covered;
}

RemoveCoveredIntervalsSolution::RemoveCoveredIntervalsSolution() {
  setMetaInfo({.id = 1288,
               .title = "Remove Covered Intervals",
               .url = "https://leetcode.com/problems/remove-covered-intervals"});
  registerStrategy(
      {.name = "Sort + Greedy",
       .expected = "Accepted",
       .time_complexity = "O(n log n)",
       .space_complexity = "O(1)",
       .tags = {"Array", "Sorting", "Greedy"}},
      solution1);
}

int RemoveCoveredIntervalsSolution::removeCoveredIntervals(
    std::vector<std::vector<int>>& intervals) {
  return getSolution()(intervals);
}

}  // namespace problem_1288
}  // namespace leetcode
