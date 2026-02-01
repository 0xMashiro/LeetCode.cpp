#include "leetcode/core.h"

namespace leetcode {
namespace problem_867 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&)>;

class TransposeMatrixSolution : public SolutionBase<Func> {
 public:
  vector<vector<int>> transpose(vector<vector<int>>& matrix);

  TransposeMatrixSolution();
};

}  // namespace problem_867
}  // namespace leetcode