#include "leetcode/core.h"

namespace leetcode {
namespace problem_868 {

using Func = std::function<int(int)>;

class BinaryGapSolution : public SolutionBase<Func> {
 public:
  //! 868. Binary Gap
  //! https://leetcode.com/problems/binary-gap/
  int binaryGap(int n);

  BinaryGapSolution();
};

}  // namespace problem_868
}  // namespace leetcode
