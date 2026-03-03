#include "leetcode/core.h"

namespace leetcode {
namespace problem_1545 {

using Func = std::function<char(int, int)>;

class FindKthBitInNthBinaryStringSolution : public SolutionBase<Func> {
 public:
  char findKthBit(int n, int k);

  FindKthBitInNthBinaryStringSolution();
};

}  // namespace problem_1545
}  // namespace leetcode
