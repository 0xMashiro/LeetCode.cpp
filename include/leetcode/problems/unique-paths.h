#include "leetcode/core.h"

namespace leetcode {
namespace problem_62 {

using Func = std::function<int(int, int)>;

class UniquePathsSolution : public SolutionBase<Func> {
 public:
  //! 62. Unique Paths
  //! https://leetcode.com/problems/unique-paths/
  int uniquePaths(int m, int n);

  UniquePathsSolution();
};

}  // namespace problem_62
}  // namespace leetcode
