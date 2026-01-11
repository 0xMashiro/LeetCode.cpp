#include "leetcode/core.h"

namespace leetcode {
namespace problem_85 {

using Func = std::function<int(vector<vector<char>>&)>;

class MaximalRectangleSolution : public SolutionBase<Func> {
 public:
  //! 85. Maximal Rectangle
  //! https://leetcode.com/problems/maximal-rectangle/
  int maximalRectangle(vector<vector<char>>& matrix);

  MaximalRectangleSolution();
};

}  // namespace problem_85
}  // namespace leetcode