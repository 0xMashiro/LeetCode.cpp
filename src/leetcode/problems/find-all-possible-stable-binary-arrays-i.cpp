#include "leetcode/problems/find-all-possible-stable-binary-arrays-i.h"

namespace leetcode {
namespace problem_3129 {

namespace {  // 匿名命名空间，替代 static

const int MOD = 1000000007;

// 解法1：三维 DP（朴素）
// 时间复杂度 O(zero * one * limit)，空间复杂度 O(zero * one)
// dp0[i][j] = 用了 i 个 0、j 个 1，最后一位是 0 的方案数
// dp1[i][j] = 用了 i 个 0、j 个 1，最后一位是 1 的方案数
// 转移：枚举最后一段连续相同数字的长度 k (1 <= k <= limit)
int solution1(int zero, int one, int limit) {
  vector<vector<long long>> dp0(zero + 1, vector<long long>(one + 1, 0));
  vector<vector<long long>> dp1(zero + 1, vector<long long>(one + 1, 0));

  // 初始化：全 0 数组
  for (int i = 1; i <= min(zero, limit); ++i) {
    dp0[i][0] = 1;
  }
  // 初始化：全 1 数组
  for (int j = 1; j <= min(one, limit); ++j) {
    dp1[0][j] = 1;
  }

  for (int i = 1; i <= zero; ++i) {
    for (int j = 1; j <= one; ++j) {
      long long sum0 = 0;
      int maxK0 = min(limit, i);
      for (int k = 1; k <= maxK0; ++k) {
        sum0 += dp1[i - k][j];
      }
      dp0[i][j] = sum0 % MOD;

      long long sum1 = 0;
      int maxK1 = min(limit, j);
      for (int k = 1; k <= maxK1; ++k) {
        sum1 += dp0[i][j - k];
      }
      dp1[i][j] = sum1 % MOD;
    }
  }

  return (int)((dp0[zero][one] + dp1[zero][one]) % MOD);
}

// 解法2：三维 DP + 前缀和优化
// 时间复杂度 O(zero * one)，空间复杂度 O(zero * one)
int solution2(int zero, int one, int limit) {
  vector<vector<long long>> dp0(zero + 1, vector<long long>(one + 1, 0));
  vector<vector<long long>> dp1(zero + 1, vector<long long>(one + 1, 0));
  vector<vector<long long>> pref1(zero + 1, vector<long long>(one + 1, 0));
  vector<vector<long long>> pref0(zero + 1, vector<long long>(one + 1, 0));

  for (int i = 0; i <= zero; ++i) {
    for (int j = 0; j <= one; ++j) {
      if (i == 0 && j == 0) {
        // 空数组
      } else if (j == 0) {
        dp0[i][0] = (i <= limit) ? 1 : 0;
      } else if (i == 0) {
        dp1[0][j] = (j <= limit) ? 1 : 0;
      } else {
        // dp0[i][j] = sum_{k=1}^{min(limit,i)} dp1[i-k][j]
        long long sum0 = pref1[i - 1][j];
        if (i - limit - 1 >= 0) {
          sum0 = (sum0 - pref1[i - limit - 1][j] + MOD) % MOD;
        }
        dp0[i][j] = sum0;

        // dp1[i][j] = sum_{k=1}^{min(limit,j)} dp0[i][j-k]
        long long sum1 = pref0[i][j - 1];
        if (j - limit - 1 >= 0) {
          sum1 = (sum1 - pref0[i][j - limit - 1] + MOD) % MOD;
        }
        dp1[i][j] = sum1;
      }

      // 更新前缀和
      if (i == 0) {
        pref1[0][j] = dp1[0][j];
      } else {
        pref1[i][j] = (pref1[i - 1][j] + dp1[i][j]) % MOD;
      }
      if (j == 0) {
        pref0[i][0] = dp0[i][0];
      } else {
        pref0[i][j] = (pref0[i][j - 1] + dp0[i][j]) % MOD;
      }
    }
  }

  return (int)((dp0[zero][one] + dp1[zero][one]) % MOD);
}

}  // anonymous namespace

FindAllPossibleStableBinaryArraysISolution::FindAllPossibleStableBinaryArraysISolution() {
  setMetaInfo({.id = 3129,
               .title = "Find All Possible Stable Binary Arrays I",
               .url = "https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/"});
  registerStrategy({.name = "3D DP"}, solution1);
  registerStrategy({.name = "Prefix Sum DP"}, solution2);
}

int FindAllPossibleStableBinaryArraysISolution::numberOfStableArrays(int zero, int one, int limit) {
  return getSolution()(zero, one, limit);
}

}  // namespace problem_3129
}  // namespace leetcode
