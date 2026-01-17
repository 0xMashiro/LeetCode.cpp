
#include "leetcode/problems/find-the-largest-area-of-square-inside-two-rectangles.h"

namespace leetcode {
namespace problem_3047 {

// 枚举所有矩形对，计算相交区域的最大正方形面积
// 时间复杂度: O(n²), 空间复杂度: O(1)
static long long solution1(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
  const int n = bottomLeft.size();
  long long maxArea = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // 计算相交区域的左下角和右上角
      int x1 = max(bottomLeft[i][0], bottomLeft[j][0]);
      int y1 = max(bottomLeft[i][1], bottomLeft[j][1]);
      int x2 = min(topRight[i][0], topRight[j][0]);
      int y2 = min(topRight[i][1], topRight[j][1]);
      // 检查是否相交
      if (x1 < x2 && y1 < y2) {
        long long width = x2 - x1;
        long long height = y2 - y1;
        long long side = min(width, height);
        long long area = side * side;
        if (area > maxArea) {
          maxArea = area;
        }
      }
    }
  }
  return maxArea;
}

FindTheLargestAreaOfSquareInsideTwoRectanglesSolution::FindTheLargestAreaOfSquareInsideTwoRectanglesSolution() {
  setMetaInfo({.id = 3047,
               .title = "Find the Largest Area of Square Inside Two Rectangles",
               .url = "https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/"});
  registerStrategy("Pairwise Enumeration", solution1);
}

long long FindTheLargestAreaOfSquareInsideTwoRectanglesSolution::largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
  return getSolution()(bottomLeft, topRight);
}

}  // namespace problem_3047
}  // namespace leetcode