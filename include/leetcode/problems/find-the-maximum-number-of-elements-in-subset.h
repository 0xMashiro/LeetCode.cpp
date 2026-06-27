#include "leetcode/core.h"

namespace leetcode {
namespace problem_3020 {

using Func = std::function<int(std::vector<int>&)>;

class FindTheMaximumNumberOfElementsInSubsetSolution : public SolutionBase<Func> {
 public:
  //! 3020. Find the Maximum Number of Elements in Subset
  //! https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/
  int maximumLength(std::vector<int>& nums);

  FindTheMaximumNumberOfElementsInSubsetSolution();
};

}  // namespace problem_3020
}  // namespace leetcode
