
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2685 {

using Func = std::function<int(int, vector<vector<int>>&)>;

/**
 * 2685. Count the Number of Complete Components
 * https://leetcode.com/problems/count-the-number-of-complete-components/
 * 
 * 给定 n 个顶点的无向图，统计完全连通分量的数量
 * 完全连通分量：连通分量中任意两个顶点之间都有边
 */
class CountTheNumberOfCompleteComponentsSolution : public SolutionBase<Func> {
 public:
  int countCompleteComponents(int n, vector<vector<int>>& edges);

  CountTheNumberOfCompleteComponentsSolution();
};

}  // namespace problem_2685
}  // namespace leetcode
