
#include "leetcode/problems/find-smallest-letter-greater-than-target.h"

namespace leetcode {
namespace problem_744 {

// 解法1：线性扫描
// 时间复杂度: O(n), 空间复杂度: O(1)
static char solution1(std::vector<char>& letters, char target) {
  for (char c : letters) {
    if (c > target) {
      return c;
    }
  }
  return letters[0];
}

// 解法2：二分查找（手动实现）
// 时间复杂度: O(log n), 空间复杂度: O(1)
static char solution2(std::vector<char>& letters, char target) {
  int left = 0;
  int right = letters.size();
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (letters[mid] <= target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  if (left == letters.size()) {
    return letters[0];
  }
  return letters[left];
}

// 解法3：使用 STL upper_bound
// 时间复杂度: O(log n), 空间复杂度: O(1)
static char solution3(std::vector<char>& letters, char target) {
  auto it = std::upper_bound(letters.begin(), letters.end(), target);
  if (it == letters.end()) {
    return letters[0];
  }
  return *it;
}

FindSmallestLetterGreaterThanTargetSolution::FindSmallestLetterGreaterThanTargetSolution() {
  setMetaInfo({.id = 744,
               .title = "Find Smallest Letter Greater Than Target",
               .url = "https://leetcode.com/problems/find-smallest-letter-greater-than-target/"});
  registerStrategy("Linear Scan", solution1);
  registerStrategy("Binary Search", solution2);
  registerStrategy("STL upper_bound", solution3);
}

char FindSmallestLetterGreaterThanTargetSolution::nextGreatestLetter(std::vector<char>& letters, char target) {
  return getSolution()(letters, target);
}

}  // namespace problem_744
}  // namespace leetcode