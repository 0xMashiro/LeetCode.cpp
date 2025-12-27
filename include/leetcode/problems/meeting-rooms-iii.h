#include "leetcode/core.h"

namespace leetcode {
namespace problem_2402 {

using Func = std::function<int(int, vector<vector<int>>&)>;

class MeetingRoomsIiiSolution : public SolutionBase<Func> {
 public:
  //! 2402. Meeting Rooms III
  //! https://leetcode.com/problems/meeting-rooms-iii/
  int mostBooked(int n, vector<vector<int>>& meetings);

  MeetingRoomsIiiSolution();
};

}  // namespace problem_2402
}  // namespace leetcode