#include "leetcode/core.h"

namespace leetcode {
namespace problem_879 {

using Func = std::function<int(int, int, vector<int>&, vector<int>&)>;

class ProfitableSchemesSolution : public SolutionBase<Func> {
 public:
  //! 879. Profitable Schemes
  //! https://leetcode.com/problems/profitable-schemes/
  int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit);

  ProfitableSchemesSolution();
};

}  // namespace problem_879
}  // namespace leetcode
