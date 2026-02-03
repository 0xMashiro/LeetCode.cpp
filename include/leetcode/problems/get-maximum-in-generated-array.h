
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1646 {

using Func = std::function<int(int)>;

class GetMaximumInGeneratedArraySolution : public SolutionBase<Func> {
 public:
  //! 1646. Get Maximum in Generated Array
  //! https://leetcode.com/problems/get-maximum-in-generated-array/
  int getMaximumGenerated(int n);

  GetMaximumInGeneratedArraySolution();
};

}  // namespace problem_1646
}  // namespace leetcode
