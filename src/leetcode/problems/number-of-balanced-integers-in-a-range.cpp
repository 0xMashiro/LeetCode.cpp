
#include "leetcode/problems/number-of-balanced-integers-in-a-range.h"

namespace leetcode {
namespace problem_3791 {

/**
 * 数位 DP 实现
 * 状态：dp[pos][diff][tight][started]
 * - pos: 当前处理的位置（从右数，或处理数字的索引）
 * - diff: 奇数位和 - 偶数位和（偏移 +72，范围 -72 到 +72）
 * - tight: 是否受限于上限数字
 * - started: 是否已经开始填非零数字（用于处理前导零）
 * 
 * 注意：这里我们用另一种方式——从左往右处理时，需要记录奇偶位置的差值
 * 由于我们不知道总长度，所以需要传递当前位置的奇偶性
 */

// 使用 memoization，状态：[位置索引][奇数和-偶数和偏移][是否受限][是否开始]
// 数字最大15位，差值范围 [-72, 72]，偏移 72
static long long dp[16][145][2][2];
static vector<int> digits;

static long long dfs(int pos, int diff, bool tight, bool started) {
  // 处理完所有位
  if (pos == (int)digits.size()) {
    // 必须已经开始（至少一位数字），且差值为0（奇数位和 = 偶数位和）
    // 且至少两位数字：通过started和最终位数判断
    return (started && diff == 72) ? 1 : 0;
  }
  
  if (dp[pos][diff][tight][started] != -1) {
    return dp[pos][diff][tight][started];
  }
  
  long long res = 0;
  int limit = tight ? digits[pos] : 9;
  
  for (int d = 0; d <= limit; ++d) {
    bool newTight = tight && (d == limit);
    bool newStarted = started || (d != 0);
    int newDiff = diff;
    
    if (newStarted) {
      // 当前位置的奇偶性：从0开始计数，pos=0是第一位（奇数位）
      // 奇数位：pos % 2 == 0，贡献 +d
      // 偶数位：pos % 2 == 1，贡献 -d
      if (pos % 2 == 0) {
        // 奇数位
        newDiff = diff + d;
      } else {
        // 偶数位
        newDiff = diff - d;
      }
    }
    
    res += dfs(pos + 1, newDiff, newTight, newStarted);
  }
  
  dp[pos][diff][tight][started] = res;
  return res;
}

// 计算 [1, n] 中的平衡整数数量
static long long countUpTo(long long n) {
  if (n < 10) return 0;  // 至少两位数
  
  digits.clear();
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
  reverse(digits.begin(), digits.end());
  
  // 初始化 DP
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 145; ++j) {
      for (int k = 0; k < 2; ++k) {
        for (int l = 0; l < 2; ++l) {
          dp[i][j][k][l] = -1;
        }
      }
    }
  }
  
  return dfs(0, 72, true, false);
}

// 主解法：数位 DP
static long long solution1(long long low, long long high) {
  return countUpTo(high) - countUpTo(low - 1);
}

NumberOfBalancedIntegersInARangeSolution::NumberOfBalancedIntegersInARangeSolution() {
  setMetaInfo({.id = 3791,
               .title = "Number of Balanced Integers in a Range",
               .url = "https://leetcode.com/problems/number-of-balanced-integers-in-a-range/"});
  registerStrategy("Digit DP", solution1);
}

long long NumberOfBalancedIntegersInARangeSolution::countBalanced(long long low, long long high) {
  return getSolution()(low, high);
}

}  // namespace problem_3791
}  // namespace leetcode
