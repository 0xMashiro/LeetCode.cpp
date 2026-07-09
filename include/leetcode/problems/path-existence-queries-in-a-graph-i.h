#include "leetcode/core.h"

namespace leetcode {
namespace problem_3532 {

using Func = std::function<std::vector<bool>(int, std::vector<int>&, int, std::vector<std::vector<int>>&)>;

class PathExistenceQueriesInAGraphISolution : public SolutionBase<Func> {
 public:
  //! 3532. Path Existence Queries in a Graph I
  //! https://leetcode.com/problems/path-existence-queries-in-a-graph-i/
  std::vector<bool> pathExistenceQueries(int n, std::vector<int>& nums, int maxDiff,
                                         std::vector<std::vector<int>>& queries);

  PathExistenceQueriesInAGraphISolution();
};

}  // namespace problem_3532
}  // namespace leetcode
