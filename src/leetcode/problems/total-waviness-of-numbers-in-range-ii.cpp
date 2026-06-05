#include "leetcode/problems/total-waviness-of-numbers-in-range-ii.h"

#include <cstring>
#include <functional>
#include <string>

namespace leetcode {
namespace problem_3753 {

// ---------------------------------------------------------------
// 解法1：暴力枚举（教学用，大范围会 TLE）
// 时间复杂度: O(N * logN), N = num2 - num1 + 1
// 空间复杂度: O(1)
// ---------------------------------------------------------------
static long long solution1(long long num1, long long num2) {
  long long total = 0;
  for (long long x = num1; x <= num2; ++x) {
    std::string s = std::to_string(x);
    int n = s.size();
    if (n < 3) continue;
    for (int i = 1; i < n - 1; ++i) {
      int left = s[i - 1] - '0';
      int mid = s[i] - '0';
      int right = s[i + 1] - '0';
      if ((mid > left && mid > right) || (mid < left && mid < right)) {
        ++total;
      }
    }
  }
  return total;
}

// ---------------------------------------------------------------
// 解法2：数位 DP（最优解）
// 将 [num1, num2] 转化为 f(num2) - f(num1-1)，其中 f(X) = [0, X] 的波状度和
// 时间复杂度: O(len * 10 * 11 * 11 * 2) ≈ O(16 * 2420)
// 空间复杂度: O(len * 11 * 11 * 2 * 2) ≈ 8K
// ---------------------------------------------------------------
static long long solution2(long long num1, long long num2) {
  // f(X) = 区间 [0, X] 的总波状度
  auto digitDp = [](long long X) -> long long {
    if (X <= 0) return 0;
    std::string s = std::to_string(X);
    int n = (int)s.size();

    // memo_cnt[pos][prev1+1][prev2+1][started][tight]
    // prev1/prev2: -1（未定义）映射到索引 0，0~9 映射到 1~10
    long long memo_cnt[16][11][11][2][2];
    long long memo_sum[16][11][11][2][2];
    std::memset(memo_cnt, -1, sizeof(memo_cnt));

    // 递归 lambda（使用 self-pass 模式）
    std::function<std::pair<long long, long long>(int, int, int, bool, bool)> dfs;
    dfs = [&](int pos, int prev1, int prev2, bool started, bool tight)
        -> std::pair<long long, long long> {
      if (pos == n) {
        // 已处理完所有位：1 个合法数，贡献 0
        return {1, 0};
      }

      int p1 = prev1 + 1;  // 映射 -1→0, 0→1, ..., 9→10
      int p2 = prev2 + 1;

      if (!tight && memo_cnt[pos][p1][p2][started][0] != -1) {
        return {memo_cnt[pos][p1][p2][started][0],
                memo_sum[pos][p1][p2][started][0]};
      }

      int limit = tight ? (s[pos] - '0') : 9;
      long long total_cnt = 0;
      long long total_sum = 0;

      for (int d = 0; d <= limit; ++d) {
        bool new_tight = tight && (d == limit);

        if (!started && d == 0) {
          // 仍在前导零阶段
          auto [cnt, sum] = dfs(pos + 1, -1, -1, false, new_tight);
          total_cnt += cnt;
          total_sum += sum;
        } else if (!started && d != 0) {
          // 第一个非零数字（数字开始）
          auto [cnt, sum] = dfs(pos + 1, d, -1, true, new_tight);
          total_cnt += cnt;
          total_sum += sum;
        } else {
          // started == true：已有至少一个非零数字
          // prev1 是位置 pos-1 的数字，prev2 是位置 pos-2 的数字
          long long add = 0;
          if (prev2 != -1) {
            // prev1 同时有左邻（prev2）和右邻（d），可以判断峰/谷
            if (prev2 < prev1 && prev1 > d) {
              add = 1;  // peak
            } else if (prev2 > prev1 && prev1 < d) {
              add = 1;  // valley
            }
          }
          auto [cnt, sum] = dfs(pos + 1, d, prev1, true, new_tight);
          total_cnt += cnt;
          total_sum += sum + cnt * add;
        }
      }

      if (!tight) {
        memo_cnt[pos][p1][p2][started][0] = total_cnt;
        memo_sum[pos][p1][p2][started][0] = total_sum;
      }
      return {total_cnt, total_sum};
    };

    return dfs(0, -1, -1, false, true).second;
  };

  return digitDp(num2) - digitDp(num1 - 1);
}

// ---------------------------------------------------------------
// 构造函数：注册元数据 + 所有策略
// ---------------------------------------------------------------
TotalWavinessOfNumbersInRangeIiSolution::
    TotalWavinessOfNumbersInRangeIiSolution() {
  setMetaInfo({.id = 3753,
               .title = "Total Waviness of Numbers in Range II",
               .url = "https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/"});
  registerStrategy("BruteForce", solution1);  // @expected: TLE
  registerStrategy("DigitDP", solution2);
}

// ---------------------------------------------------------------
// 公开方法：通过 SolutionBase 调度
// ---------------------------------------------------------------
long long TotalWavinessOfNumbersInRangeIiSolution::totalWaviness(
    long long num1, long long num2) {
  return getSolution()(num1, num2);
}

}  // namespace problem_3753
}  // namespace leetcode
