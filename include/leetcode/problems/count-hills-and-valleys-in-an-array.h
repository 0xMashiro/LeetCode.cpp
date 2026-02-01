#include "leetcode/core.h"

namespace leetcode {
namespace problem_2210 {

using Func = std::function<int(vector<int>&)>;

class CountHillsAndValleysInAnArraySolution : public SolutionBase<Func> {
 public:
  //! 2210. Count Hills and Valleys in an Array
  //! https://leetcode.com/problems/count-hills-and-valleys-in-an-array/
  int countHillValley(vector<int>& nums);

  CountHillsAndValleysInAnArraySolution();
};

}  // namespace problem_2210
}  // namespace leetcode
