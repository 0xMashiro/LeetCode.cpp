#include "leetcode/problems/rotating-the-box.h"

namespace leetcode {
namespace problem_1861 {

// 本题结构唯一合理解为：先模拟重力（每行让石头向右落到底），再旋转 90°
// 无法用其他思路显著区分（如排序 vs 哈希、贪心 vs DP），无真正多解
// 时间复杂度: O(m*n), 空间复杂度: O(m*n)
//
// 思路：
// 1. 对每一行从右向左扫描，用双指针 writePos 标记下一个石头可放置的最右空位
//    - 遇到障碍物 '*'：原地放下，writePos 重置为障碍物左侧
//    - 遇到石头 '#'：放到 writePos 处，writePos 左移
//    - 遇到空位 '.'：跳过
// 2. 将处理后的矩阵顺时针旋转 90° (i,j) -> (j, m-1-i)
static vector<vector<char>> solution1(vector<vector<char>>& boxGrid) {
  int m = boxGrid.size();
  int n = boxGrid[0].size();

  // 复制一份，避免修改输入（若允许原地修改可节省空间，但为了保证幂等性我们复制）
  vector<vector<char>> gravityApplied(m, vector<char>(n, '.'));

  // Step 1: 对每一行应用重力（石头向右落到底）
  for (int i = 0; i < m; ++i) {
    int writePos = n - 1;
    for (int j = n - 1; j >= 0; --j) {
      if (boxGrid[i][j] == '*') {
        gravityApplied[i][j] = '*';
        writePos = j - 1;
      } else if (boxGrid[i][j] == '#') {
        gravityApplied[i][writePos] = '#';
        --writePos;
      }
      // '.' 跳过即可，gravityApplied[i][j] 已初始化为 '.'
    }
  }

  // Step 2: 旋转 90° 顺时针
  vector<vector<char>> rotated(n, vector<char>(m));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      rotated[j][m - 1 - i] = gravityApplied[i][j];
    }
  }

  return rotated;
}

RotatingTheBoxSolution::RotatingTheBoxSolution() {
  setMetaInfo({.id = 1861,
               .title = "Rotating the Box",
               .url = "https://leetcode.com/problems/rotating-the-box/"});
  // 本题核心解法唯一（行内重力 + 旋转），无需多策略
  registerStrategy({.name = "Two Pointer Gravity + Rotation"}, solution1);
}

vector<vector<char>> RotatingTheBoxSolution::rotateTheBox(
    vector<vector<char>>& boxGrid) {
  return getSolution()(boxGrid);
}

}  // namespace problem_1861
}  // namespace leetcode
