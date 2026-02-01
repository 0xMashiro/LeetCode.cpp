#include "leetcode/core.h"

namespace leetcode {
namespace problem_1108 {

using Func = std::function<string(string)>;

class DefangingAnIpAddressSolution : public SolutionBase<Func> {
 public:
  //! 1108. Defanging an IP Address
  //! https://leetcode.com/problems/defanging-an-ip-address/
  string defangIPaddr(string address);

  DefangingAnIpAddressSolution();
};

}  // namespace problem_1108
}  // namespace leetcode
