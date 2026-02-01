
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2646 {

using Func = std::function<int(int, vector<vector<int>>&, vector<int>&, vector<vector<int>>&)>;

class MinimizeTheTotalPriceOfTheTripsSolution : public SolutionBase<Func> {
 public:
  //! 2646. Minimize the Total Price of the Trips
  //! https://leetcode.com/problems/minimize-the-total-price-of-the-trips/
  int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips);

  MinimizeTheTotalPriceOfTheTripsSolution();
};

}  // namespace problem_2646
}  // namespace leetcode
