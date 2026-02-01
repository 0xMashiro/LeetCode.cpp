#include "leetcode/core.h"

namespace leetcode {
namespace problem_123 {

using Func = std::function<int(vector<int>&)>;

/**
 * 123. Best Time to Buy and Sell Stock III
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
 * 
 * 给定一个数组 prices，其中 prices[i] 是第 i 天的股票价格。
 * 最多可以完成两笔交易，求能获得的最大利润。
 * 注意：不能同时参与多笔交易（必须在再次购买前出售掉之前的股票）。
 */
class BestTimeToBuyAndSellStockIiiSolution : public SolutionBase<Func> {
 public:
  int maxProfit(vector<int>& prices);

  BestTimeToBuyAndSellStockIiiSolution();
};

}  // namespace problem_123
}  // namespace leetcode
