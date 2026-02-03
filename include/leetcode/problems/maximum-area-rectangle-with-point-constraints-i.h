#include "leetcode/core.h"

namespace leetcode {
namespace problem_3380 {

using Func = std::function<int(vector<vector<int>>&)>;

class MaximumAreaRectangleWithPointConstraintsISolution : public SolutionBase<Func> {
 public:
  int maxRectangleArea(vector<vector<int>>& points);
  MaximumAreaRectangleWithPointConstraintsISolution();
};

}  // namespace problem_3380
}  // namespace leetcode