
#include "leetcode/problems/minimum-number-of-frogs-croaking.h"

namespace leetcode {
namespace problem_1419 {

// 模拟计数法
// 用 cnt[5] 跟踪每个字母的等待数量，遍历字符串模拟青蛙叫声
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution(string croakOfFrogs) {
  // cnt[i] 表示正在等待第 i 个字母的青蛙数
  // 0:'c', 1:'r', 2:'o', 3:'a', 4:'k'
  int cnt[5] = {0};
  int activeFrogs = 0;  // 当前正在叫的青蛙数（还没叫完）
  int maxFrogs = 0;     // 同时叫的青蛙的最大数量

  for (char ch : croakOfFrogs) {
    if (ch == 'c') {
      // 新青蛙开始叫
      cnt[0]++;
      activeFrogs++;
      maxFrogs = max(maxFrogs, activeFrogs);
    } else if (ch == 'r') {
      // 必须有 'c' 在前
      if (cnt[0] == 0) return -1;
      cnt[0]--;
      cnt[1]++;
    } else if (ch == 'o') {
      // 必须有 'r' 在前
      if (cnt[1] == 0) return -1;
      cnt[1]--;
      cnt[2]++;
    } else if (ch == 'a') {
      // 必须有 'o' 在前
      if (cnt[2] == 0) return -1;
      cnt[2]--;
      cnt[3]++;
    } else if (ch == 'k') {
      // 必须有 'a' 在前
      if (cnt[3] == 0) return -1;
      cnt[3]--;
      activeFrogs--;  // 这只青蛙叫完了
    }
  }

  // 所有青蛙必须都完成了叫声
  if (activeFrogs != 0) return -1;

  return maxFrogs;
}

MinimumNumberOfFrogsCroakingSolution::MinimumNumberOfFrogsCroakingSolution() {
  setMetaInfo({.id = 1419,
               .title = "Minimum Number of Frogs Croaking",
               .url = "https://leetcode.com/problems/minimum-number-of-frogs-croaking/"});
  registerStrategy("Simulation", solution);
}

int MinimumNumberOfFrogsCroakingSolution::minNumberOfFrogs(string croakOfFrogs) {
  return getSolution()(croakOfFrogs);
}

}  // namespace problem_1419
}  // namespace leetcode
