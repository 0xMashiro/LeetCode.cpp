
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3074 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

class AppleRedistributionIntoBoxesSolution : public SolutionBase<Func> {
 public:
  //! 3074. Apple Redistribution into Boxes
  //! https://leetcode.com/problems/apple-redistribution-into-boxes/
  int minimumBoxes(vector<int>& apple, vector<int>& capacity);

  AppleRedistributionIntoBoxesSolution();
};

}  // namespace problem_3074
}  // namespace leetcode