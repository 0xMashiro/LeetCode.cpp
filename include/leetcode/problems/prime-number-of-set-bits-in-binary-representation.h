
#include "leetcode/core.h"

namespace leetcode {
namespace problem_762 {

using Func = std::function<int(int, int)>;

class PrimeNumberOfSetBitsInBinaryRepresentationSolution : public SolutionBase<Func> {
 public:
  //! 762. Prime Number of Set Bits in Binary Representation
  //! https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/
  int countPrimeSetBits(int left, int right);

  PrimeNumberOfSetBitsInBinaryRepresentationSolution();
};

}  // namespace problem_762
}  // namespace leetcode
