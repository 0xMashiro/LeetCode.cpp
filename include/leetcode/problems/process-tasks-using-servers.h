#include "leetcode/core.h"

namespace leetcode {
namespace problem_1882 {

using Func = std::function<vector<int>(vector<int>&, vector<int>&)>;

class ProcessTasksUsingServersSolution : public SolutionBase<Func> {
 public:
  //! 1882. Process Tasks Using Servers
  //! https://leetcode.com/problems/process-tasks-using-servers/
  vector<int> assignTasks(vector<int>& servers, vector<int>& tasks);

  ProcessTasksUsingServersSolution();
};

}  // namespace problem_1882
}  // namespace leetcode
