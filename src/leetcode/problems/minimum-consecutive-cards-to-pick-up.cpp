#include "leetcode/problems/minimum-consecutive-cards-to-pick-up.h"

namespace leetcode {
namespace problem_2260 {

// 哈希表解法：记录每个数字最近一次出现的索引
// 遍历数组，如果数字已存在则计算距离并更新最小值
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& cards) {
  const int n = cards.size();
  unordered_map<int, int> lastIndex;  // 数字 -> 最近出现的位置
  int minCards = INT_MAX;
  
  for (int i = 0; i < n; ++i) {
    int card = cards[i];
    if (lastIndex.find(card) != lastIndex.end()) {
      // 找到了一对匹配卡片
      // 从 lastIndex[card] 到 i 的连续卡片数量为 i - lastIndex[card] + 1
      minCards = min(minCards, i - lastIndex[card] + 1);
    }
    // 更新该数字的最近索引
    lastIndex[card] = i;
  }
  
  return minCards == INT_MAX ? -1 : minCards;
}

MinimumConsecutiveCardsToPickUpSolution::MinimumConsecutiveCardsToPickUpSolution() {
  setMetaInfo({.id = 2260,
               .title = "Minimum Consecutive Cards to Pick Up",
               .url = "https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/"});
  registerStrategy("Hash Table", solution1);
}

int MinimumConsecutiveCardsToPickUpSolution::minimumCardPickup(vector<int>& cards) {
  return getSolution()(cards);
}

}  // namespace problem_2260
}  // namespace leetcode
