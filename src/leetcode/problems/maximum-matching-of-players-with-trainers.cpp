#include "leetcode/problems/maximum-matching-of-players-with-trainers.h"

namespace leetcode {
namespace problem_2410 {

// 贪心算法：排序 + 双指针
// 思路：为每个运动员找能满足条件的最小训练师，这样可以留下大训练师给能力更强的运动员
// 时间复杂度: O(n log n + m log m)，空间复杂度: O(1)（忽略排序栈空间）
static int solution1(vector<int>& players, vector<int>& trainers) {
  // 对两个数组进行排序
  sort(players.begin(), players.end());
  sort(trainers.begin(), trainers.end());
  
  int n = players.size();
  int m = trainers.size();
  int i = 0;  // 运动员指针
  int j = 0;  // 训练师指针
  int matchCount = 0;
  
  // 双指针遍历
  while (i < n && j < m) {
    if (players[i] <= trainers[j]) {
      // 当前训练师可以满足当前运动员
      matchCount++;
      i++;  // 运动员匹配成功，找下一个
      j++;  // 训练师被占用，找下一个
    } else {
      // 当前训练师容量不够，尝试更大的训练师
      j++;
    }
  }
  
  return matchCount;
}

MaximumMatchingOfPlayersWithTrainersSolution::MaximumMatchingOfPlayersWithTrainersSolution() {
  setMetaInfo({.id = 2410,
               .title = "Maximum Matching of Players With Trainers",
               .url = "https://leetcode.com/problems/maximum-matching-of-players-with-trainers/"});
  registerStrategy("Greedy Sorting", solution1);
}

int MaximumMatchingOfPlayersWithTrainersSolution::matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
  return getSolution()(players, trainers);
}

}  // namespace problem_2410
}  // namespace leetcode
