#include "leetcode/core.h"

namespace leetcode {
namespace problem_1806 {

using Func = std::function<int(int)>;

class MinimumNumberOfOperationsToReinitializeAPermutationSolution : public SolutionBase<Func> {
 public:
  //! 1806. Minimum Number of Operations to Reinitialize a Permutation
  //! https://leetcode.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/
  int reinitializePermutation(int n);

  MinimumNumberOfOperationsToReinitializeAPermutationSolution();
};

}  // namespace problem_1806
}  // namespace leetcode
