#include "leetcode/core.h"

namespace leetcode {
namespace problem_841 {

using Func = std::function<bool(vector<vector<int>>&)>;

class KeysAndRoomsSolution : public SolutionBase<Func> {
 public:
  //! 841. Keys and Rooms
  //! https://leetcode.com/problems/keys-and-rooms/
  bool canVisitAllRooms(vector<vector<int>>& rooms);

  KeysAndRoomsSolution();
};

}  // namespace problem_841
}  // namespace leetcode
