#include "leetcode/core.h"

namespace leetcode {
namespace problem_2295 {

using Func = std::function<vector<int>(vector<int>&, vector<vector<int>>&)>;

class ReplaceElementsInAnArraySolution : public SolutionBase<Func> {
 public:
  //! 2295. Replace Elements in an Array
  //! https://leetcode.com/problems/replace-elements-in-an-array/
  vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations);

  ReplaceElementsInAnArraySolution();
};

}  // namespace problem_2295
}  // namespace leetcode
