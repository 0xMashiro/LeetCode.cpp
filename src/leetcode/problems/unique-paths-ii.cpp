#include "leetcode/problems/unique-paths-ii.h"

namespace leetcode {
namespace problem_63 {

// 动态规划（原地修改）：利用 obstacleGrid 原地存储 dp 值
// 时间复杂度: O(m*n), 空间复杂度: O(1)
static int solution1(vector<vector<int>>& obstacleGrid) {
  const int m = obstacleGrid.size();
  const int n = obstacleGrid[0].size();
  
  // 如果起点或终点有障碍物，直接返回 0
  if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
    return 0;
  }
  
  // 初始化起点
  obstacleGrid[0][0] = 1;
  
  // 初始化第一列
  for (int i = 1; i < m; ++i) {
    obstacleGrid[i][0] = (obstacleGrid[i][0] == 0 && obstacleGrid[i - 1][0] == 1) ? 1 : 0;
  }
  
  // 初始化第一行
  for (int j = 1; j < n; ++j) {
    obstacleGrid[0][j] = (obstacleGrid[0][j] == 0 && obstacleGrid[0][j - 1] == 1) ? 1 : 0;
  }
  
  // 状态转移
  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      if (obstacleGrid[i][j] == 0) {
        // 如果当前位置不是障碍物，路径数 = 上方路径数 + 左方路径数
        obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
      } else {
        // 当前位置是障碍物，路径数为 0
        obstacleGrid[i][j] = 0;
      }
    }
  }
  
  return obstacleGrid[m - 1][n - 1];
}

// 动态规划（滚动数组优化）：使用一维数组存储 dp 值
// 时间复杂度: O(m*n), 空间复杂度: O(n)
static int solution2(vector<vector<int>>& obstacleGrid) {
  const int m = obstacleGrid.size();
  const int n = obstacleGrid[0].size();
  
  // 如果起点或终点有障碍物，直接返回 0
  if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
    return 0;
  }
  
  vector<int> dp(n, 0);
  dp[0] = 1;  // 起点
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (obstacleGrid[i][j] == 1) {
        dp[j] = 0;  // 当前位置是障碍物，无法到达
      } else if (j > 0) {
        dp[j] += dp[j - 1];  // dp[j] 已经包含从上方的路径，加上从左方的路径
      }
      // j == 0 时，dp[j] 保持不变（只能从上方的 dp[j] 继承）
    }
  }
  
  return dp[n - 1];
}

UniquePathsIiSolution::UniquePathsIiSolution() {
  setMetaInfo({.id = 63,
               .title = "Unique Paths II",
               .url = "https://leetcode.com/problems/unique-paths-ii/"});
  registerStrategy("DP In-Place", solution1);
  registerStrategy("DP Rolling Array", solution2);
}

int UniquePathsIiSolution::uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
  return getSolution()(obstacleGrid);
}

}  // namespace problem_63
}  // namespace leetcode
