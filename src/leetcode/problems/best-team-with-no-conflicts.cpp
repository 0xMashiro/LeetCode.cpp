#include "leetcode/problems/best-team-with-no-conflicts.h"

namespace leetcode {
namespace problem_1626 {

// 动态规划解法
// 1. 将球员按年龄升序排序（年龄相同则按得分升序）
// 2. 排序后问题转化为：找得分非递减子序列的最大和
// 3. dp[i] 表示以第 i 个球员结尾的最大球队得分
// 时间复杂度: O(n²), 空间复杂度: O(n)
static int solution1(vector<int>& scores, vector<int>& ages) {
  const int n = scores.size();
  
  // 将球员打包并按年龄排序（年龄相同按得分排序）
  vector<pair<int, int>> players;  // {age, score}
  for (int i = 0; i < n; ++i) {
    players.push_back({ages[i], scores[i]});
  }
  sort(players.begin(), players.end());  // 默认按 first 再按 second 排序
  
  // dp[i] 表示以第 i 个球员为结尾的最大得分
  vector<int> dp(n);
  int maxScore = 0;
  
  for (int i = 0; i < n; ++i) {
    dp[i] = players[i].second;  // 至少可以只选自己
    // 尝试将第 i 个球员加入以 j 结尾的球队
    for (int j = 0; j < i; ++j) {
      // 因为按年龄排序，players[j].age <= players[i].age
      // 需要满足 players[j].score <= players[i].score 才无冲突
      if (players[j].second <= players[i].second) {
        dp[i] = max(dp[i], dp[j] + players[i].second);
      }
    }
    maxScore = max(maxScore, dp[i]);
  }
  
  return maxScore;
}

BestTeamWithNoConflictsSolution::BestTeamWithNoConflictsSolution() {
  setMetaInfo({.id = 1626,
               .title = "Best Team With No Conflicts",
               .url = "https://leetcode.com/problems/best-team-with-no-conflicts/"});
  registerStrategy("DP with Sorting", solution1);
}

int BestTeamWithNoConflictsSolution::bestTeamScore(vector<int>& scores, vector<int>& ages) {
  return getSolution()(scores, ages);
}

}  // namespace problem_1626
}  // namespace leetcode