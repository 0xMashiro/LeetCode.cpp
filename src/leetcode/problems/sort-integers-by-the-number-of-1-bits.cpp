#include "leetcode/problems/sort-integers-by-the-number-of-1-bits.h"

namespace leetcode {
namespace problem_1356 {

// 计算整数二进制表示中 1 的个数
static int countBits(int n) {
  int count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

// 使用自定义比较器排序
// 先按二进制 1 的个数排序，个数相同则按数值排序
// 时间复杂度: O(n log n), 空间复杂度: O(log n) 或 O(n)
static vector<int> solution1(vector<int>& arr) {
  vector<int> result = arr;
  sort(result.begin(), result.end(), [](int a, int b) {
    int countA = countBits(a);
    int countB = countBits(b);
    if (countA != countB) {
      return countA < countB;
    }
    return a < b;
  });
  return result;
}

SortIntegersByTheNumberOf1BitsSolution::SortIntegersByTheNumberOf1BitsSolution() {
  setMetaInfo({.id = 1356,
               .title = "Sort Integers by The Number of 1 Bits",
               .url = "https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/"});
  registerStrategy("Custom Comparator", solution1);
}

vector<int> SortIntegersByTheNumberOf1BitsSolution::sortByBits(vector<int>& arr) {
  return getSolution()(arr);
}

}  // namespace problem_1356
}  // namespace leetcode
