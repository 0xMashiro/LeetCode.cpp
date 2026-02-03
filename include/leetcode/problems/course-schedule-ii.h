#include "leetcode/core.h"

namespace leetcode {
namespace problem_210 {

using Func = std::function<vector<int>(int, vector<vector<int>>&)>;

class CourseScheduleIiSolution : public SolutionBase<Func> {
 public:
  //! 210. Course Schedule II
  //! https://leetcode.com/problems/course-schedule-ii/
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);

  CourseScheduleIiSolution();
};

}  // namespace problem_210
}  // namespace leetcode
