#include "leetcode/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold.h"

namespace leetcode {
namespace problem_1292 {

// 策略1：二维前缀和 + 整体二分搜索边长
// 时间复杂度: O(m * n * log(min(m, n))), 空间复杂度: O(m * n)
static int solution1(vector<vector<int>>& mat, int threshold) {
  int m = mat.size();
  int n = mat[0].size();
  
  // 计算二维前缀和
  vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      prefix[i + 1][j + 1] = mat[i][j] + prefix[i][j + 1] + 
                            prefix[i + 1][j] - prefix[i][j];
    }
  }
  
  // 计算子矩阵和的辅助函数
  auto getSum = [&](int r1, int c1, int r2, int c2) {
    return prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] - 
           prefix[r2 + 1][c1] + prefix[r1][c1];
  };
  
  // 检查是否存在边长为 k 的正方形满足条件
  auto check = [&](int k) -> bool {
    if (k == 0) return true;
    for (int i = 0; i + k <= m; ++i) {
      for (int j = 0; j + k <= n; ++j) {
        int sum = getSum(i, j, i + k - 1, j + k - 1);
        if (sum <= threshold) {
          return true;
        }
      }
    }
    return false;
  };
  
  // 二分搜索最大边长
  int lo = 1;
  int hi = min(m, n);
  int ans = 0;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (check(mid)) {
      ans = mid;
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return ans;
}

// 策略2：二维前缀和 + 逐位置二分搜索
// 时间复杂度: O(m * n * log(min(m, n))), 空间复杂度: O(m * n)
static int solution2(vector<vector<int>>& mat, int threshold) {
  int m = mat.size();
  int n = mat[0].size();
  
  // 计算二维前缀和
  vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      prefix[i + 1][j + 1] = mat[i][j] + prefix[i][j + 1] + 
                            prefix[i + 1][j] - prefix[i][j];
    }
  }
  
  // 计算子矩阵和的辅助函数
  auto getSum = [&](int r1, int c1, int r2, int c2) {
    return prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] - 
           prefix[r2 + 1][c1] + prefix[r1][c1];
  };
  
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int maxK = min(m - i, n - j);
      // 如果当前最大边长已经大于等于最大可能边长，跳过
      if (ans >= maxK) continue;
      
      // 二分搜索从 ans+1 开始
      int lo = ans + 1;
      int hi = maxK;
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int sum = getSum(i, j, i + mid - 1, j + mid - 1);
        if (sum <= threshold) {
          ans = max(ans, mid);
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
    }
  }
  return ans;
}

// 策略3：二维前缀和 + 逐步增加边长（优化版）
// 时间复杂度: O(m * n * min(m, n)) 最坏情况，但实际中较快
// 空间复杂度: O(m * n)
static int solution3(vector<vector<int>>& mat, int threshold) {
  int m = mat.size();
  int n = mat[0].size();
  
  // 计算二维前缀和
  vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      prefix[i + 1][j + 1] = mat[i][j] + prefix[i][j + 1] + 
                            prefix[i + 1][j] - prefix[i][j];
    }
  }
  
  // 计算子矩阵和的辅助函数
  auto getSum = [&](int r1, int c1, int r2, int c2) {
    return prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] - 
           prefix[r2 + 1][c1] + prefix[r1][c1];
  };
  
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // 尝试扩展边长，从 ans+1 开始
      while (i + ans < m && j + ans < n) {
        int sum = getSum(i, j, i + ans, j + ans);
        if (sum <= threshold) {
          ++ans;
        } else {
          break;
        }
      }
    }
  }
  return ans;
}

MaximumSideLengthOfASquareWithSumLessThanOrEqualToThresholdSolution::
MaximumSideLengthOfASquareWithSumLessThanOrEqualToThresholdSolution() {
  setMetaInfo({.id = 1292,
               .title = "Maximum Side Length of a Square with Sum Less than or Equal to Threshold",
               .url = "https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/"});
  registerStrategy({.name = "Binary Search on Side Length (Global)"}, solution1);
  registerStrategy({.name = "Binary Search per Position"}, solution2);
  registerStrategy({.name = "Incremental Expansion"}, solution3);
}

int MaximumSideLengthOfASquareWithSumLessThanOrEqualToThresholdSolution::
maxSideLength(vector<vector<int>>& mat, int threshold) {
  return getSolution()(mat, threshold);
}

}  // namespace problem_1292
}  // namespace leetcode