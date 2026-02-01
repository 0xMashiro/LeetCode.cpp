#include "leetcode/core.h"

namespace leetcode {
namespace problem_3168 {

using Func = std::function<int(string)>;

class MinimumNumberOfChairsInAWaitingRoomSolution : public SolutionBase<Func> {
 public:
  //! 3168. Minimum Number of Chairs in a Waiting Room
  //! https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/
  int minimumChairs(string s);

  MinimumNumberOfChairsInAWaitingRoomSolution();
};

}  // namespace problem_3168
}  // namespace leetcode
