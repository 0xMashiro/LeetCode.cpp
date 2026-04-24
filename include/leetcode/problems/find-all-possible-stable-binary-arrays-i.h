#include "leetcode/core.h"

namespace leetcode {
namespace problem_3129 {

using Func = std::function<int(int, int, int)>;

class FindAllPossibleStableBinaryArraysISolution : public SolutionBase<Func> {
 public:
  int numberOfStableArrays(int zero, int one, int limit);
  FindAllPossibleStableBinaryArraysISolution();
};

}  // namespace problem_3129
}  // namespace leetcode
