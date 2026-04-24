#include "leetcode/core.h"

namespace leetcode {
namespace problem_2584 {

using Func = std::function<int(vector<int>&)>;

class SplitTheArrayToMakeCoprimeProductsSolution : public SolutionBase<Func> {
 public:
  //! 2584. Split the Array to Make Coprime Products
  //! https://leetcode.com/problems/split-the-array-to-make-coprime-products/
  int findValidSplit(vector<int>& nums);

  SplitTheArrayToMakeCoprimeProductsSolution();
};

}  // namespace problem_2584
}  // namespace leetcode
