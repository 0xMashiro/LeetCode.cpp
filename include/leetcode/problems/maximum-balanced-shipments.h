#include "leetcode/core.h"

namespace leetcode {
namespace problem_3638 {

using Func = std::function<int(vector<int>&)>;

class MaximumBalancedShipmentsSolution : public SolutionBase<Func> {
 public:
  //! 3638. Maximum Balanced Shipments
  //! https://leetcode.com/problems/maximum-balanced-shipments/
  int maxBalancedShipments(vector<int>& weight);

  MaximumBalancedShipmentsSolution();
};

}  // namespace problem_3638
}  // namespace leetcode
