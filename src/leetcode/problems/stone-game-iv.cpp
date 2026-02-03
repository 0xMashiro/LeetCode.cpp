
#include "leetcode/problems/stone-game-iv.h"

namespace leetcode {
namespace problem_1510 {

/**
 * 动态规划解法
 * dp[i] = true: 当剩余 i 个石子时，当前玩家必胜
 * dp[i] = false: 当剩余 i 个石子时，当前玩家必败
 *
 * 状态转移：
 * 对于状态 i，当前玩家可以移除 k^2 个石子（k^2 <= i）
 * 如果存在某个 k 使得 dp[i - k^2] == false，则当前玩家让对手处于必败态，所以 dp[i] = true
 * 如果所有选择都使得 dp[i - k^2] == true，则当前玩家必败，dp[i] = false
 *
 * 时间复杂度: O(n * sqrt(n))
 * 空间复杂度: O(n)
 */
static bool solution1(int n) {
  vector<bool> dp(n + 1, false);
  // dp[0] = false: 石子为0，无法操作，当前玩家输

  for (int i = 1; i <= n; ++i) {
    // 尝试所有可能的平方数
    for (int k = 1; k * k <= i; ++k) {
      int square = k * k;
      if (!dp[i - square]) {
        // 如果移除 k^2 后对手处于必败态，则当前玩家必胜
        dp[i] = true;
        break;
      }
    }
    // 如果所有选择都使对手必胜，则 dp[i] 保持 false
  }

  return dp[n];
}

/**
 * 优化版：预计算所有平方数，减少乘法运算
 */
static bool solution2(int n) {
  vector<bool> dp(n + 1, false);

  // 预计算所有不超过 n 的平方数
  vector<int> squares;
  for (int k = 1; k * k <= n; ++k) {
    squares.push_back(k * k);
  }

  for (int i = 1; i <= n; ++i) {
    for (int square : squares) {
      if (square > i) break;
      if (!dp[i - square]) {
        dp[i] = true;
        break;
      }
    }
  }

  return dp[n];
}

StoneGameIvSolution::StoneGameIvSolution() {
  setMetaInfo({.id = 1510,
               .title = "Stone Game IV",
               .url = "https://leetcode.com/problems/stone-game-iv/"});
  registerStrategy("DP with Square Check", solution1);
  registerStrategy("DP with Precomputed Squares", solution2);
}

bool StoneGameIvSolution::winnerSquareGame(int n) {
  return getSolution()(n);
}

}  // namespace problem_1510
}  // namespace leetcode
