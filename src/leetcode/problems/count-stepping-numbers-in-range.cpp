#include "leetcode/problems/count-stepping-numbers-in-range.h"

namespace leetcode {
namespace problem_2801 {

static const int MOD = 1000000007;

// 数位DP：计算 [0, s] 中的步进数个数
static int countStepping(const string& s) {
  int n = s.size();
  // dp[pos][tight][lastDigit+1]: lastDigit=-1 表示前导零状态
  // 使用 -1 表示 lastDigit 为前导零状态，用 10 作为维度（0-9 表示实际数字，10 表示前导零）
  vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(2, vector<long long>(11, -1)));
  
  function<long long(int, bool, int)> dfs = [&](int pos, bool tight, int lastDigit) -> long long {
    if (pos == n) {
      // 如果 lastDigit 不是前导零状态，说明形成了一个有效数字
      return lastDigit != 10 ? 1 : 0;
    }
    
    if (memo[pos][tight][lastDigit] != -1) {
      return memo[pos][tight][lastDigit];
    }
    
    long long res = 0;
    int limit = tight ? (s[pos] - '0') : 9;
    
    for (int d = 0; d <= limit; ++d) {
      bool newTight = tight && (d == limit);
      
      if (lastDigit == 10) {
        // 前导零状态
        if (d == 0) {
          // 继续保持前导零状态
          res = (res + dfs(pos + 1, newTight, 10)) % MOD;
        } else {
          // 选择了一个非零数字作为第一位
          res = (res + dfs(pos + 1, newTight, d)) % MOD;
        }
      } else {
        // 非前导零状态，需要检查相邻数字差是否为1
        if (abs(d - lastDigit) == 1) {
          res = (res + dfs(pos + 1, newTight, d)) % MOD;
        }
      }
    }
    
    memo[pos][tight][lastDigit] = res;
    return res;
  };
  
  return (int)dfs(0, true, 10);
}

// 字符串减法：计算 low - 1
static string subtractOne(string low) {
  int n = low.size();
  int i = n - 1;
  while (i >= 0 && low[i] == '0') {
    low[i] = '9';
    i--;
  }
  if (i >= 0) {
    low[i]--;
  }
  // 移除前导零
  int start = 0;
  while (start < n && low[start] == '0') {
    start++;
  }
  if (start == n) return "0";
  return low.substr(start);
}

static int solve(string low, string high) {
  // 计算 [0, high] - [0, low-1] = [low, high]
  string lowMinusOne = subtractOne(low);
  int countHigh = countStepping(high);
  int countLowMinusOne = (lowMinusOne == "0" || lowMinusOne.empty()) ? 0 : countStepping(lowMinusOne);
  return (countHigh - countLowMinusOne + MOD) % MOD;
}

CountSteppingNumbersInRangeSolution::CountSteppingNumbersInRangeSolution() {
  setMetaInfo({.id = 2801,
               .title = "Count Stepping Numbers in Range",
               .url = "https://leetcode.com/problems/count-stepping-numbers-in-range/"});
  registerStrategy("Digit DP", solve);
}

int CountSteppingNumbersInRangeSolution::countSteppingNumbers(string low, string high) {
  return getSolution()(low, high);
}

}  // namespace problem_2801
}  // namespace leetcode
