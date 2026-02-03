#include "leetcode/problems/maximum-area-rectangle-with-point-constraints-i.h"

namespace leetcode {
namespace problem_3380 {

// 暴力枚举所有可能的矩形
// 对于轴对齐矩形，需要找到 (x1,y1), (x1,y2), (x2,y1), (x2,y2) 四个点
// 时间复杂度: O(n^4) 枚举四个点，但实际优化后是 O(n^2) 枚举对角线
// 空间复杂度: O(n) 存储点集
static int solution1(vector<vector<int>>& points) {
  int n = points.size();
  if (n < 4) return -1;
  
  // 将点存入 set，方便快速查找
  // 使用 pair 存储 x, y
  set<pair<int, int>> pointSet;
  for (const auto& p : points) {
    pointSet.insert({p[0], p[1]});
  }
  
  int maxArea = -1;
  
  // 枚举所有点对作为矩形的对角线
  // 如果点 i 和点 j 可以作为对角线，则需要 (xi, yj) 和 (xj, yi) 也存在
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int x1 = points[i][0], y1 = points[i][1];
      int x2 = points[j][0], y2 = points[j][1];
      
      // 跳过共线的情况（无法形成矩形）
      if (x1 == x2 || y1 == y2) continue;
      
      // 检查另外两个角点是否存在
      if (pointSet.count({x1, y2}) == 0) continue;
      if (pointSet.count({x2, y1}) == 0) continue;
      
      // 计算矩形边界
      int minX = min(x1, x2);
      int maxX = max(x1, x2);
      int minY = min(y1, y2);
      int maxY = max(y1, y2);
      
      // 检查矩形内部或边界上是否有其他点
      bool hasExtraPoint = false;
      for (const auto& p : points) {
        int x = p[0], y = p[1];
        // 跳过四个角点
        if ((x == x1 && y == y1) || (x == x1 && y == y2) ||
            (x == x2 && y == y1) || (x == x2 && y == y2)) {
          continue;
        }
        // 检查点是否在矩形内部或边界上
        if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
          hasExtraPoint = true;
          break;
        }
      }
      
      if (!hasExtraPoint) {
        int area = (maxX - minX) * (maxY - minY);
        maxArea = max(maxArea, area);
      }
    }
  }
  
  return maxArea;
}

MaximumAreaRectangleWithPointConstraintsISolution::MaximumAreaRectangleWithPointConstraintsISolution() {
  setMetaInfo({
    .id = 3380,
    .title = "Maximum Area Rectangle With Point Constraints I",
    .url = "https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/"
  });
  registerStrategy("Brute Force", solution1);
}

int MaximumAreaRectangleWithPointConstraintsISolution::maxRectangleArea(vector<vector<int>>& points) {
  return getSolution()(points);
}

}  // namespace problem_3380
}  // namespace leetcode