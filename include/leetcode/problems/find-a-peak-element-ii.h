#include "leetcode/core.h"

namespace leetcode {
namespace problem_1901 {

using Func = std::function<vector<int>(vector<vector<int>>&)>;

class FindAPeakElementIiSolution : public SolutionBase<Func> {
 public:
  //! 1901. Find a Peak Element II
  //! https://leetcode.com/problems/find-a-peak-element-ii/
  vector<int> findPeakGrid(vector<vector<int>>& mat);

  FindAPeakElementIiSolution();
};

}  // namespace problem_1901
}  // namespace leetcode
