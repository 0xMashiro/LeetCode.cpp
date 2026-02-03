#include "leetcode/core.h"

namespace leetcode {
namespace problem_2501 {

using Func = std::function<int(vector<int>&)>;

class LongestSquareStreakInAnArraySolution : public SolutionBase<Func> {
 public:
  //! 2501. Longest Square Streak in an Array
  //! https://leetcode.com/problems/longest-square-streak-in-an-array/
  int longestSquareStreak(vector<int>& nums);

  LongestSquareStreakInAnArraySolution();
};

}  // namespace problem_2501
}  // namespace leetcode
