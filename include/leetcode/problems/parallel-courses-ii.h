#include "leetcode/core.h"

namespace leetcode {
namespace problem_1494 {

using Func = std::function<int(int, vector<vector<int>>&, int)>;

class ParallelCoursesIiSolution : public SolutionBase<Func> {
 public:
  //! 1494. Parallel Courses II
  //! https://leetcode.com/problems/parallel-courses-ii/
  int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k);

  ParallelCoursesIiSolution();
};

}  // namespace problem_1494
}  // namespace leetcode
