#include "leetcode/core.h"

namespace leetcode {
namespace problem_3593 {

using Func = std::function<int(int, vector<vector<int>>&, vector<int>&)>;

class MinimumIncrementsToEqualizeLeafPathsSolution : public SolutionBase<Func> {
 public:
  //! 3593. Minimum Increments to Equalize Leaf Paths
  //! https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/
  int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost);

  MinimumIncrementsToEqualizeLeafPathsSolution();
};

}  // namespace problem_3593
}  // namespace leetcode