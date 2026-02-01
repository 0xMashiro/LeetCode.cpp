
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2235 {

using Func = std::function<int(int, int)>;

class AddTwoIntegersSolution : public SolutionBase<Func> {
 public:
  //! 2235. Add Two Integers
  //! https://leetcode.com/problems/add-two-integers/
  int sum(int num1, int num2);

  AddTwoIntegersSolution();
};

}  // namespace problem_2235
}  // namespace leetcode
