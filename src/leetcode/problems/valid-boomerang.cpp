#include "leetcode/problems/valid-boomerang.h"

namespace leetcode {
namespace problem_1037 {

// 使用向量叉积判断三点是否共线
// 向量 AB = (x2-x1, y2-y1), 向量 AC = (x3-x1, y3-y1)
// 叉积 = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)
// 叉积为0表示三点共线
// 时间复杂度: O(1), 空间复杂度: O(1)
static bool solution1(vector<vector<int>>& points) {
  // 提取三个点的坐标
  int x1 = points[0][0], y1 = points[0][1];
  int x2 = points[1][0], y2 = points[1][1];
  int x3 = points[2][0], y3 = points[2][1];
  
  // 计算向量 AB 和 AC 的叉积
  // 叉积为0表示三点共线，不为0表示不共线
  int crossProduct = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
  
  return crossProduct != 0;
}

ValidBoomerangSolution::ValidBoomerangSolution() {
  setMetaInfo({.id = 1037,
               .title = "Valid Boomerang",
               .url = "https://leetcode.com/problems/valid-boomerang/"});
  registerStrategy("Cross Product", solution1);
}

bool ValidBoomerangSolution::isBoomerang(vector<vector<int>>& points) {
  return getSolution()(points);
}

}  // namespace problem_1037
}  // namespace leetcode
