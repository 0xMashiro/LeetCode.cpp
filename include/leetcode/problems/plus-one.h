#include "leetcode/core.h"

namespace leetcode {
namespace problem_66 {

using Func = std::function<vector<int>(vector<int>&)>;

class PlusOneSolution : public SolutionBase<Func> {
 public:
  //! 66. Plus One
  //! https://leetcode.com/problems/plus-one/
  vector<int> plusOne(vector<int>& digits);

  PlusOneSolution();
};

}  // namespace problem_66
}  // namespace leetcode