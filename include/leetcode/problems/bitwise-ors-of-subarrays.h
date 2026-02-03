#include "leetcode/core.h"

namespace leetcode {
namespace problem_898 {

using Func = std::function<int(vector<int>&)>;

class BitwiseOrsOfSubarraysSolution : public SolutionBase<Func> {
 public:
  //! 898. Bitwise ORs of Subarrays
  //! https://leetcode.com/problems/bitwise-ors-of-subarrays/
  int subarrayBitwiseORs(vector<int>& arr);

  BitwiseOrsOfSubarraysSolution();
};

}  // namespace problem_898
}  // namespace leetcode
