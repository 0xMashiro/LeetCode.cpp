
#include "leetcode/problems/minimum-cost-homecoming-of-a-robot-in-a-grid.h"

namespace leetcode {
namespace problem_2087 {

// 贪心策略：直接走向目标，无需绕行
// 因为成本只与进入的格子有关，与移动顺序无关
// 时间复杂度: O(|start_row - home_row| + |start_col - home_col|)
// 空间复杂度: O(1)
static int solution1(vector<int>& startPos, vector<int>& homePos, 
                     vector<int>& rowCosts, vector<int>& colCosts) {
  int start_row = startPos[0];
  int start_col = startPos[1];
  int home_row = homePos[0];
  int home_col = homePos[1];
  
  // 已经在终点
  if (start_row == home_row && start_col == home_col) {
    return 0;
  }
  
  int total_cost = 0;
  
  // 行方向移动：从 start_row 走到 home_row
  if (start_row <= home_row) {
    // 向下移动：经过的行是 start_row+1, start_row+2, ..., home_row
    for (int r = start_row + 1; r <= home_row; ++r) {
      total_cost += rowCosts[r];
    }
  } else {
    // 向上移动：经过的行是 start_row-1, start_row-2, ..., home_row
    for (int r = start_row - 1; r >= home_row; --r) {
      total_cost += rowCosts[r];
    }
  }
  
  // 列方向移动：从 start_col 走到 home_col
  if (start_col <= home_col) {
    // 向右移动：经过的列是 start_col+1, start_col+2, ..., home_col
    for (int c = start_col + 1; c <= home_col; ++c) {
      total_cost += colCosts[c];
    }
  } else {
    // 向左移动：经过的列是 start_col-1, start_col-2, ..., home_col
    for (int c = start_col - 1; c >= home_col; --c) {
      total_cost += colCosts[c];
    }
  }
  
  return total_cost;
}

MinimumCostHomecomingOfARobotInAGridSolution::MinimumCostHomecomingOfARobotInAGridSolution() {
  setMetaInfo({.id = 2087,
               .title = "Minimum Cost Homecoming of a Robot in a Grid",
               .url = "https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/"});
  registerStrategy("Greedy Direct Path", solution1);
}

int MinimumCostHomecomingOfARobotInAGridSolution::minCost(
    vector<int>& startPos, vector<int>& homePos, 
    vector<int>& rowCosts, vector<int>& colCosts) {
  return getSolution()(startPos, homePos, rowCosts, colCosts);
}

}  // namespace problem_2087
}  // namespace leetcode
