#include "leetcode/core.h"

namespace leetcode {
namespace problem_1356 {

using Func = std::function<vector<int>(vector<int>&)>;

class SortIntegersByTheNumberOf1BitsSolution : public SolutionBase<Func> {
 public:
  //! 1356. Sort Integers by The Number of 1 Bits
  //! https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
  vector<int> sortByBits(vector<int>& arr);

  SortIntegersByTheNumberOf1BitsSolution();
};

}  // namespace problem_1356
}  // namespace leetcode
