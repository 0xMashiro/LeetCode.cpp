
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1129 {

using Func = std::function<vector<int>(int, vector<vector<int>>&, vector<vector<int>>&)>;

class ShortestPathWithAlternatingColorsSolution : public SolutionBase<Func> {
 public:
  //! 1129. Shortest Path with Alternating Colors
  //! https://leetcode.com/problems/shortest-path-with-alternating-colors/
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, 
                                       vector<vector<int>>& blueEdges);

  ShortestPathWithAlternatingColorsSolution();
};

}  // namespace problem_1129
}  // namespace leetcode
