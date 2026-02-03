#include "leetcode/problems/can-i-win.h"

namespace leetcode {
namespace problem_464 {

class Solution {
 public:
  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    // 特殊情况：如果目标总和 <= 0，先手直接获胜
    if (desiredTotal <= 0) return true;
    
    // 特殊情况：如果所有数字之和小于目标总和，无人能获胜
    int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
    if (sum < desiredTotal) return false;
    
    // 记忆化数组，dp[state] 表示当前状态下先手是否能获胜
    // state 是一个位掩码，第 i 位为 1 表示数字 (i+1) 已被使用
    memset(dp, -1, sizeof(dp));
    this->maxChoosableInteger = maxChoosableInteger;
    this->desiredTotal = desiredTotal;
    
    return dfs(0, 0);
  }

 private:
  int dp[1 << 20];  // 记忆化数组，2^20 = 1,048,576
  int maxChoosableInteger;
  int desiredTotal;
  
  // state: 位掩码表示已使用的数字
  // currentTotal: 当前累计总和
  // 返回值：当前玩家是否能获胜
  bool dfs(int state, int currentTotal) {
    // 如果已经计算过这个状态，直接返回
    if (dp[state] != -1) return dp[state];
    
    // 尝试每一个可用的数字
    for (int i = 1; i <= maxChoosableInteger; ++i) {
      int bit = 1 << (i - 1);
      // 如果数字 i 还没有被使用
      if (!(state & bit)) {
        // 选择数字 i 后能达到或超过目标总和，当前玩家获胜
        if (currentTotal + i >= desiredTotal) {
          return dp[state] = 1;
        }
        
        // 选择数字 i 后，轮到对手在新区间选择
        // 如果对手不能获胜，则当前玩家获胜
        if (!dfs(state | bit, currentTotal + i)) {
          return dp[state] = 1;
        }
      }
    }
    
    // 没有任何选择能让当前玩家获胜
    return dp[state] = 0;
  }
};

// 解决方案
static bool solution1(int maxChoosableInteger, int desiredTotal) {
  Solution sol;
  return sol.canIWin(maxChoosableInteger, desiredTotal);
}

CanIWinSolution::CanIWinSolution() {
  setMetaInfo({.id = 464,
               .title = "Can I Win",
               .url = "https://leetcode.com/problems/can-i-win/"});
  registerStrategy("Memoization DFS", solution1);
}

bool CanIWinSolution::canIWin(int maxChoosableInteger, int desiredTotal) {
  return getSolution()(maxChoosableInteger, desiredTotal);
}

}  // namespace problem_464
}  // namespace leetcode
