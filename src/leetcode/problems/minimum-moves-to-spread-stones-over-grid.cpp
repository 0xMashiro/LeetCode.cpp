#include "leetcode/problems/minimum-moves-to-spread-stones-over-grid.h"

namespace leetcode {
namespace problem_2850 {

class Solution {
 public:
  int minimumMoves(vector<vector<int>>& grid) {
    sources_.clear();
    targets_.clear();
    
    // 收集源位置（石头数 > 1）和目标位置（石头数 = 0）
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (grid[i][j] > 1) {
          // 有多余的石头，可以作为源
          for (int k = 1; k < grid[i][j]; ++k) {
            sources_.push_back({i, j});
          }
        } else if (grid[i][j] == 0) {
          // 需要石头
          targets_.push_back({i, j});
        }
      }
    }
    
    // 如果没有需要移动的，直接返回 0
    if (targets_.empty()) return 0;
    
    ans_ = INT_MAX;
    visited_.assign(targets_.size(), false);
    
    // 从第一个目标开始回溯
    backtrack(0, 0);
    
    return ans_;
  }
  
 private:
  vector<pair<int, int>> sources_;  // 源位置列表（每个多余石头单独一个条目）
  vector<pair<int, int>> targets_;  // 目标位置列表
  vector<bool> visited_;            // 标记哪些源已被使用
  int ans_;
  
  // 计算曼哈顿距离
  int distance(const pair<int, int>& a, const pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
  }
  
  // 回溯：为第 target_idx 个目标格子选择源格子
  void backtrack(int target_idx, int current_moves) {
    if (target_idx == (int)targets_.size()) {
      // 所有目标都已分配
      ans_ = min(ans_, current_moves);
      return;
    }
    
    // 剪枝：如果当前移动数已经超过最优解，直接返回
    if (current_moves >= ans_) return;
    
    // 尝试每个未使用的源
    for (int i = 0; i < (int)sources_.size(); ++i) {
      if (!visited_[i]) {
        visited_[i] = true;
        int dist = distance(sources_[i], targets_[target_idx]);
        backtrack(target_idx + 1, current_moves + dist);
        visited_[i] = false;
      }
    }
  }
};

// 包装函数适配 SolutionBase 模式
static int solution1(vector<vector<int>>& grid) {
  Solution sol;
  return sol.minimumMoves(grid);
}

MinimumMovesToSpreadStonesOverGridSolution::MinimumMovesToSpreadStonesOverGridSolution() {
  setMetaInfo({
    .id = 2850,
    .title = "Minimum Moves to Spread Stones Over Grid",
    .url = "https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/"
  });
  registerStrategy("Backtracking", solution1);
}

int MinimumMovesToSpreadStonesOverGridSolution::minimumMoves(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_2850
}  // namespace leetcode
