#include "leetcode/core.h"

namespace leetcode {
namespace problem_122 {

using Func = std::function<int(vector<int>&)>;

class BestTimeToBuyAndSellStockIiSolution : public SolutionBase<Func> {
 public:
  int maxProfit(vector<int>& prices);
  BestTimeToBuyAndSellStockIiSolution();
};

}  // namespace problem_122
}  // namespace leetcode
