#include "leetcode/problems/minimum-time-visiting-all-points.h"

namespace leetcode {
namespace problem_1266 {

// 策略：计算相邻点之间的切比雪夫距离（Chebyshev distance）之和
// 时间复杂度: O(n)，空间复杂度: O(1)
static int solution1(vector<vector<int>>& points) {
  int totalTime = 0;
  for (int i = 1; i < points.size(); ++i) {
    int dx = abs(points[i][0] - points[i - 1][0]);
    int dy = abs(points[i][1] - points[i - 1][1]);
    totalTime += max(dx, dy);
  }
  return totalTime;
}

MinimumTimeVisitingAllPointsSolution::MinimumTimeVisitingAllPointsSolution() {
  setMetaInfo({.id = 1266,
               .title = "Minimum Time Visiting All Points",
               .url = "https://leetcode.com/problems/minimum-time-visiting-all-points/"});
  registerStrategy({.name = "Chebyshev Distance Sum"}, solution1);
}

int MinimumTimeVisitingAllPointsSolution::minTimeToVisitAllPoints(vector<vector<int>>& points) {
  return getSolution()(points);
}

}  // namespace problem_1266
}  // namespace leetcode