#include "leetcode/core.h"

namespace leetcode {
namespace problem_48 {

using Func = std::function<void(vector<vector<int>>&)>;

class RotateImageSolution : public SolutionBase<Func> {
 public:
  void rotate(vector<vector<int>>& matrix);
  RotateImageSolution();
};

}  // namespace problem_48
}  // namespace leetcode
