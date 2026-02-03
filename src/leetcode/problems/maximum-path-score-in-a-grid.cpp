#include "leetcode/problems/maximum-path-score-in-a-grid.h"

namespace leetcode {
namespace problem_3742 {

int Solution::maxPathScore(vector<vector<int>>& grid, int k) {
  const int m = grid.size();
  const int n = grid[0].size();
  const int INF_NEG = -1e9;
  
  // dp[j][c] = 到达当前行第j列，总成本为c时的最大得分
  vector<vector<int>> dp(n, vector<int>(k + 1, INF_NEG));
  
  // 起点 (0,0)，grid[0][0] == 0
  dp[0][0] = 0;
  
  for (int i = 0; i < m; ++i) {
    vector<vector<int>> newDp(n, vector<int>(k + 1, INF_NEG));
    for (int j = 0; j < n; ++j) {
      int val = grid[i][j];
      int score = val;
      int cost = (val == 0) ? 0 : 1;
      
      for (int c = cost; c <= k; ++c) {
        int prevCost = c - cost;
        int bestPrev = INF_NEG;
        
        // 从上方来
        if (i > 0 && dp[j][prevCost] != INF_NEG) {
          bestPrev = max(bestPrev, dp[j][prevCost]);
        }
        
        // 从左方来
        if (j > 0 && newDp[j-1][prevCost] != INF_NEG) {
          bestPrev = max(bestPrev, newDp[j-1][prevCost]);
        }
        
        // 起点 (0,0)
        if (i == 0 && j == 0 && c == 0) {
          bestPrev = 0;
        }
        
        if (bestPrev != INF_NEG) {
          newDp[j][c] = bestPrev + score;
        }
      }
    }
    dp = move(newDp);
  }
  
  // 找最大值
  int ans = INF_NEG;
  for (int c = 0; c <= k; ++c) {
    ans = max(ans, dp[n-1][c]);
  }
  
  return (ans == INF_NEG) ? -1 : ans;
}

static int solution(vector<vector<int>>& grid, int k) {
  Solution sol;
  return sol.maxPathScore(grid, k);
}

MaximumPathScoreInAGridSolution::MaximumPathScoreInAGridSolution() {
  setMetaInfo({
    .id = 3742,
    .title = "Maximum Path Score in a Grid",
    .url = "https://leetcode.com/problems/maximum-path-score-in-a-grid/"
  });
  registerStrategy("DP", solution);
}

int MaximumPathScoreInAGridSolution::maxPathScore(vector<vector<int>>& grid, int k) {
  return getSolution()(grid, k);
}

}  // namespace problem_3742
}  // namespace leetcode
