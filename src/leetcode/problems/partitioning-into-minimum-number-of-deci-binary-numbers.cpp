#include "leetcode/problems/partitioning-into-minimum-number-of-deci-binary-numbers.h"

namespace leetcode {
namespace problem_1689 {

// 解法：找到字符串中最大的数字
// 时间复杂度: O(n), 空间复杂度: O(1)
// 核心思想：deci-binary 数字的每一位只能是 0 或 1
// 要表示数字 d，需要 d 个 deci-binary 数字在该位上为 1
// 因此答案就是 n 中最大的那个数字
static int solution1(string n) {
  int max_digit = 0;
  for (char c : n) {
    max_digit = max(max_digit, c - '0');
    // 如果已经找到 9，直接返回（最大可能值）
    if (max_digit == 9) break;
  }
  return max_digit;
}

PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution::PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution() {
  setMetaInfo({.id = 1689,
               .title = "Partitioning Into Minimum Number Of Deci-Binary Numbers",
               .url = "https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/"});
  registerStrategy("Max Digit", solution1);
}

int PartitioningIntoMinimumNumberOfDeciBinaryNumbersSolution::minPartitions(string n) {
  return getSolution()(n);
}

}  // namespace problem_1689
}  // namespace leetcode
