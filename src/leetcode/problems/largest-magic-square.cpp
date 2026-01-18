
#include "leetcode/problems/largest-magic-square.h"

namespace leetcode {
namespace problem_1895 {

// 策略1：暴力枚举 + 行/列前缀和优化
// 时间复杂度：O(m * n * min(m,n)^3)，但常数较小，实际运行快
// 空间复杂度：O(m * n) 用于前缀和
static int solution1(vector<vector<int>>& grid) {
  const int m = grid.size();
  const int n = grid[0].size();
  const int maxK = min(m, n);

  // 行前缀和：rowPrefix[i][j] 表示第 i 行前 j 个元素的和（0-indexed）
  vector<vector<long long>> rowPrefix(m, vector<long long>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j];
    }
  }

  // 列前缀和：colPrefix[i][j] 表示第 j 列前 i 个元素的和（0-indexed）
  vector<vector<long long>> colPrefix(m + 1, vector<long long>(n, 0));
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < m; ++i) {
      colPrefix[i + 1][j] = colPrefix[i][j] + grid[i][j];
    }
  }

  // 从大到小枚举 k
  for (int k = maxK; k >= 2; --k) {
    // 枚举所有可能的左上角
    for (int r = 0; r + k <= m; ++r) {
      for (int c = 0; c + k <= n; ++c) {
        // 检查行和
        long long target = -1;
        bool valid = true;

        // 检查每一行的和
        for (int i = 0; i < k; ++i) {
          long long rowSum = rowPrefix[r + i][c + k] - rowPrefix[r + i][c];
          if (target == -1) {
            target = rowSum;
          } else if (rowSum != target) {
            valid = false;
            break;
          }
        }
        if (!valid) continue;

        // 检查每一列的和
        for (int j = 0; j < k; ++j) {
          long long colSum = colPrefix[r + k][c + j] - colPrefix[r][c + j];
          if (colSum != target) {
            valid = false;
            break;
          }
        }
        if (!valid) continue;

        // 检查主对角线
        long long diag1 = 0;
        for (int d = 0; d < k; ++d) {
          diag1 += grid[r + d][c + d];
        }
        if (diag1 != target) continue;

        // 检查副对角线
        long long diag2 = 0;
        for (int d = 0; d < k; ++d) {
          diag2 += grid[r + d][c + k - 1 - d];
        }
        if (diag2 != target) continue;

        // 找到幻方
        return k;
      }
    }
  }

  // 每个 1x1 都是幻方
  return 1;
}

// 策略2：暴力枚举 + 行/列/对角线前缀和优化
// 使用对角线前缀和实现 O(1) 计算对角线
// 时间复杂度：O(m * n * min(m,n)^2)
// 空间复杂度：O(m * n)
static int solution2(vector<vector<int>>& grid) {
  const int m = grid.size();
  const int n = grid[0].size();
  const int maxK = min(m, n);

  // 行前缀和
  vector<vector<long long>> rowPrefix(m, vector<long long>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j];
    }
  }

  // 列前缀和
  vector<vector<long long>> colPrefix(m + 1, vector<long long>(n, 0));
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < m; ++i) {
      colPrefix[i + 1][j] = colPrefix[i][j] + grid[i][j];
    }
  }

  // 主对角线前缀和：diag1[r][c] 表示从 (0,0) 到 (r,c) 的主对角线方向的和
  // 即 diag1[r][c] = grid[r][c] + (r>0 && c>0 ? diag1[r-1][c-1] : 0)
  vector<vector<long long>> diag1(m, vector<long long>(n, 0));
  for (int r = 0; r < m; ++r) {
    for (int c = 0; c < n; ++c) {
      diag1[r][c] = grid[r][c];
      if (r > 0 && c > 0) {
        diag1[r][c] += diag1[r - 1][c - 1];
      }
    }
  }

  // 副对角线前缀和：diag2[r][c] 表示从 (0,c) 开始沿右下方向（行增加，列减少）到 (r, c) 的和
  // 即 diag2[r][c] = grid[r][c] + (r>0 && c+1<n ? diag2[r-1][c+1] : 0)
  vector<vector<long long>> diag2(m, vector<long long>(n, 0));
  for (int r = 0; r < m; ++r) {
    for (int c = 0; c < n; ++c) {
      diag2[r][c] = grid[r][c];
      if (r > 0 && c + 1 < n) {
        diag2[r][c] += diag2[r - 1][c + 1];
      }
    }
  }

  // 从大到小枚举 k
  for (int k = maxK; k >= 2; --k) {
    // 枚举所有可能的左上角
    for (int r = 0; r + k <= m; ++r) {
      for (int c = 0; c + k <= n; ++c) {
        // 检查行和
        long long target = -1;
        bool valid = true;

        // 检查每一行的和
        for (int i = 0; i < k; ++i) {
          long long rowSum = rowPrefix[r + i][c + k] - rowPrefix[r + i][c];
          if (target == -1) {
            target = rowSum;
          } else if (rowSum != target) {
            valid = false;
            break;
          }
        }
        if (!valid) continue;

        // 检查每一列的和
        for (int j = 0; j < k; ++j) {
          long long colSum = colPrefix[r + k][c + j] - colPrefix[r][c + j];
          if (colSum != target) {
            valid = false;
            break;
          }
        }
        if (!valid) continue;

        // 检查主对角线
        long long diag1Sum = diag1[r + k - 1][c + k - 1];
        if (r > 0 && c > 0) {
          diag1Sum -= diag1[r - 1][c - 1];
        }
        if (diag1Sum != target) continue;

        // 检查副对角线
        long long diag2Sum = diag2[r + k - 1][c];
        if (r > 0 && c + k < n) {
          diag2Sum -= diag2[r - 1][c + k];
        }
        if (diag2Sum != target) continue;

        // 找到幻方
        return k;
      }
    }
  }

  // 每个 1x1 都是幻方
  return 1;
}

LargestMagicSquareSolution::LargestMagicSquareSolution() {
  setMetaInfo({.id = 1895,
               .title = "Largest Magic Square",
               .url = "https://leetcode.com/problems/largest-magic-square/"});
  registerStrategy("Brute Force with Prefix Sum", solution1);
  registerStrategy("Optimized with Diagonal Prefix Sum", solution2);
}

int LargestMagicSquareSolution::largestMagicSquare(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_1895
}  // namespace leetcode
