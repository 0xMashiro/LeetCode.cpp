#include "leetcode/core.h"

namespace leetcode {
namespace problem_693 {

using Func = std::function<bool(int)>;

class BinaryNumberWithAlternatingBitsSolution : public SolutionBase<Func> {
 public:
  //! 693. Binary Number with Alternating Bits
  //! https://leetcode.com/problems/binary-number-with-alternating-bits/
  bool hasAlternatingBits(int n);

  BinaryNumberWithAlternatingBitsSolution();
};

}  // namespace problem_693
}  // namespace leetcode
