#include "leetcode/problems/minimum-number-of-chairs-in-a-waiting-room.h"

namespace leetcode {
namespace problem_3168 {

// 贪心计数：跟踪当前人数，记录最大人数
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(string s) {
  int current = 0;  // 当前等待室中的人数
  int maxChairs = 0;  // 需要的最大椅子数
  
  for (char c : s) {
    if (c == 'E') {
      ++current;  // 有人进入
      maxChairs = max(maxChairs, current);
    } else {
      --current;  // 有人离开
    }
  }
  
  return maxChairs;
}

MinimumNumberOfChairsInAWaitingRoomSolution::MinimumNumberOfChairsInAWaitingRoomSolution() {
  setMetaInfo({.id = 3168,
               .title = "Minimum Number of Chairs in a Waiting Room",
               .url = "https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/"});
  registerStrategy("Greedy Counting", solution1);
}

int MinimumNumberOfChairsInAWaitingRoomSolution::minimumChairs(string s) {
  return getSolution()(s);
}

}  // namespace problem_3168
}  // namespace leetcode
