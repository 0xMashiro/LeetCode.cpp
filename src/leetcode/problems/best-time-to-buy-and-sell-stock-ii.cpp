#include "leetcode/problems/best-time-to-buy-and-sell-stock-ii.h"

namespace leetcode {
namespace problem_122 {

// 贪心算法：累加所有上升段的利润
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(vector<int>& prices) {
  int profit = 0;
  for (size_t i = 1; i < prices.size(); ++i) {
    if (prices[i] > prices[i - 1]) {
      profit += prices[i] - prices[i - 1];
    }
  }
  return profit;
}

BestTimeToBuyAndSellStockIiSolution::BestTimeToBuyAndSellStockIiSolution() {
  setMetaInfo({
    .id = 122,
    .title = "Best Time to Buy and Sell Stock II",
    .url = "https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/"
  });
  registerStrategy("Greedy", solution1);
}

int BestTimeToBuyAndSellStockIiSolution::maxProfit(vector<int>& prices) {
  return getSolution()(prices);
}

}  // namespace problem_122
}  // namespace leetcode
