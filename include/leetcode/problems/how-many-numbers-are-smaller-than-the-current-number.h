
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1365 {

using Func = std::function<vector<int>(vector<int>&)>;

class HowManyNumbersAreSmallerThanTheCurrentNumberSolution : public SolutionBase<Func> {
 public:
  //! 1365. How Many Numbers Are Smaller Than the Current Number
  //! https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/
  vector<int> smallerNumbersThanCurrent(vector<int>& nums);

  HowManyNumbersAreSmallerThanTheCurrentNumberSolution();
};

}  // namespace problem_1365
}  // namespace leetcode
