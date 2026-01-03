#include "leetcode/problems/number-of-ways-to-paint-n-3-grid.h"

namespace leetcode {
namespace problem_1411 {

namespace {
constexpr int MOD = 1'000'000'007;

// 生成所有可能的行排列（长度为3，相邻颜色不同）
vector<vector<int>> generateRows() {
  vector<vector<int>> rows;
  for (int a = 0; a < 3; ++a) {
    for (int b = 0; b < 3; ++b) {
      if (b == a) continue;
      for (int c = 0; c < 3; ++c) {
        if (c == b) continue;
        rows.push_back({a, b, c});
      }
    }
  }
  return rows;
}

// 构建兼容性矩阵，compat[i][j] = true 表示排列 i 可以放在排列 j 的下一行
vector<vector<bool>> buildCompatibilityMatrix(const vector<vector<int>>& rows) {
  const int m = rows.size();
  vector<vector<bool>> compat(m, vector<bool>(m, false));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      bool ok = true;
      for (int k = 0; k < 3; ++k) {
        if (rows[i][k] == rows[j][k]) {
          ok = false;
          break;
        }
      }
      compat[i][j] = ok;
    }
  }
  return compat;
}

}  // namespace

// 策略1：动态规划 O(n * m^2)，其中 m = 12
static int solution1(int n) {
  const auto rows = generateRows();
  const int m = rows.size();  // 12
  const auto compat = buildCompatibilityMatrix(rows);

  vector<long long> cur(m, 1);  // 第一行可以是任何排列
  vector<long long> nxt(m, 0);

  for (int i = 2; i <= n; ++i) {
    fill(nxt.begin(), nxt.end(), 0);
    for (int t = 0; t < m; ++t) {
      long long sum = 0;
      for (int s = 0; s < m; ++s) {
        if (compat[s][t]) {
          sum += cur[s];
          if (sum >= MOD) sum -= MOD;
        }
      }
      nxt[t] = sum;
    }
    swap(cur, nxt);
  }

  long long ans = 0;
  for (long long val : cur) {
    ans += val;
    if (ans >= MOD) ans -= MOD;
  }
  return static_cast<int>(ans);
}

// 策略2：矩阵快速幂 O(m^3 log n)，其中 m = 12
static int solution2(int n) {
  const auto rows = generateRows();
  const int m = rows.size();  // 12
  const auto compat = buildCompatibilityMatrix(rows);

  // 构建转移矩阵 M（大小为 m×m）
  vector<vector<long long>> M(m, vector<long long>(m, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      M[i][j] = compat[i][j] ? 1 : 0;
    }
  }

  // 计算 M^(n-1)
  auto matrixMul = [](const vector<vector<long long>>& A,
                      const vector<vector<long long>>& B) {
    const int n = A.size();
    const int m = B.size();   // 应该等于 A[0].size()
    const int p = B[0].size();
    vector<vector<long long>> C(n, vector<long long>(p, 0));
    for (int i = 0; i < n; ++i) {
      for (int k = 0; k < m; ++k) {
        if (A[i][k] == 0) continue;
        for (int j = 0; j < p; ++j) {
          C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        }
      }
    }
    return C;
  };

  auto matrixPow = [&matrixMul](vector<vector<long long>> mat, int power) {
    const int n = mat.size();
    // 单位矩阵
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) result[i][i] = 1;

    while (power > 0) {
      if (power & 1) {
        result = matrixMul(result, mat);
      }
      mat = matrixMul(mat, mat);
      power >>= 1;
    }
    return result;
  };

  if (n == 1) {
    // M^0 是单位矩阵，所有元素之和为 m = 12
    return m;
  }

  auto Mp = matrixPow(M, n - 1);

  // 求所有元素之和
  long long ans = 0;
  for (const auto& row : Mp) {
    for (long long val : row) {
      ans += val;
      if (ans >= MOD) ans -= MOD;
    }
  }
  return static_cast<int>(ans);
}

NumberOfWaysToPaintN3GridSolution::NumberOfWaysToPaintN3GridSolution() {
  setMetaInfo({.id = 1411,
               .title = "Number of Ways to Paint N × 3 Grid",
               .url = "https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/"});
  registerStrategy("Dynamic Programming", solution1);
  registerStrategy("Matrix Exponentiation", solution2);
}

int NumberOfWaysToPaintN3GridSolution::numOfWays(int n) {
  return getSolution()(n);
}

}  // namespace problem_1411
}  // namespace leetcode