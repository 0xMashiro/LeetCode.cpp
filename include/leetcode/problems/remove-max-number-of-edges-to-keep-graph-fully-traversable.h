#include "leetcode/core.h"

namespace leetcode {
namespace problem_1579 {

using Func = std::function<int(int, vector<vector<int>>&)>;

class RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution : public SolutionBase<Func> {
 public:
  //! 1579. Remove Max Number of Edges to Keep Graph Fully Traversable
  //! https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
  int maxNumEdgesToRemove(int n, vector<vector<int>>& edges);

  RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution();
};

}  // namespace problem_1579
}  // namespace leetcode
