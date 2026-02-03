#include "leetcode/problems/three-consecutive-odds.h"

namespace leetcode {
namespace problem_1550 {

// 遍历数组，检查每三个连续的元素是否都是奇数
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution1(vector<int>& arr) {
  const int n = arr.size();
  // 数组长度小于3时，不可能有三个连续的奇数
  if (n < 3) return false;
  
  for (int i = 0; i <= n - 3; ++i) {
    // 检查 arr[i], arr[i+1], arr[i+2] 是否都是奇数
    if (arr[i] % 2 == 1 && arr[i + 1] % 2 == 1 && arr[i + 2] % 2 == 1) {
      return true;
    }
  }
  return false;
}

// 计数法：遍历数组，记录连续奇数的个数
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution2(vector<int>& arr) {
  int count = 0;
  for (int num : arr) {
    if (num % 2 == 1) {
      ++count;
      if (count == 3) return true;
    } else {
      count = 0;
    }
  }
  return false;
}

ThreeConsecutiveOddsSolution::ThreeConsecutiveOddsSolution() {
  setMetaInfo({.id = 1550,
               .title = "Three Consecutive Odds",
               .url = "https://leetcode.com/problems/three-consecutive-odds"});
  registerStrategy("Direct Check", solution1);
  registerStrategy("Counter", solution2);
}

bool ThreeConsecutiveOddsSolution::threeConsecutiveOdds(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_1550
}  // namespace leetcode
