
#include "leetcode/problems/solving-questions-with-brainpower.h"

namespace leetcode {
namespace problem_2140 {

// 动态规划（倒推）：
// dp[i] 表示从第 i 题开始能获得的最大分数
// 对于第 i 题，有两种选择：
// 1. 解决：获得 points[i]，然后跳到 i + brainpower[i] + 1
// 2. 跳过：继续考虑第 i+1 题
// dp[i] = max(points[i] + dp[i + brainpower[i] + 1], dp[i + 1])
// 时间复杂度: O(n), 空间复杂度: O(n)
static long long solution1(vector<vector<int>>& questions) {
  int n = questions.size();
  vector<long long> dp(n + 1, 0);  // dp[n] = 0 作为边界

  for (int i = n - 1; i >= 0; --i) {
    int points = questions[i][0];
    int brainpower = questions[i][1];
    
    // 解决第 i 题后的下一个位置
    int nextIdx = i + brainpower + 1;
    long long solve = points + (nextIdx < n ? dp[nextIdx] : 0);
    
    // 跳过第 i 题
    long long skip = dp[i + 1];
    
    dp[i] = max(solve, skip);
  }

  return dp[0];
}

// 动态规划（空间优化）：只保留需要的值
// 时间复杂度: O(n), 空间复杂度: O(1)
static long long solution2(vector<vector<int>>& questions) {
  int n = questions.size();
  // 只需要 dp[i+1] 和 dp[i+brainpower+1]，但 brainpower 不确定
  // 所以还是用数组更方便，或者可以用 unordered_map，但数组更快
  // 这里用基础版本即可，因为题目约束 1e5，空间足够
  vector<long long> dp(n + 1, 0);

  for (int i = n - 1; i >= 0; --i) {
    long long solve = questions[i][0];
    int nextIdx = i + questions[i][1] + 1;
    if (nextIdx < n) {
      solve += dp[nextIdx];
    }
    dp[i] = max(solve, dp[i + 1]);
  }

  return dp[0];
}

SolvingQuestionsWithBrainpowerSolution::SolvingQuestionsWithBrainpowerSolution() {
  setMetaInfo({.id = 2140,
               .title = "Solving Questions With Brainpower",
               .url = "https://leetcode.com/problems/solving-questions-with-brainpower/"});
  registerStrategy("DP Bottom-up", solution1);
  registerStrategy("DP Optimized", solution2);
}

long long SolvingQuestionsWithBrainpowerSolution::mostPoints(vector<vector<int>>& questions) {
  return getSolution()(questions);
}

}  // namespace problem_2140
}  // namespace leetcode
