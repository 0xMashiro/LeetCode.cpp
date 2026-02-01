#include "leetcode/problems/find-closest-person.h"

namespace leetcode {
namespace problem_3516 {

// 直接计算距离比较
// 时间复杂度: O(1), 空间复杂度: O(1)
static int solution1(int x, int y, int z) {
  int dist1 = abs(x - z);  // Person 1 到 Person 3 的距离
  int dist2 = abs(y - z);  // Person 2 到 Person 3 的距离
  
  if (dist1 < dist2) {
    return 1;  // Person 1 先到达
  } else if (dist1 > dist2) {
    return 2;  // Person 2 先到达
  } else {
    return 0;  // 同时到达
  }
}

FindClosestPersonSolution::FindClosestPersonSolution() {
  setMetaInfo({.id = 3516,
               .title = "Find Closest Person",
               .url = "https://leetcode.com/problems/find-closest-person/"});
  registerStrategy("Direct Compare", solution1);
}

int FindClosestPersonSolution::findClosest(int x, int y, int z) {
  return getSolution()(x, y, z);
}

}  // namespace problem_3516
}  // namespace leetcode
