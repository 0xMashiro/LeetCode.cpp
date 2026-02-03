
#include "leetcode/problems/guess-number-higher-or-lower.h"

namespace leetcode {
namespace problem_374 {

// Forward declaration of the guess API
extern int guess(int num);

// 二分查找：根据 guess API 的反馈不断缩小搜索范围
// 时间复杂度: O(log n), 空间复杂度: O(1)
static int solution1(int n) {
  int left = 1;
  int right = n;
  
  while (left <= right) {
    // 防溢出写法
    int mid = left + (right - left) / 2;
    int result = guess(mid);
    
    if (result == 0) {
      // 猜对了
      return mid;
    } else if (result == -1) {
      // 猜大了，往左半部分搜索
      right = mid - 1;
    } else {
      // 猜小了，往右半部分搜索
      left = mid + 1;
    }
  }
  
  // 根据题意一定能找到，这里返回 -1 作为兜底
  return -1;
}

GuessNumberHigherOrLowerSolution::GuessNumberHigherOrLowerSolution() {
  setMetaInfo({.id = 374,
               .title = "Guess Number Higher or Lower",
               .url = "https://leetcode.com/problems/guess-number-higher-or-lower/"});
  registerStrategy("Binary Search", solution1);
}

int GuessNumberHigherOrLowerSolution::guessNumber(int n) {
  return getSolution()(n);
}

}  // namespace problem_374
}  // namespace leetcode
