#include "leetcode/problems/find-the-first-player-to-win-k-games-in-a-row.h"

namespace leetcode {
namespace problem_3175 {

// 队列模拟：显式模拟比赛过程，便于理解问题机制
// 时间复杂度: O(n), 空间复杂度: O(n)
// 核心观察：一旦最大技能玩家成为冠军，他将永远不败，可直接返回
static int solution1(vector<int>& skills, int k) {
  int n = skills.size();

  // 预先找到最大技能玩家的索引
  int max_skill_idx = 0;
  for (int i = 1; i < n; ++i) {
    if (skills[i] > skills[max_skill_idx]) {
      max_skill_idx = i;
    }
  }

  deque<int> q;
  for (int i = 0; i < n; ++i) q.push_back(i);

  int win_count = 0;
  int champion = q.front();

  while (true) {
    int a = q.front(); q.pop_front();
    int b = q.front(); q.pop_front();

    int winner, loser;
    if (skills[a] > skills[b]) {
      winner = a;
      loser = b;
    } else {
      winner = b;
      loser = a;
    }

    q.push_front(winner);
    q.push_back(loser);

    if (winner == champion) {
      ++win_count;
    } else {
      champion = winner;
      win_count = 1;
    }

    // 达到 k 连胜，返回
    if (win_count == k) return champion;
    // 最大技能玩家已成为冠军，他将持续获胜直到达到 k 胜
    if (champion == max_skill_idx) return champion;
  }

  return -1;  // unreachable
}

// 线性扫描：最优解法
// 关键洞察：只需遍历一次玩家列表，维护当前冠军和连胜次数
// 如果当前玩家技能更高，成为新冠军；否则当前冠军连胜+1
// 一旦连胜达到k，立即返回；遍历完所有玩家后，当前冠军必然是最大技能玩家
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(vector<int>& skills, int k) {
  int n = skills.size();
  int champion = 0;
  int win_count = 0;

  for (int i = 1; i < n; ++i) {
    if (skills[champion] > skills[i]) {
      ++win_count;
    } else {
      champion = i;
      win_count = 1;
    }
    if (win_count == k) return champion;
  }

  // 遍历完所有对手，当前冠军是最大技能玩家，将持续获胜直到达到k胜
  return champion;
}

FindTheFirstPlayerToWinKGamesInARowSolution::FindTheFirstPlayerToWinKGamesInARowSolution() {
  setMetaInfo({.id = 3175,
               .title = "Find The First Player to win K Games in a Row",
               .url = "https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/"});
  registerStrategy("Queue Simulation", solution1);
  registerStrategy("Linear Scan", solution2);
}

int FindTheFirstPlayerToWinKGamesInARowSolution::findWinningPlayer(vector<int>& skills, int k) {
  return getSolution()(skills, k);
}

}  // namespace problem_3175
}  // namespace leetcode
