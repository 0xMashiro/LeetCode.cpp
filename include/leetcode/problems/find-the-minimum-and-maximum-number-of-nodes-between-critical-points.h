
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2058 {

using Func = std::function<vector<int>(ListNode*)>;

class FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution : public SolutionBase<Func> {
 public:
  //! 2058. Find the Minimum and Maximum Number of Nodes Between Critical Points
  //! https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/
  vector<int> nodesBetweenCriticalPoints(ListNode* head);

  FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPointsSolution();
};

}  // namespace problem_2058
}  // namespace leetcode
