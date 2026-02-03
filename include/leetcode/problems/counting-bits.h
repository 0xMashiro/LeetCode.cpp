#include "leetcode/core.h"

namespace leetcode {
namespace problem_338 {

using Func = std::function<vector<int>(int)>;

class CountingBitsSolution : public SolutionBase<Func> {
 public:
  //! 338. Counting Bits
  //! https://leetcode.com/problems/counting-bits/
  vector<int> countBits(int n);

  CountingBitsSolution();
};

}  // namespace problem_338
}  // namespace leetcode
