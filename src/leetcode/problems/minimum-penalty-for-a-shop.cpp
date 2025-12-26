
#include "leetcode/problems/minimum-penalty-for-a-shop.h"

namespace leetcode {
namespace problem_2483 {

// 策略一：前缀后缀数组
// 计算 leftN[i] = 前 i 小时中 'N' 的数量
// 计算 rightY[i] = 从 i 小时开始到结束的 'Y' 的数量
// 对于关闭时间 j，惩罚 = leftN[j] + rightY[j]
// 时间复杂度: O(n)，空间复杂度: O(n)
static int solution1(string customers) {
  const int n = customers.size();
  // leftN[0] = 0, leftN[i] = 前 i 个字符中 'N' 的个数 (i = 0..n)
  vector<int> leftN(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    leftN[i + 1] = leftN[i] + (customers[i] == 'N' ? 1 : 0);
  }
  // rightY[i] = 从索引 i 开始到末尾的 'Y' 的个数
  vector<int> rightY(n + 1, 0);
  for (int i = n - 1; i >= 0; --i) {
    rightY[i] = rightY[i + 1] + (customers[i] == 'Y' ? 1 : 0);
  }
  int minPenalty = INT_MAX;
  int bestHour = 0;
  for (int j = 0; j <= n; ++j) {
    int penalty = leftN[j] + rightY[j];
    if (penalty < minPenalty) {
      minPenalty = penalty;
      bestHour = j;
    }
  }
  return bestHour;
}

// 策略二：一次遍历优化
// 初始惩罚 = 总 'Y' 的数量（假设关闭时间为 0）
// 遍历每个小时，如果将关闭时间推后一小时，惩罚的变化：
// - 如果当前小时是 'Y'，惩罚减少 1（因为该小时从关闭变为开放，有顾客不产生惩罚）
// - 如果当前小时是 'N'，惩罚增加 1（因为该小时从关闭变为开放，没有顾客产生惩罚）
// 时间复杂度: O(n)，空间复杂度: O(1)
static int solution2(string customers) {
  const int n = customers.size();
  // 计算总 'Y' 的数量
  int totalY = 0;
  for (char c : customers) {
    if (c == 'Y') ++totalY;
  }
  int penalty = totalY;
  int minPenalty = penalty;
  int bestHour = 0;
  for (int i = 0; i < n; ++i) {
    if (customers[i] == 'Y') {
      --penalty;  // 该小时从关闭变为开放，有顾客，惩罚减少
    } else {
      ++penalty;  // 该小时从关闭变为开放，没有顾客，惩罚增加
    }
    if (penalty < minPenalty) {
      minPenalty = penalty;
      bestHour = i + 1;
    }
  }
  return bestHour;
}

MinimumPenaltyForAShopSolution::MinimumPenaltyForAShopSolution() {
  setMetaInfo({.id = 2483,
               .title = "Minimum Penalty for a Shop",
               .url = "https://leetcode.com/problems/minimum-penalty-for-a-shop"});
  registerStrategy("Prefix-Suffix Array", solution1);
  registerStrategy("One-Pass Optimization", solution2);
}

int MinimumPenaltyForAShopSolution::bestClosingTime(string customers) {
  return getSolution()(customers);
}

}  // namespace problem_2483
}  // namespace leetcode