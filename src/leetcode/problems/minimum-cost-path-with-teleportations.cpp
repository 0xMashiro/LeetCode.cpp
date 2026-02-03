#include "leetcode/problems/minimum-cost-path-with-teleportations.h"

namespace leetcode {
namespace problem_3651 {

static int solution1(vector<vector<int>>& grid, int k) {
  const int m = grid.size();
  const int n = grid[0].size();
  const int INF = 1e9;
  
  // Collect and compress values
  vector<int> allValues;
  allValues.reserve(m * n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      allValues.push_back(grid[i][j]);
    }
  }
  sort(allValues.begin(), allValues.end());
  allValues.erase(unique(allValues.begin(), allValues.end()), allValues.end());
  const int V = allValues.size();
  
  // Map value to index
  auto getValueIdx = [&](int val) {
    return lower_bound(allValues.begin(), allValues.end(), val) - allValues.begin();
  };
  
  // dp[i][j][t] = min cost to reach (i,j) using exactly t teleports
  // Use 2D array per t to save memory
  vector<vector<int>> dp(m, vector<int>(n, INF));
  vector<vector<int>> newDp(m, vector<int>(n, INF));
  
  int ans = INF;
  
  for (int t = 0; t <= k; ++t) {
    // Initialize: start at (0,0) with cost 0 for any t
    dp[0][0] = 0;
    
    if (t > 0) {
      // Compute best cost for each value from dp (t-1 layer)
      // best[idx] = min dp[i][j] among cells with value = allValues[idx]
      vector<int> best(V, INF);
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          int idx = getValueIdx(grid[i][j]);
          best[idx] = min(best[idx], dp[i][j]);
        }
      }
      
      // Compute suffix min: suffixBest[idx] = min best[u] for u >= idx
      // This gives min cost to reach any cell with value >= allValues[idx] using t-1 teleports
      vector<int> suffixBest(V, INF);
      suffixBest[V-1] = best[V-1];
      for (int i = V-2; i >= 0; --i) {
        suffixBest[i] = min(best[i], suffixBest[i+1]);
      }
      
      // Initialize newDp with teleport costs
      // newDp[i][j] can be reached by teleport from any cell with value >= grid[i][j]
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          int idx = getValueIdx(grid[i][j]);
          newDp[i][j] = suffixBest[idx];  // cost via teleport
        }
      }
    } else {
      // t = 0, no teleport possible
      for (int i = 0; i < m; ++i) {
        fill(newDp[i].begin(), newDp[i].end(), INF);
      }
      newDp[0][0] = 0;  // start
    }
    
    // DP for normal moves (right and down)
    // Process in row-major order since we can only move right or down
    // Actually we need to be careful: we can also stay in place (if teleport gives better cost)
    // So we need to propagate minimums
    
    // Forward pass: from top-left to bottom-right
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0 && j == 0) continue;  // start position
        int fromTop = (i > 0) ? newDp[i-1][j] + grid[i][j] : INF;
        int fromLeft = (j > 0) ? newDp[i][j-1] + grid[i][j] : INF;
        newDp[i][j] = min(newDp[i][j], min(fromTop, fromLeft));
      }
    }
    
    // Update answer
    ans = min(ans, newDp[m-1][n-1]);
    
    // Copy newDp to dp for next iteration
    dp.swap(newDp);
  }
  
  return ans;
}

MinimumCostPathWithTeleportationsSolution::MinimumCostPathWithTeleportationsSolution() {
  setMetaInfo({.id = 3651,
               .title = "Minimum Cost Path with Teleportations",
               .url = "https://leetcode.com/problems/minimum-cost-path-with-teleportations/"});
  registerStrategy("DP with Value Compression", solution1);
}

int MinimumCostPathWithTeleportationsSolution::minCost(vector<vector<int>>& grid, int k) {
  return getSolution()(grid, k);
}

}  // namespace problem_3651
}  // namespace leetcode
