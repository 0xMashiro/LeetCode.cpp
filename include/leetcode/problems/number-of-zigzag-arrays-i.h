#include "leetcode/core.h"

namespace leetcode {
namespace problem_3699 {

using Func = std::function<int(int, int, int)>;

class NumberOfZigzagArraysISolution : public SolutionBase<Func> {
 public:
  int zigZagArrays(int n, int l, int r);

  NumberOfZigzagArraysISolution();
};

}  // namespace problem_3699
}  // namespace leetcode
