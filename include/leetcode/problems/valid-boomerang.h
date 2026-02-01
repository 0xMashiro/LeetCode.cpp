#include "leetcode/core.h"

namespace leetcode {
namespace problem_1037 {

using Func = std::function<bool(vector<vector<int>>&)>;

class ValidBoomerangSolution : public SolutionBase<Func> {
 public:
  //! 1037. Valid Boomerang
  //! https://leetcode.com/problems/valid-boomerang/
  bool isBoomerang(vector<vector<int>>& points);

  ValidBoomerangSolution();
};

}  // namespace problem_1037
}  // namespace leetcode
