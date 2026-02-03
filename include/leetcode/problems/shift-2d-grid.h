#include "leetcode/core.h"

namespace leetcode {
namespace problem_1260 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&, int)>;

class Shift2dGridSolution : public SolutionBase<Func> {
 public:
  vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k);
  Shift2dGridSolution();
};

}  // namespace problem_1260
}  // namespace leetcode
