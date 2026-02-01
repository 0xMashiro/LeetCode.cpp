#include "leetcode/problems/best-time-to-buy-and-sell-stock-iii.h"

namespace leetcode {
namespace problem_123 {

/**
 * 动态规划解法
 * 
 * 状态定义：
 * - buy1:  第一次买入后的最大利润（负数，表示支出）
 * - sell1: 第一次卖出后的最大利润
 * - buy2:  第二次买入后的最大利润
 * - sell2: 第二次卖出后的最大利润
 * 
 * 状态转移方程：
 * - buy1  = max(buy1,  -price[i])     // 第一次买入，或保持之前状态
 * - sell1 = max(sell1, buy1 + price[i])  // 第一次卖出
 * - buy2  = max(buy2,  sell1 - price[i]) // 第二次买入（用第一次的利润）
 * - sell2 = max(sell2, buy2 + price[i])  // 第二次卖出
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
static int solution1(vector<int>& prices) {
  const int n = prices.size();
  if (n < 2) return 0;
  
  // 初始状态：
  // buy1 = -prices[0]（第一天买入）
  // sell1 = 0（尚未卖出）
  // buy2 = -prices[0]（同一天买卖再买入，实际相当于只买入一次）
  // sell2 = 0（尚未卖出）
  int buy1 = -prices[0];
  int sell1 = 0;
  int buy2 = -prices[0];
  int sell2 = 0;
  
  for (int i = 1; i < n; ++i) {
    // 更新顺序很重要：先更新 sell2，然后 buy2，然后 sell1，最后 buy1
    // 或者使用临时变量保存上一轮的状态
    int price = prices[i];
    
    // 新的状态基于旧状态计算
    int new_sell2 = max(sell2, buy2 + price);
    int new_buy2 = max(buy2, sell1 - price);
    int new_sell1 = max(sell1, buy1 + price);
    int new_buy1 = max(buy1, -price);
    
    sell2 = new_sell2;
    buy2 = new_buy2;
    sell1 = new_sell1;
    buy1 = new_buy1;
  }
  
  return sell2;
}

/**
 * 简化版动态规划
 * 使用数组存储每个状态下的最大利润
 */
static int solution2(vector<int>& prices) {
  const int n = prices.size();
  if (n < 2) return 0;
  
  // dp[0]: 未进行任何操作
  // dp[1]: 第一次持有股票
  // dp[2]: 第一次卖出股票
  // dp[3]: 第二次持有股票
  // dp[4]: 第二次卖出股票
  vector<int> dp(5, 0);
  dp[1] = dp[3] = -prices[0];
  
  for (int i = 1; i < n; ++i) {
    int price = prices[i];
    dp[4] = max(dp[4], dp[3] + price);
    dp[3] = max(dp[3], dp[2] - price);
    dp[2] = max(dp[2], dp[1] + price);
    dp[1] = max(dp[1], -price);
  }
  
  return dp[4];
}

BestTimeToBuyAndSellStockIiiSolution::BestTimeToBuyAndSellStockIiiSolution() {
  setMetaInfo({
    .id = 123,
    .title = "Best Time to Buy and Sell Stock III",
    .url = "https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/"
  });
  registerStrategy("DP with Variables", solution1);
  registerStrategy("DP with Array", solution2);
}

int BestTimeToBuyAndSellStockIiiSolution::maxProfit(vector<int>& prices) {
  return getSolution()(prices);
}

}  // namespace problem_123
}  // namespace leetcode
