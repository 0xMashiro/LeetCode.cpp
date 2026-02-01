#include "leetcode/problems/erect-the-fence.h"

namespace leetcode {
namespace problem_587 {

/**
 * 计算向量 p1p2 和 p2p3 的叉积
 * cross = (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x)
 * 
 * 叉积 > 0: 左转（逆时针）
 * 叉积 < 0: 右转（顺时针）
 * 叉积 = 0: 共线
 */
static int cross(const vector<int>& p1, const vector<int>& p2, const vector<int>& p3) {
  return (p2[0] - p1[0]) * (p3[1] - p2[1]) - (p2[1] - p1[1]) * (p3[0] - p2[0]);
}

/**
 * Andrew's Monotone Chain 算法（单调链算法）
 * 1. 先按 x 坐标排序，x 相同按 y 排序
 * 2. 构建下凸包：从左到右遍历
 * 3. 构建上凸包：从右到左遍历
 * 4. 合并上下凸包（注意去重）
 * 
 * 注意：题目要求围栏周界上的所有点，包括共线的点，所以使用 <= 0 判断
 */
static vector<vector<int>> convexHull(vector<vector<int>>& trees) {
  const int n = trees.size();
  if (n <= 1) return trees;
  
  // 按 x 排序，x 相同按 y 排序
  sort(trees.begin(), trees.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
  });
  
  vector<vector<int>> lower;  // 下凸包
  vector<vector<int>> upper;  // 上凸包
  
  // 构建下凸包（从左到右）
  for (const auto& p : trees) {
    while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < 0) {
      lower.pop_back();
    }
    lower.push_back(p);
  }
  
  // 构建上凸包（从右到左）
  for (int i = n - 1; i >= 0; --i) {
    while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), trees[i]) < 0) {
      upper.pop_back();
    }
    upper.push_back(trees[i]);
  }
  
  // 合并下凸包和上凸包（去掉重复的点）
  // lower 和 upper 的第一个和最后一个点相同
  lower.pop_back();
  upper.pop_back();
  
  // 合并结果
  lower.insert(lower.end(), upper.begin(), upper.end());
  
  // 去重（可能存在重复点，如所有点共线的情况）
  sort(lower.begin(), lower.end());
  lower.erase(unique(lower.begin(), lower.end(), 
    [](const vector<int>& a, const vector<int>& b) {
      return a[0] == b[0] && a[1] == b[1];
    }), lower.end());
  
  return lower;
}

ErectTheFenceSolution::ErectTheFenceSolution() {
  setMetaInfo({.id = 587,
               .title = "Erect the Fence",
               .url = "https://leetcode.com/problems/erect-the-fence/"});
  registerStrategy("Monotone Chain", convexHull);
}

vector<vector<int>> ErectTheFenceSolution::outerTrees(vector<vector<int>>& trees) {
  return getSolution()(trees);
}

}  // namespace problem_587
}  // namespace leetcode
