
#include "leetcode/core.h"

namespace leetcode {
namespace problem_440 {

using Func = std::function<int(int, int)>;

class KThSmallestInLexicographicalOrderSolution : public SolutionBase<Func> {
 public:
  //! 440. K-th Smallest in Lexicographical Order
  //! https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/
  int findKthNumber(int n, int k);

  KThSmallestInLexicographicalOrderSolution();
};

}  // namespace problem_440
}  // namespace leetcode
