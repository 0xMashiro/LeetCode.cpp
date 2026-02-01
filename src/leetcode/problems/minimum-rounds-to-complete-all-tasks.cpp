
#include "leetcode/problems/minimum-rounds-to-complete-all-tasks.h"

namespace leetcode {
namespace problem_2244 {

// 哈希表统计频率 + 贪心
// 思路：
// 1. 统计每种难度级别的出现次数
// 2. 对于次数 count：
//    - 如果 count == 1，无法完成，返回 -1
//    - 否则，尽量多用 3，最少轮数为 ceil(count / 3) = (count + 2) / 3
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& tasks) {
  unordered_map<int, int> freq;
  for (int task : tasks) {
    freq[task]++;
  }
  
  int rounds = 0;
  for (const auto& [level, count] : freq) {
    if (count == 1) {
      return -1;  // 无法完成
    }
    // 尽量多用 3，最少轮数为 ceil(count / 3)
    // 数学上等于 (count + 2) / 3
    rounds += (count + 2) / 3;
  }
  
  return rounds;
}

MinimumRoundsToCompleteAllTasksSolution::MinimumRoundsToCompleteAllTasksSolution() {
  setMetaInfo({.id = 2244,
               .title = "Minimum Rounds to Complete All Tasks",
               .url = "https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/"});
  registerStrategy("Hash Table + Greedy", solution1);
}

int MinimumRoundsToCompleteAllTasksSolution::minimumRounds(vector<int>& tasks) {
  return getSolution()(tasks);
}

}  // namespace problem_2244
}  // namespace leetcode
