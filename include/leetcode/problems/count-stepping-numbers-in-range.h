#include "leetcode/core.h"

namespace leetcode {
namespace problem_2801 {

using Func = std::function<int(string, string)>;

class CountSteppingNumbersInRangeSolution : public SolutionBase<Func> {
 public:
  //! 2801. Count Stepping Numbers in Range
  //! https://leetcode.com/problems/count-stepping-numbers-in-range/
  int countSteppingNumbers(string low, string high);

  CountSteppingNumbersInRangeSolution();
};

}  // namespace problem_2801
}  // namespace leetcode
