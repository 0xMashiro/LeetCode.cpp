#ifndef LEETCODE_PROBLEMS_PATH_EXISTENCE_QUERIES_IN_A_GRAPH_II_H_
#define LEETCODE_PROBLEMS_PATH_EXISTENCE_QUERIES_IN_A_GRAPH_II_H_

#include "leetcode/core.h"

namespace leetcode {
namespace problem_3534 {

using Func = std::function<std::vector<int>(int, std::vector<int>&, int,
                                            std::vector<std::vector<int>>&)>;

class PathExistenceQueriesInAGraphIiSolution : public SolutionBase<Func> {
 public:
  //! 3534. Path Existence Queries in a Graph II
  //! https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/
  std::vector<int> pathExistenceQueries(int n, std::vector<int>& nums,
                                        int maxDiff,
                                        std::vector<std::vector<int>>& queries);

  PathExistenceQueriesInAGraphIiSolution();
};

}  // namespace problem_3534
}  // namespace leetcode

#endif  // LEETCODE_PROBLEMS_PATH_EXISTENCE_QUERIES_IN_A_GRAPH_II_H_
