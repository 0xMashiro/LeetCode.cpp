#include "leetcode/problems/first-bad-version.h"

namespace leetcode {
namespace problem_278 {

// 定义 API 变量
std::function<bool(int)> isBadVersion_api;

// 二分查找：寻找第一个坏版本
// 时间复杂度: O(log n), 空间复杂度: O(1)
static int solution1(int n) {
  int left = 1, right = n;
  while (left < right) {
    // 防止整数溢出
    int mid = left + (right - left) / 2;
    if (isBadVersion_api(mid)) {
      // mid 是坏版本，第一个坏版本在 [left, mid]
      right = mid;
    } else {
      // mid 是好版本，第一个坏版本在 [mid+1, right]
      left = mid + 1;
    }
  }
  return left;
}

FirstBadVersionSolution::FirstBadVersionSolution() {
  setMetaInfo({.id = 278,
               .title = "First Bad Version",
               .url = "https://leetcode.com/problems/first-bad-version/"});
  registerStrategy("Binary Search", solution1);
}

int FirstBadVersionSolution::firstBadVersion(int n) {
  return getSolution()(n);
}

}  // namespace problem_278
}  // namespace leetcode
